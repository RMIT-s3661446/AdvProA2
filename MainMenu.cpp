#include "MainMenu.h"
#include "LinkedList.h"
#include <cctype> 



MainMenu::MainMenu()
{
    hasQuit = false;
    userChoice = 0;
}

MainMenu::MainMenu(LinkedList* foodList){
    this -> foodList = foodList;
    hasQuit = false;
    userChoice = 0;
}

MainMenu::~MainMenu()
{
    foodList->clear();
}

void MainMenu::menuStart()
{
    do{
        displayMainMenu();
        std::string userInput;
        std::getline(std::cin, userInput);
        try
        {
            userChoice = std::stoi(userInput);
            handleMenuSelection(userChoice);   
        }
        catch(const std::exception& e)
        {
            std::cout << "Please enter a number for the option!!" << std::endl << std::endl;
        }
    }
    while (hasQuit != true);
    
}

//******************************



void MainMenu::displayMainMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "   1. Display Meal Options\n";
    std::cout << "   2. Purchase Meal\n";
    std::cout << "   3. Save and Exit\n";
    std::cout << "Administrator-Only Menu:\n";
    std::cout << "   4. Add Food\n";
    std::cout << "   5. Remove Food\n";
    std::cout << "   6. Display Balance\n";
    std::cout << "   7. Abort Program\n";
    std::cout << "Select your choice: " << std::endl;
}




bool MainMenu::handleMenuSelection(int option) {
    if (option == 1) {
        displayFoodMenu();
    } else if (option == 2) {
        purchaseMeal();
    } else if (option == 3) {
        std::cout << "Saving and exiting.\n";
        // Exits the main loop
        hasQuit = true;
    } else if (option == 4) {
        addFood();
    } else if (option == 5) {
        removeFood();
    } else if (option == 6) {
        displayBalance();
    } else if (option == 7) {
        abortProgram();
    } else {
        std::cout << "Invalid selection. Please try again.\n";
    }
    // Keeps the loop running
    return true;
}




void MainMenu::displayFoodMenu() {
    
    std::cout << "Food Menu\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(6) << "ID" << "|"
              << std::setw(10) << "Name" << "|"
              << std::setw(70) << "Description" << "|"
              << std::right << std::setw(10) << "Price" << "\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    std::vector<FoodItem> foodVector = foodList->returnFoodVector();
    for (const auto& item : foodVector) {
        std::string description = item.description.length() > 67 ? item.description.substr(0, 67) + "..." : item.description;
        std::cout << std::left << std::setw(6) << item.id << "|"
                  << std::setw(10) << item.name << "|"
                  << std::setw(70) << description << "|"
                  << std::right << std::fixed << std::setprecision(2) << std::setw(10) << item.Price << "\n";
    }
}


void MainMenu::purchaseMeal() {
    std::string foodID;
    std::cout << "Please enter the ID of the food you wish to purchase:\n";
    std::cin >> foodID;

    std::vector<FoodItem> foodMenu = foodList->returnFoodVector();

    // Find the food item by ID
    auto it = std::find_if(foodMenu.begin(), foodMenu.end(), [&foodID](const FoodItem& f) { return f.id == foodID; });
    if (it == foodMenu.end()) {
        std::cout << "Food item not found.\n";
        return;
    }

    // Display selected food details
    std::cout << "You have selected \"" << it->name << " - " << it->description << "\". This will cost you $ " << it->Price << ".\n";
    std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase.\n";

    // Handle payment
    double totalReceived = 0;
    double amountDue = it->Price;
    int inputCent;
    bool validInput = true;


    while (totalReceived < amountDue) {
        std::cout << "You still need to give us $" << amountDue - totalReceived << ": ";
        if (!(std::cin >> inputCent)) {
            std::cin.clear(); // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
            std::cout << "Transaction cancelled.\n";
            return;
        }

        validInput = CoinManager::getInstance().isValidDenomination(inputCent);
        if (!validInput) {
            std::cout << "Error: invalid denomination encountered.\n";
        } else {
            // Add the received amount
            totalReceived += inputCent / 100.0;
            CoinManager::getInstance().addCoin(static_cast<Denomination>(inputCent / 100), 1);
        }
    }

    // Calculate change if overpaid
    double change = totalReceived - amountDue;
    if (change > 0) {
        if (!CoinManager::getInstance().provideChange(change)) {
            std::cout << "Unable to provide correct change. Transaction cancelled.\n";
            CoinManager::getInstance().refund(totalReceived);
            return;
        }
    }

    std::cout << "Thank you for your purchase!\n";
}




void MainMenu::addFood() {
    // Get input from user for the name
    std::cout << "Enter the item name: ";
    std::string name;
    std::getline(std::cin, name);
    // Convert the first character to uppercase
    if (!name.empty()) {
        name[0] = std::toupper(name[0]);
    }
    //If name is empty return to the main menu
    if (name.size() != 0){
        if (name.size() < NAMELEN){
        
        // Get input from user for the description
        std::cout << "Enter the item description: ";
        std::string description;
        std::getline(std::cin, description);

        if (description != ""){

            if(description.size() < DESCLEN){
            
            std::cout << "Enter the price for this item (in dollars and cents, e.g., 5.25): ";
            try
            {
                std::string userInput;
                std::getline(std::cin, userInput);
                if (userInput != ""){
                    double price;
                    price = std::stod(userInput);

                    // Handle the ID formatting and price conversion
                    int priceInCents = static_cast<int>(price * 100);  // Convert dollars to cents
                    int nextID = foodList->getNextID();
                    std::stringstream idStream;
                    idStream << 'F' << std::setw(4) << std::setfill('0') << nextID;

                    name[0] = std::toupper(name[0]);

                    // Create and add a new FoodItem to the list
                    FoodItem newFood(idStream.str(), name, description, priceInCents);
                    foodList->insertSorted(newFood); // Used insertSorted to keep the list in order
    
                    // Confirmation message
                    std::cout << "This item \"" << name << " - " << description
                              << "\" has now been added to the food menu with ID " << idStream.str() << std::endl;
                }
                else{std::cout << std::endl << "Returning to the main menu" << std::endl;}
            }
            catch(const std::exception& e) {std::cout << "Please enter the number" << std::endl;}
            
        }
        else{
            std::cout << "Description is too long" << std::endl;
        }
        }else{std::cout << std::endl << "Returning to the main menu" << std::endl;}
    }
    else {std::cout << "Name is too long" << std::endl;}
    }
    else{std::cout << std::endl << "Returning to the main menu" << std::endl;}
}





void MainMenu::removeFood() {
    std::string foodID;
    std::cout << "Enter the food ID of the food to remove from the menu: ";
    std::getline(std::cin, foodID);
    if (foodID != ""){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer

        Node* itemNode = foodList->searchByID(foodID);  // Utilizing searchByID to find the node
        if (itemNode != nullptr) {
            // Access the FoodItem data from the Node
            FoodItem* item = &itemNode->data;
            std::cout << "\"" << item->id << " - " << item->name << " - " << item->description
                      << "\" is being removed from the system." << std::endl;

            foodList->deleteByID(foodID);  // Utilizing deleteByID to remove the item
        // No need to delete the FoodItem* as it is not dynamically allocated separately
        } else {
            std::cout << "No item found with ID " << foodID << std::endl;
        }
    }
    else{std::cout << "Returning to the main menu" << std::endl;}
}



void MainMenu::displayBalance() {
    // Placeholder function for displaying balance
    //std::cout << "Display Balance - To be implemented\n";
    int total = 0;
    std::cout << std::setw(10) << std::left <<  "Denom"  << " | " << std::setw(10) << std::left << "Quantity" << " | " << std::setw(10) << std::left << "Value" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    for(auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); it++){
        int denomValue = it -> second;
        int amount = CoinManager::getInstance().getBalance(it -> first);
        int subtotal = denomValue * amount;
        std::cout << std::setw(10) << std::left <<  denomValue  << " | " << std::setw(10) << std::left << amount << " | " << "$" << std::setw(10) << std::fixed << std::left << std::setprecision(2) << ((double) subtotal)/100 << std::endl;
        total += subtotal;
    }
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::setw(27) << std::right << "$" << std::right << std::fixed << std::setprecision(2) << ((double) total) /100 << std::endl;
}



void MainMenu::abortProgram() {
    std::cout << "Aborting program...\n";
    exit(0);
}