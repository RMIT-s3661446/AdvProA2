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
            price = std::stod(priceLine) * 100;
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

void ReadWriter::loadCoinInformation(Coin coins[NUM_DENOMS], std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()){
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
    else{
        while (getline(file, line)){
            std::istringstream iss(line);
            std::string denom;
            int quantity;
            std::getline(iss, denom, (char)DELIM);
            iss >> quantity;

            switch (std::stoi(denom)){
                case 5:
                coins[0].denom = Coin::centsToCoin(5);
                coins[0].count = quantity;
                break;

                case 10:
                coins[1].denom = Coin::centsToCoin(10);
                coins[1].count = quantity;
                break;

                case 20:
                coins[2].denom = Coin::centsToCoin(20);
                coins[2].count = quantity;
                break;

                case 50:
                coins[3].denom = Coin::centsToCoin(50);
                coins[3].count = quantity;
                break;

                case 100:
                coins[4].denom = Coin::centsToCoin(100);
                coins[4].count = quantity;
                break;

                case 200:
                coins[5].denom = Coin::centsToCoin(200);
                coins[5].count = quantity;
                break;

                case 500:
                coins[6].denom = Coin::centsToCoin(500);
                coins[6].count = quantity;
                break;

                case 1000:
                coins[7].denom = Coin::centsToCoin(1000);
                coins[7].count = quantity;
                break;

                case 2000:
                coins[8].denom = Coin::centsToCoin(2000);
                coins[8].count = quantity;
                break;

                case 5000:
                coins[9].denom = Coin::centsToCoin(5000);
                coins[9].count = quantity;
                break;
            }
        }

        file.close();
    }
}
