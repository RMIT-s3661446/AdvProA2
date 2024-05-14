#include "MainMenu.h"
#include "LinkedList.h"




MainMenu::MainMenu()
{
    hasQuit = false;
    userChoice = 0;
}

MainMenu::MainMenu(LinkedList* foodList){
    this -> foodList = foodList;
    hasQuit = false;
    userChoice = 0;

    /*for (int i = 0; i < NUM_DENOMS; i++){
        this -> coins[i] = coins[i];
    }*/
}

MainMenu::~MainMenu()
{
    foodList->clear();
}

void MainMenu::menuStart()
{
    do{
        displayMainMenu();
        try
        {
            std::string userInput;
            std::getline(std::cin, userInput);
            userChoice = std::stoi(userInput);
           // std::cin >> userChoice;
            handleMenuSelection(userChoice);
        }
        catch(const std::exception& e)
        {
            //std::cerr << e.what() << '\n';
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
        //return false;
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
    std::cout << "--------------\n";
    std::cout << std::setw(6) << "ID" << "|"
              << std::setw(10) << "Name" << "|"
              << std::setw(80) << "Description" << "|"
              << std::setw(6) << "Price\n";
    std::cout << "------------------------------------------------------------------\n";
    foodList -> sortByName();
    std::vector<FoodItem> foodVector = foodList -> returnFoodVector();
    for (int i = 0; i < (int)foodVector.size(); i++) {
        std::cout << std::left << std::setw(6) << foodVector[i].id << "|"
                  << std::setw(10) << foodVector[i].name << "|"
                  << std::setw(80) << foodVector[i].description << "|"
                  << std::right << std::fixed << std::setprecision(2) << std::setw(6) << foodVector[i].Price << "\n";
    }
}

void MainMenu::purchaseMeal() {
    // Placeholder function for meal purchase logic
    std::cout << "Purchase Meal - To be implemented\n";
}

void MainMenu::addFood() {
    // Clear the buffer before taking any inputs
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear any leftover characters in the input buffer

    // Get input from user for the name
    std::cout << "Enter the item name: ";
    std::string name;
    std::getline(std::cin, name);

    // Get input from user for the description
    std::cout << "Enter the item description: ";
    std::string description;
    std::getline(std::cin, description);

    double price;
    std::cout << "Enter the price for this item (in dollars and cents, e.g., 5.25): ";
    std::cin >> price;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer again after reading a numeric input

    // Handle the ID formatting and price conversion
    int priceInCents = static_cast<int>(price * 100);  // Convert dollars to cents
    int nextID = foodList->getNextID();
    std::stringstream idStream;
    idStream << 'F' << std::setw(4) << std::setfill('0') << nextID;

    // Create and add a new FoodItem to the list
    FoodItem newFood(idStream.str(), name, description, priceInCents);
    foodList->insertSorted(newFood); // Used insertSorted to keep the list in order
    

    // Confirmation message
    std::cout << "This item \"" << name << " - " << description
              << "\" has now been added to the food menu with ID " << idStream.str() << std::endl;
}


void MainMenu::removeFood() {
    std::string foodID;
    std::cout << "Enter the food ID of the food to remove from the menu: ";
    std::cin >> foodID;
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

void MainMenu::displayBalance() {
    // Placeholder function for displaying balance
    std::cout << "Display Balance - To be implemented\n";

    for (int i = 0; i > NUM_DENOMS; i++){
        std::cout << "Line " << i + 1 << ". Value: " << Coin::coinToCents(coins[i].denom)
        << ". Count: " << coins[i].count << std::endl;
    }
}

/* potential displayBalance ?
    std::vector<Coin> coins;

    void displayBalance() {
        // Sort coins by denomination
        std::sort(coins.begin(), coins.end(), [](const Coin& a, const Coin& b) {
            return a.denom < b.denom;
        });

        // Header
        std::cout << "Balance Summary\n";
        std::cout << "-------------\n";
        std::cout << "Denom | Quantity | Value\n";
        std::cout << "---------------------------\n";

        double totalValue = 0.0;
        // Display each denomination's details
        for (const auto& coin : coins) {
            double value = coin.denom * coin.count / 100.0; // Convert cents to dollars
            totalValue += value;

            std::cout << std::right << std::setw(5) << coin.denom << " |"
                      << std::right << std::setw(9) << coin.count << " |$"
                      << std::right << std::setw(6) << std::fixed << std::setprecision(2) << value << std::endl;
        }

        std::cout << "---------------------------\n";
        std::cout << "$ " << std::fixed << std::setprecision(2) << totalValue << std::endl;
    }
};*/

void MainMenu::abortProgram() {
    std::cout << "Aborting program...\n";
    exit(0);
}