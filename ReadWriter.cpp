#include "ReadWriter.h"

void ReadWriter::loadFoodItems(LinkedList *list, std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

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

void ReadWriter::saveFoodItems(const LinkedList &list, const std::string &filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Assuming `toString` method that returns all nodes' data as string formatted as required
    //file << list.toString();

    file.close();

}

/*void ReadWriter::loadCoins(std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    while (getline(file, line)) {
        try
        {
            std::istringstream iss(line);
            std::string denomString, quantString;
            int denom, quantity;
            std::getline(iss, denomString, ',');
            std::getline(iss, quantString);

            try
            {
                //CoinManager::getInstance().addCoin(DenominationValues.find(denom), );
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
            std::cerr << "invalid item" << std::endl;
            std::cerr << e.what() << std::endl;
        }
        

    }

    file.close();
}*/
