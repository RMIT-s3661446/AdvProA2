#ifndef MENU_H
#define MENU_H

#include "LinkedList.h"
#include "LinkedList.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>


class MainMenu {
    public:

    MainMenu();
    MainMenu(LinkedList* foodList);
    ~MainMenu();


    void displayMainMenu();
    bool handleMenuSelection(int option);
    void displayFoodMenu();
    void purchaseMeal();
    void addFood();
    void removeFood();
    void displayBalance();
    void abortProgram();

    bool hasQuit;
    int userChoice;
    LinkedList* foodList;
    Coin coins[];




    //*************************
    void menuStart();
    void menuDisplay();
    void menuPurchase();

    void adminAdd();
    void adminRemove();
    void adminDisplayBalance();
    void adminAbort();
};





#endif