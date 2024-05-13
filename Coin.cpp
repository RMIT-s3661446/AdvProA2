#include "Coin.h"
 

 int Coin::coinToCents(Denomination coinDenom){
    int cents = 0;


    /*if (coinDenom == FIVE_CENTS){
        cents = 5;
    }
    else if (coinDenom == TEN_CENTS){
        cents = 10;
    }
    else if (coinDenom == TWENTY_CENTS){
        cents = 20;
    }
    else if (coinDenom == FIFTY_CENTS){
        cents = 50;
    }
    else if (coinDenom == ONE_DOLLAR){
        cents = 100;
    }
    else if (coinDenom == TWO_DOLLARS){
        cents == 200;
    }
    else if (coinDenom == FIVE_DOLLARS){
        cents == 500;
    }
    else if (coinDenom == TEN_DOLLARS){
        cents == 1000;
    }
    else if (coinDenom == TWENTY_DOLLARS){
        cents == 2000;
    }*/


    return cents;
 }
 Denomination Coin::centsToCoin(int cents)
 {
    Denomination coinDenom;
    switch (cents){
        case 5:
        coinDenom = FIVE_CENTS;
        break;

        case 10:
        coinDenom = TEN_CENTS;
        break;

        case 20:
        coinDenom = TWENTY_CENTS;
        break;

        case 50:
        coinDenom = FIFTY_CENTS;
        break;

        case 100:
        coinDenom = ONE_DOLLAR;
        break;

        case 200:
        coinDenom = TWO_DOLLARS;
        break;

        case 500:
        coinDenom = FIVE_DOLLARS;
        break;

        case 1000:
        coinDenom = TEN_DOLLARS;
        break;

        case 2000:
        coinDenom = TWENTY_DOLLARS;
        break;

        case 5000:
        coinDenom = FIFTY_DOLLARS;
        break;

        
        default:
        coinDenom = FIVE_CENTS;
        break;

    }

    return coinDenom;
    
 }
 // implement functions for managing coins; this may depend on your design.
