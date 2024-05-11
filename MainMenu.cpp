#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::menuStart()
{
    std::cout << "Main Menu:" << std::endl
    << "  1. Display Meal Options" << std::endl
    << "  2. Purchase Meal" << std::endl
    << "  3. Save and Exit" << std::endl
    << "Adminstrator-Only Menu" << std::endl
    << "  4. Add Food" << std::endl
    << "  5. Remove Food" << std::endl
    << "  6. Display Balance" << std::endl
    << "  7. Abort Program" << std::endl
    << "Select your option: ";
}