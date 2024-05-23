#include "ReadWriter.h"
// Load food items from a file and insert them into the linked list
void ReadWriter::loadFoodItems(LinkedList *list, std::string fileName)
{
    // Open the file for reading
    std::ifstream file(fileName);
    std::string line;
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
    else{
 // Read each line from the file
    while (getline(file, line)) {
        try
        {
            // Create a string stream from the line
            std::istringstream iss(line);
            std::string id, name, description;
            std::string priceLine;
            double price;
            // Extract id, name, description, and price from the line
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

         // Insert the item into the list if it meets the criteria
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
    // Close the file
    file.close();
    }
}
// Save food items from the linked list to a file
void ReadWriter::saveFoodItems(LinkedList *list, const std::string &filename)
{
    // Open the file for writing (truncate the file if it exists)
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
    }
    else{

    
    //file << list.toString();
    // Traverse the list and write each food item to the file
    Node* currNode = list -> getHead();
    while(currNode != nullptr){
        FoodItem currItem = currNode -> data;
        file << currItem.id + "|" + currItem.name + "|" + currItem.description + "|" << currItem.Price << std::endl;
        currNode = currNode -> next;
    }
    }

    // Close the file
    file.close();

}

// Save coin balances to a file
void ReadWriter::saveCoins(const std::string &filename){
    // Open the file for writing (truncate the file if it exists)
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
    // Check if the file opened successfully
    if (!file.is_open()){}
    else{
     // Iterate through the denomination values in reverse order and write to the file
    for (auto it = DenominationValues.rbegin(); it != DenominationValues.rend(); it++){
        file << it -> second << "," << CoinManager::getInstance().getBalance(it -> first) << std::endl;
    }
        // Close the file
        file.close();
    }
}
// Load coin balances from a file
void ReadWriter::loadCoins(std::string fileName)
{
    // Open the file for reading
    std::ifstream file(fileName);
    std::string line;
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
    else{
        // Read each line from the file
    while (getline(file, line)) {
        try
            {
                // Create a string stream from the line
                std::istringstream iss(line);
                std::string denomString, quantString;
            //int denom, quantity;
            // Extract denomination and quantity from the line
                std::getline(iss, denomString, ',');
                std::getline(iss, quantString);

                try
                {
                    // Iterate through the denomination values and add coins to the CoinManager
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

        
            
            }
            catch(const std::exception& e)
            {
            //std::cerr << "invalid item" << std::endl;
            //std::cerr << e.what() << std::endl;
            }
        

        }
     // Close the file
        file.close();
    }
}
