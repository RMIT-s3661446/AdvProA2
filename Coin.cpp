#include "Coin.h"
#include <cmath>



void CoinManager::addCoin(Denomination denom, unsigned num) {
    coins[denom] += num;
}

bool CoinManager::subtractCoin(Denomination denom, unsigned num) {
    if (coins[denom] < num) return false;
    coins[denom] -= num;
    return true;
}

bool CoinManager::canProvideChange(double amount) {
    int cents = amount * 100; //static_cast<int>(round(amount * 100));
    auto backup = coins;
    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); ++it) {
        while (cents >= it->second && coins[it->first] > 0) {
            cents -= it->second;
            coins[it->first]--;
        }
    }
    coins = backup;
    //std::cout<< "DEBUG: " << cents << std::endl;
    return cents == 0;
}

std::vector<std::pair<Denomination, unsigned>> CoinManager::getChange(double amount) {
    std::vector<std::pair<Denomination, unsigned>> change;
    int cents = static_cast<int>(round(amount * 100));
    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); it++) {
        unsigned count = 0;
        while (cents >= it->second && coins[it->first] > 0) {
            cents -= it->second;
            coins[it->first]--;
            count++;
        }
        if (count > 0) {
            change.push_back({it->first, count});
        }
    }
    if (cents > 0) {
        // Unable to provide exact change, rollback
        for (auto& ch : change) {
            coins[ch.first] += ch.second;
        }
        change.clear();
    }
    return change;
}

bool CoinManager::isValidDenomination(int cent) {
    for (const auto& pair : DenominationValues) {
        if (pair.second == cent) return true;
    }
    return false;
}

void CoinManager::refund(double totalReceived) {
    std::cout << "Refunding $" << totalReceived << std::endl;
    // Here you would typically add logic to return coins
}

bool CoinManager::provideChange(double change) {
    auto changes = getChange(change);
    if (getChange(change).empty()) {
        return false;
    }
    std::cout << "Your change is: ";
    for (const auto& ch : changes) {
        int denomValue = DenominationValues.at(ch.first);
        std::cout << denomValue / 100 << " dollar(s) " << denomValue % 100 << " cent(s) ";
    }
    std::cout << std::endl;
    return true;
}