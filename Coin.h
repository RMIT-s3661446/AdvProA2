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
static const std::map<Denomination, int> DenominationValues = {
    {FIVE_CENTS, 5}, {TEN_CENTS, 10}, {TWENTY_CENTS, 20}, {FIFTY_CENTS, 50},
    {ONE_DOLLAR, 100}, {TWO_DOLLARS, 200}, {FIVE_DOLLARS, 500},
    {TEN_DOLLARS, 1000}, {TWENTY_DOLLARS, 2000}, {FIFTY_DOLLARS, 5000}
};

class CoinManager {
private:
    std::map<Denomination, unsigned> coins;

public:
    

    static CoinManager& getInstance() {
        static CoinManager instance;
        return instance;
    }

    CoinManager(const CoinManager&) = delete;
    void operator=(const CoinManager&) = delete;

    void addCoin(Denomination denom, unsigned num);
    bool subtractCoin(Denomination denom, unsigned num);
    bool canProvideChange(double amount);
    std::vector<std::pair<Denomination, unsigned>> getChange(double amount);
    bool isValidDenomination(int cent);
    void refund(double totalReceived);
    bool provideChange(double change);

    int getBalance(Denomination denom);

private:
    CoinManager() {}
};

#endif // COIN_H