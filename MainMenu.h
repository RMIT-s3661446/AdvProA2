#ifndef MENU_H
#define MENU_H

#include "LinkedList.h"
#include "ReadWriter.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm> 


class MainMenu {
    public:

    MainMenu();
    MainMenu(std::string foodFile, std::string coinFile);
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
    std::string foodFile;
    std::string coinFile;
    //Coin coins[];




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