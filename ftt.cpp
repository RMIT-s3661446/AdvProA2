#include <iostream>
#include <fstream>
#include <sstream>

#include "LinkedList.h"
#include "ReadWriter.cpp"
#include "MainMenu.h"

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

//void loadFoodItems(LinkedList* list, std::string fileName);



int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO
    
    //std::cout << "Just a test, nothing implemented yet!" << std::endl;
    LinkedList* foodList = new LinkedList();
    //Coin coins[NUM_DENOMS];
    
    MainMenu* menu = new MainMenu(foodList);
    ReadWriter::loadFoodItems(foodList, argv[1]);

    //foodList -> traverse();
    //ReadWriter::loadCoinInformation(coins, "coins.dat");
    menu -> menuStart();
    //foodList.traverse();
    foodList -> clear();
    delete menu;
    delete foodList;
    return EXIT_SUCCESS;
}