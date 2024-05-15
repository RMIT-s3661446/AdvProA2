#ifndef READ_WRITE
#define READ_WRITE


#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.h"


class ReadWriter{
    public:
    static void loadFoodItems(LinkedList* list, std::string fileName);
    static void saveFoodItems(const LinkedList& list, const std::string& filename);
    //static void loadCoinInformation(Coin coins[], std::string fileName);
};



#endif