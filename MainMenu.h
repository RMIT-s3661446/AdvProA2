#ifndef MENU_H
#define MENU_H

#include "LinkedList.h"
#include "LinkedList.h"


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