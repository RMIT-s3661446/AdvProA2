#include "MainMenu.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



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
}

void MainMenu::menuStart()
{
    do{
        displayMainMenu();
        std::cin >> userChoice;
        handleMenuSelection(userChoice);

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
    foodList->add(newFood);

    // Confirmation message
    std::cout << "This item \"" << name << " - " << description
              << "\" has now been added to the food menu with ID " << idStream.str() << std::endl;
}


void MainMenu::removeFood() {
    // Placeholder function for removing a food
    std::cout << "Remove Food - To be implemented\n";

    //debug line
    
    std::string foodID;
    std::cout << "Enter the ID of the food that you want to remove: ";
    std::cin >> foodID;

    foodList -> deleteByID(foodID);


}

void MainMenu::displayBalance() {
    // Placeholder function for displaying balance
    std::cout << "Display Balance - To be implemented\n";

    for (int i = 0; i > NUM_DENOMS; i++){
        std::cout << "Line " << i + 1 << ". Value: " << Coin::coinToCents(coins[i].denom)
        << ". Count: " << coins[i].count << std::endl;
    }
}

void MainMenu::abortProgram() {
    std::cout << "Aborting program...\n";
    exit(0);
}