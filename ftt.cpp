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
//Patrick Leonello -3 





int main(int argc, char **argv)
{

    //LinkedList* foodList = new LinkedList();
    MainMenu* menu = new MainMenu(argv[1], argv[2]);
    //ReadWriter::loadFoodItems(foodList, argv[1]);
    //ReadWriter::loadCoins("coins.dat");
    menu -> menuStart();
    //foodList -> clear();
    delete menu;
    //delete foodList;
    return EXIT_SUCCESS;
}