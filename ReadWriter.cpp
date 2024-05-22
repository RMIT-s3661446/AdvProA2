#include "ReadWriter.h"

void ReadWriter::loadFoodItems(LinkedList *list, std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
    else{

    while (getline(file, line)) {
        try
        {
            std::istringstream iss(line);
            std::string id, name, description;
            std::string priceLine;
            double price;
            std::getline(iss, id, '|');
        //std::cout << id << ",";
            std::getline(iss, name, '|');
        //std::cout << name << ",";
            std::getline(iss, description, '|');
        //std::cout << description << ",";
            //iss >> price;
            std::getline(iss, priceLine);
            price = std::stod(priceLine);
        //std::cout << price << std::endl;

        // Assuming there is a method to create and insert a node directly
            if (id[0] == 'F' && id.size() == IDLEN && name.size() <= NAMELEN && description.size() <= DESCLEN){
                list -> insertSorted(FoodItem(id,name,description,price));
            }
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "invalid item" << std::endl;
            std::cerr << e.what() << std::endl;
        }
        

    }

    file.close();
    }
}

void ReadWriter::saveFoodItems(LinkedList *list, const std::string &filename)
{
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
    }
    else{

    
    //file << list.toString();

    Node* currNode = list -> getHead();
    while(currNode != nullptr){
        FoodItem currItem = currNode -> data;
        file << currItem.id + "|" + currItem.name + "|" + currItem.description + "|" << currItem.Price << std::endl;
        currNode = currNode -> next;
    }
    }


    file.close();

}


void ReadWriter::saveCoins(const std::string &filename){
    
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()){

    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); it++){
        file << it -> second << "," << CoinManager::getInstance().getBalance(it -> first) << std::endl;
    }
    }
}

void ReadWriter::loadCoins(std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
    else{

    while (getline(file, line)) {
        try
            {
                std::istringstream iss(line);
                std::string denomString, quantString;
            //int denom, quantity;
                std::getline(iss, denomString, ',');
                std::getline(iss, quantString);

                try
                {
                    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); it++) {
                        if (std::stoi(denomString) == it -> second){
                            CoinManager::getInstance().addCoin(it->first, std::stoi(quantString));
                        }
                    }
                }
            
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            


        //std::cout << price << std::endl;

        // Assuming there is a method to create and insert a node directly
            
            }
            catch(const std::exception& e)
            {
            //std::cerr << "invalid item" << std::endl;
            //std::cerr << e.what() << std::endl;
            }
        

        }

        file.close();
    }
}
