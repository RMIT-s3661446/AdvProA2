#include "MainMenu.h"
#include "LinkedList.h"
#include "ReadWriter.h"
#include <cctype>
// MainMenu default constructor
MainMenu::MainMenu()
{
    // Initialise hasQuit to false, userChoice to 0
    hasQuit = false;
    userChoice = 0;
}
// MainMenu constructor with parameters for foodFile and coinFile
MainMenu::MainMenu(std::string foodFile, std::string coinFile)
{
    // Assign foodFile and coinFile parameters to class members
    this->foodFile = foodFile;
    this->coinFile = coinFile;
    // Initialise foodList with a new LinkedList
    foodList = new LinkedList();
    // Load food items from foodFile into foodList
    ReadWriter::loadFoodItems(foodList, foodFile);
    // Load coins from coinFile
    ReadWriter::loadCoins(coinFile);
    hasQuit = false;
    userChoice = 0;
}
// MainMenu destructor
MainMenu::~MainMenu()
{
    foodList->clear();
    delete foodList;
    // Set foodList pointer to nullptr
    foodList = nullptr;
}
// Start the main menu loop
void MainMenu::menuStart()
{
    do
    {
        // Display the main menu
        displayMainMenu();
        // Get user input
        std::string userInput;
        std::getline(std::cin, userInput);
        try
        {
            // Convert user input to integer
            userChoice = std::stoi(userInput);
            // Handle the menu selection
            handleMenuSelection(userChoice);
        }
        catch (const std::exception &e)
        {
            // Display error message for invalid input
            std::cout << "Please enter a number for the option!!" << std::endl
                      << std::endl;
        }
    } while (hasQuit != true);
}

//******************************
// Display the main menu options
void MainMenu::displayMainMenu()
{
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
// Handle menu selection based on user input
bool MainMenu::handleMenuSelection(int option)
{
    if (option == 1)
    {
        // Display the food menu
        displayFoodMenu();
    }
    else if (option == 2)
    {
        // Handle meal purchase
        purchaseMeal();
    }
    else if (option == 3)
    {
        std::cout << "Saving and exiting.\n";
        // Exits the main loop
        hasQuit = true;
        // Save food items and coins to files
        ReadWriter::saveFoodItems(foodList, foodFile);
        ReadWriter::saveCoins(coinFile);
    }
    else if (option == 4)
    {
        // Add new food item
        addFood();
    }
    else if (option == 5)
    {
        // Remove a food item
        removeFood();
    }
    else if (option == 6)
    {
        // Display current balance
        displayBalance();
    }
    else if (option == 7)
    {
        // Abort the program
        abortProgram();
    }
    else
    {
        // Display invalid selection message
        std::cout << "Invalid selection. Please try again.\n";
    }
    // Keeps the loop running
    return true;
}
// Display the food menu
void MainMenu::displayFoodMenu()
{

    std::cout << "Food Menu\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(6) << "ID" << "|"
              << std::setw(10) << "Name" << "|"
              << std::setw(70) << "Description" << "|"
              << std::right << std::setw(10) << "Price" << "\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    // Retrieve food items from the list
    std::vector<FoodItem> foodVector = foodList->returnFoodVector();
    for (const auto &item : foodVector)
    {
        // Format the description to fit within 70 characters
        std::string description = item.description.length() > 67 ? item.description.substr(0, 67) + "..." : item.description;
        // Display food item details
        std::cout << std::left << std::setw(6) << item.id << "|"
                  << std::setw(10) << item.name << "|"
                  << std::setw(70) << description << "|"
                  << std::right << std::fixed << std::setprecision(2) << std::setw(10) << item.Price << "\n";
    }
}

void MainMenu::purchaseMeal()
{
    std::string foodID;
    std::cout << "Please enter the ID of the food you wish to purchase:\n";
    // std::cin >> foodID;
    std::getline(std::cin, foodID);
    // Get the list of food items
    std::vector<FoodItem> foodMenu = foodList->returnFoodVector();
    // Search for the food item by ID
    Node *itemNode = foodList->searchByID(foodID);
    // Check if the item was found
    if (itemNode != nullptr)
    {
        // Get the food item
        FoodItem *item = &(itemNode->data);

        if (item->on_hand != 0)
        {
            // Display selected food details
            std::cout << "You have selected \"" << item->name << " - " << item->description << "\". This will cost you $ " << item->Price << ".\n";
            std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
            std::cout << "Please enter 'enter' on a new line to cancel this purchase.\n";

            // Handle payment
            double totalReceived = 0;
            double amountDue = item->Price;
            int inputCent;
            std::string userInput;
            bool validInput = true;
            bool purchaseCancelled = false;
            // Loop to process payment until the amount due is covered or purchase is cancelled
            while (totalReceived < amountDue && !purchaseCancelled)
            {
                try
                {
                    std::cout << "You still need to give us $" << amountDue - totalReceived << ": ";
                    std::getline(std::cin, userInput);
                    if (userInput == "")
                    {
                        // Set flag if the user cancels the purchase
                        purchaseCancelled = true;
                    }
                    else
                    {
                        // Convert user input to integer
                        inputCent = std::stoi(userInput);
                        // Check if the input is a valid denomination
                        validInput = CoinManager::getInstance().isValidDenomination(inputCent);
                        if (!validInput)
                        {
                            std::cout << "Error: invalid denomination encountered.\n";
                        }
                        else
                        {
                            // Add the received amount to totalReceived
                            totalReceived += inputCent / 100.0;
                            // Find the coin value and add it to CoinManager
                            auto it = CoinValues.find(inputCent);
                            CoinManager::getInstance().addCoin(it->second, 1);
                        }
                    }
                }
                catch (const std::exception &e)
                {
                    // std::cerr << e.what() << '\n';
                }
            }
            // Check if purchase was not cancelled
            if (!purchaseCancelled)
            {
                // Calculate change if overpaid
                double change = totalReceived - amountDue;
                if (change > 0)
                {
                    // Try to provide change
                    if (!CoinManager::getInstance().provideChange(change))
                    {
                        std::cout << "Unable to provide correct change. Transaction cancelled.\n";
                        CoinManager::getInstance().refund(totalReceived);
                        // Refund the total received amount
                    }
                    // Deduct one unit from the item's stock
                }
                item->on_hand = item->on_hand - 1;
                std::cout << "Thank you for your purchase!\n";
            }
            else
            {
                // Handle purchase cancellation
                std::cout << "Purchase cancelled" << std::endl;
                // Refund the total received amount
                CoinManager::getInstance().refund(totalReceived);
            }
        }
        else
        {
            std::cout << "Item is out of stock" << std::endl;
        }
    }
    else
    {
        // Handle case where item is not found
        std::cout << "No item found" << std::endl;
    }
}

void MainMenu::addFood()
{
    // Get input from user for the name
    std::cout << "Enter the item name: ";
    std::string name;
    std::getline(std::cin, name);
    // Convert the first character to uppercase
    if (!name.empty())
    {
        name[0] = std::toupper(name[0]);
    }
    // If name is empty return to the main menu
    if (name.size() != 0)
    {
        if (name.size() < NAMELEN)
        {

            // Get input from user for the description
            std::cout << "Enter the item description: ";
            std::string description;
            std::getline(std::cin, description);

            if (description != "")
            {

                if (description.size() < DESCLEN)
                {

                    std::cout << "Enter the price for this item (in dollars and cents, e.g., 5.25): ";
                    try
                    {
                        std::string userInput;
                        std::getline(std::cin, userInput);
                        if (userInput != "")
                        {
                            double price;
                            price = std::stod(userInput);

                            // Handle the ID formatting and price conversion
                            int nextID = foodList->getNextID();
                            std::stringstream idStream;
                            idStream << 'F' << std::setw(4) << std::setfill('0') << nextID;

                            name[0] = std::toupper(name[0]);

                            // Create and add a new FoodItem to the list
                            FoodItem newFood(idStream.str(), name, description, price);
                            foodList->insertSorted(newFood); // Used insertSorted to keep the list in order

                            // Confirmation message
                            std::cout << "This item \"" << name << " - " << description
                                      << "\" has now been added to the food menu with ID " << idStream.str() << std::endl;
                        }
                        else
                        {
                            std::cout << std::endl
                                      << "Returning to the main menu" << std::endl;
                        }
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << "Please enter the number" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Description is too long" << std::endl;
                }
            }
            else
            {
                std::cout << std::endl
                          << "Returning to the main menu" << std::endl;
            }
        }
        else
        {
            std::cout << "Name is too long" << std::endl;
        }
    }
    else
    {
        std::cout << std::endl
                  << "Returning to the main menu" << std::endl;
    }
}

void MainMenu::removeFood()
{
    std::string foodID;
    std::cout << "Enter the food ID of the food to remove from the menu: ";
    std::getline(std::cin, foodID);
    if (foodID != "")
    {
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer

        Node *itemNode = foodList->searchByID(foodID); // Utilizing searchByID to find the node
        if (itemNode != nullptr)
        {
            // Access the FoodItem data from the Node
            FoodItem *item = &itemNode->data;
            std::cout << "\"" << item->id << " - " << item->name << " - " << item->description
                      << "\" is being removed from the system." << std::endl;

            // Utilizing deleteByID to remove the item
            foodList->deleteByID(foodID);

            // No need to delete the FoodItem* as it is not dynamically allocated separately
        }
        else
        {
            std::cout << "No item found with ID " << foodID << std::endl;
        }
    }
    else
    {
        std::cout << "Returning to the main menu" << std::endl;
    }
}

void MainMenu::displayBalance()
{
    // Placeholder function for displaying balance
    // std::cout << "Display Balance - To be implemented\n";
    int total = 0;
    std::cout << std::setw(10) << std::left << "Denom" << " | " << std::setw(10) << std::left << "Quantity" << " | " << std::setw(10) << std::left << "Value" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    // Get a reverse iterator to the end of DenominationValues
    auto it = DenominationValues.rend();
    // Iterate through DenominationValues in reverse order
    while (it != DenominationValues.rbegin())
    {
        // Move iterator to the previous element
        it--;
        // Get the denomination value
        int denomValue = it->second;
        // Get the amount of the current denomination from CoinManager
        int amount = CoinManager::getInstance().getBalance(it->first);
        // Calculate the subtotal for the current denomination
        int subtotal = denomValue * amount;
        // Print the denomination, quantity, and value
        std::cout << std::setw(10) << std::left << denomValue << " | " << std::setw(10) << std::left << amount << " | " << "$" << std::setw(10) << std::fixed << std::left << std::setprecision(2) << ((double)subtotal) / 100 << std::endl;
        // Add the subtotal to the total
        total += subtotal;
    }

    std::cout << "-----------------------------------" << std::endl;
    // Print the total balance
    std::cout << std::setw(27) << std::right << "$" << std::right << std::fixed << std::setprecision(2) << ((double)total) / 100 << std::endl;
}

void MainMenu::abortProgram()
{
    std::cout << "Aborting program...\n";
    hasQuit = true;
    // exit(0);
}