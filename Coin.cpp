#include "Coin.h"
#include <cmath>


// Add a specified number of coins of a given denomination to the coin manager
void CoinManager::addCoin(Denomination denom, unsigned num) {
    coins[denom] += num;
}

// Subtract a specified number of coins of a given denomination from the coin manager
// Returns false if there aren't enough coins of that denomination
bool CoinManager::subtractCoin(Denomination denom, unsigned num) {
    if (coins[denom] < num) return false;
    coins[denom] -= num;
    return true;
}

// Check if the coin manager can provide the exact change for a given amount
bool CoinManager::canProvideChange(double amount) {
    int cents = amount * 100;
    auto backup = coins;
    
     // Iterate through the denominations from largest to smallest
    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); ++it) {
        while (cents >= it->second && coins[it->first] > 0) {
            cents -= it->second;
            coins[it->first]--;
        }
    }
     // Restore the original state of the coins
    coins = backup;

    // Return true if exact change can be provided, otherwise false
    return cents == 0;
}

// Get the exact change for a given amount
// Returns a vector of pairs representing the denominations and their counts
std::vector<std::pair<Denomination, unsigned>> CoinManager::getChange(double amount) {
    std::vector<std::pair<Denomination, unsigned>> change;
    int cents = static_cast<int>(round(amount * 100));
     // Iterate through the denominations from largest to smallest
    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); it++) {
        unsigned count = 0;
        while (cents >= it->second && coins[it->first] > 0) {
            cents -= it->second;
            coins[it->first]--;
            std::cout << coins[it -> first] << std::endl;
            count++;
        }
        if (count > 0) {
            change.push_back({it->first, count});
        }
    }
    
    // If unable to provide exact change, rollback and clear the change vector
    if (cents > 0) {
        for (auto& ch : change) {
            coins[ch.first] += ch.second;
        }
        change.clear();
    }
    return change;
}


// Check if a given value in cents is a valid denomination
bool CoinManager::isValidDenomination(int cent) {
    for (const auto& pair : DenominationValues) {
        if (pair.second == cent) return true;
    }
    return false;
}

// Simulate refunding the total amount received
void CoinManager::refund(double totalReceived) {
    std::cout << "Refunding $" << totalReceived << std::endl;
    // Here you would typically add logic to return coins
}

void CoinManager::refund(double totalReceived) {
    std::cout << "Refunding $" << totalReceived << std::endl;
    // Here you would typically add logic to return coins
}


// Provide change for a given amount
// Returns false if exact change cannot be provided
bool CoinManager::provideChange(double change) {
    auto changes = getChange(change);
    if (changes.empty()) {
        return false;
    }
     // Print out the change provided
    std::cout << "Your change is: ";
    for (const auto& ch : changes) {
        int denomValue = DenominationValues.at(ch.first);
        int dollars = denomValue / 100;
        int cents = denomValue % 100;
        if (cents == 0){
            std::cout << ch.second << "x " << dollars << " dollar(s) ";
        }
        else if (cents >= 1){
            std::cout << ch.second << "x " << cents << " cent(s) ";
        }
        
        //std::cout << denomValue / 100 << " dollar(s) " << denomValue % 100 << " cent(s) ";
    }
    //std::cout << dollars << " dollar(s) " << cents % 100 << " cent(s) ";
    std::cout << std::endl;
    return true;
}

// Get the balance of a specific denomination
int CoinManager::getBalance(Denomination denom){
    return (int) coins[denom];
}
