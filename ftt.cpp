#include <iostream>
#include "LinkedList.h"
//#include "MainMenu.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/



 //commit check sign your name here and commit:
//Mikhail Vasilchenko -1.0
//Filip Filiposki -2
//I am testing too// Whetever
//Patrick Leonello -3 lwdoakdoadoaod
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO


    

    std::cout << "Just a test, nothing implemented yet!" << std::endl;



    /*LinkedList foodList;

    foodList.insertAtBeginning(FoodItem("002", "Burek", "hjkfhdkf", 5));
    foodList.insertAtEnd(FoodItem("003", "Chevapi", "hjkfhdkf", 3));
    foodList.insertAtBeginning(FoodItem("001", "Borscht", "hjkfhdkf", 2));
    foodList.traverse();*/
    //MainMenu::menuStart();
    return EXIT_SUCCESS;
}

/*
// possible Data Handling. Loading, Reading, and Writing Data was confused so i keep comment for feedback
void loadFoodItems(LinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, description;
        double price;
        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        std::getline(iss, description, '|');
        iss >> price;

        // Assuming there is a method to create and insert a node directly
        list.insert(id, name, description, price);
    }

    file.close();
}

void saveFoodItems(const LinkedList& list, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Assuming `toString` method that returns all nodes' data as string formatted as required
    file << list.toString();

    file.close();
}


int main() {
    LinkedList foodItems;
    loadFoodItems(foodItems, "foods.dat");
    // other operations
    saveFoodItems(foodItems, "foods.dat");
    return 0;
}
*/