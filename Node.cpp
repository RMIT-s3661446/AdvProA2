#include "Node.h"




// Default constructor for FoodItem
FoodItem::FoodItem(){

};
// Parameterised constructor for FoodItem
FoodItem::FoodItem(std::string id, std::string name, std::string description, double price){
    // Initialize member variables with provided values
    this -> id = id;
    this -> name = name;
    this -> description = description;
    this -> Price = price;
     // Set default stock level
    on_hand = DEFAULT_FOOD_STOCK_LEVEL;
}
// Destructor for FoodItem
FoodItem::~FoodItem(){

}

// Default constructor for Node
Node::Node(){
    // TODO
};

// Parameterised constructor for Node with a FoodItem
Node::Node(FoodItem item){
    // Initialise data member with the provided FoodItem
    data = item;
};
// Destructor for Node
Node::~Node(){
    //delete data;
};

