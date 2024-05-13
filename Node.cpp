#include "Node.h"





FoodItem::FoodItem(){

};

FoodItem::FoodItem(std::string id, std::string name, std::string description, double price){
    this -> id = id;
    this -> name = name;
    this -> description = description;
    this -> Price = price;
    on_hand = DEFAULT_FOOD_STOCK_LEVEL;
}

FoodItem::~FoodItem(){

}



Node::Node(){
    // TODO
};

Node::Node(FoodItem item){
    data = item;
};

Node::~Node(){
    // TODO
};

