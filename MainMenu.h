#ifndef MENU_H
#define MENU_H


class MainMenu {
    public:

    MainMenu();
    ~MainMenu();
    
    void menuStart();
    void menuDisplay();
    void menuPurchase();

    void adminAdd();
    void adminRemove();
    void adminDisplayBalance();
    void adminAbort();
};





#endif