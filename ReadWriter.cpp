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
        std::istringstream iss(line);
        std::string id, name, description;
        double price;
        std::getline(iss, id, '|');
        //std::cout << id << ",";
        std::getline(iss, name, '|');
        //std::cout << name << ",";
        std::getline(iss, description, '|');
        //std::cout << description << ",";
        iss >> price;
        //std::cout << price << std::endl;

        // Assuming there is a method to create and insert a node directly
        list -> insertAtEnd(FoodItem(id,name,description,price));
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
