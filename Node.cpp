#include "Node.h"



FoodItem::FoodItem(){

};

FoodItem::FoodItem(std::string id, std::string name, std::string description, int price){
    this -> id = id;
    this -> name = name;
    this -> description = description;
    this -> Price = price;
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

