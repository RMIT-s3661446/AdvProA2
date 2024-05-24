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





int main(int argc, char **argv)
{
    MainMenu* menu = new MainMenu(argv[1], argv[2]);
    menu -> menuStart();
    delete menu;

    return EXIT_SUCCESS;
}