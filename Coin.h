#ifndef COIN_H
#define COIN_H

#include <vector>
#include <map>
#include <iostream>

// Keeping the original enum structure
enum Denomination {
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS, TWENTY_DOLLARS, FIFTY_DOLLARS
};

// Maps enum to its value in cents
/*static const std::map<Denomination, int> DenominationValues = {
    {FIFTY_DOLLARS, 5000}, {TWENTY_DOLLARS, 2000}, {TEN_DOLLARS, 1000}, 
    {FIVE_DOLLARS, 500}, {TWO_DOLLARS, 200}, {ONE_DOLLAR, 100}, {FIFTY_CENTS, 50},
    {TWENTY_CENTS, 20}, {TEN_CENTS, 10}, {FIVE_CENTS, 5}
};*/

// Map linking each denomination to its value in cents
static const std::map<Denomination, int> DenominationValues = {
    {FIVE_CENTS, 5}, {TEN_CENTS, 10}, {TWENTY_CENTS, 20}, {FIFTY_CENTS, 50},
    {ONE_DOLLAR, 100}, {TWO_DOLLARS, 200}, {FIVE_DOLLARS, 500},
    {TEN_DOLLARS, 1000}, {TWENTY_DOLLARS, 2000}, {FIFTY_DOLLARS, 5000}
};

static const std::map<int, Denomination> CoinValues = {
    {5, FIVE_CENTS}, {10, TEN_CENTS}, {20, TWENTY_CENTS}, {50, FIFTY_CENTS},
    {100, ONE_DOLLAR}, {200, TWO_DOLLARS}, {500, FIVE_DOLLARS},
    {1000, TEN_DOLLARS}, {2000, TWENTY_DOLLARS}, {5000, FIFTY_DOLLARS}
};

// CoinManager class to manage coins
class CoinManager {
private:
    // Map to store the count of each denomination of coins
    std::map<Denomination, unsigned> coins;

public: 
    // Get the singleton instance of CoinManager
    static CoinManager& getInstance() {
        static CoinManager instance;
        return instance;
    }
   
    // Delete the copy constructor
    CoinManager(const CoinManager&) = delete;
     // Delete the assignment operator
   
    void operator=(const CoinManager&) = delete;
     // Add a specified number of coins of a given denomination to the coin manager
    
    void addCoin(Denomination denom, unsigned num);
    // Subtract a specified number of coins of a given denomination from the coin manager
    // Returns false if there aren't enough coins of that denomination
    bool subtractCoin(Denomination denom, unsigned num);
    
    // Check if the coin manager can provide the exact change for a given amount
    bool canProvideChange(double amount);
    
    // Get the exact change for a given amount
    // Returns a vector of pairs representing the denominations and their counts
    std::vector<std::pair<Denomination, unsigned>> getChange(double amount);
   
    // Check if a given value in cents is a valid denomination
    bool isValidDenomination(int cent);
    
    // Simulate refunding the total amount received
    void refund(double totalReceived);
    
    // Provide change for a given amount
    // Returns false if exact change cannot be provided
    bool provideChange(double change);
    
    // Get the balance of a specific denomination
    int getBalance(Denomination denom);

private:
    // Private constructor to prevent instantiation
    CoinManager() {}
};

#endif // COIN_H