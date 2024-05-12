#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
}

void LinkedList::insertAtBeginning(FoodItem item){
    Node* newNode = new Node(item); //creates new node
    newNode -> next = head; //pushes the head
    head =  newNode; //designeates new node as the head

    //std::cout << "node added" << std::endl;
}

void LinkedList::insertAtEnd(FoodItem item){
    Node* newNode = new Node(item); //creates new node
    if (head == nullptr){ //if list is empty, makes the new node the head
        head = newNode;
    }

    else{
        Node* tempNode = head;
        while (tempNode -> next != nullptr){ //iterates throughout the list, until founds empty
            tempNode = tempNode -> next;
        }
        tempNode -> next = newNode;
    }
}



void LinkedList::insertInPosition(){
    //TODO
}

void LinkedList::deleteFromBeginning(){
    
    if (head != nullptr){
        Node* deletedNode = head;
        head = head -> next; //desigates next node as the head node
        delete deletedNode; //deletes first node
    }
    
    
}

void LinkedList::deleteFromEnd(){
    if (head != nullptr){
        if (head -> next == nullptr){
            delete head; //deletes head node
            head = nullptr; //designates null pointer as the head
        }
        else{
            Node* lastNode = head; 
            Node* deletedNode;
            while(lastNode -> next -> next != nullptr){ //starts looking for the second last node
                lastNode = lastNode -> next;
            }
            deletedNode = lastNode -> next; //designates the last node as the node to be deleted
            lastNode -> next = nullptr; //sets the null pointer to the last node
            delete deletedNode; //deletes from the memory
        }

    }
}

/*void LinkedList::deleteNode(Node *node)
{
    if (head != nullptr){
        Node* tempNode = head;
        Node* deletedNode;
        while(tempNode != nullptr){

        }
    }
}*/

void LinkedList::traverse(){
    Node* tempNode = head;
    while(tempNode != nullptr){
        std::cout << "ID: " << tempNode -> data.id 
        << " Name: " << tempNode -> data.name 
        << " Description: " << tempNode -> data.description
        << " Price: $" << tempNode -> data.Price << std::endl;
        tempNode = tempNode -> next;
    }
}

Node *LinkedList::searchByID(std::string itemID)
{
    Node* searchedNode = head;
    Node* returnNode = nullptr;
    while(searchedNode != nullptr){
        if (itemID == (searchedNode->data.id)){
            returnNode = searchedNode;
        }
        searchedNode = searchedNode -> next;
    }

    return returnNode;
}

int LinkedList::size()
{
    int size = 0;

    if (head != nullptr){
        Node* tempNode = head;
        while (tempNode != nullptr){
            size = size + 1;
            tempNode = tempNode -> next;
        }
    }

    return size;
}


void LinkedList::sortByName(){
    if (head != nullptr){
        for (int i = 0; i > size(); i++){
            
        }
    }
}


void LinkedList::clear()
{
    Node* current = head;
    Node* nextNode;

    while (current != nullptr){
        nextNode = current -> next;
        delete current;
        current = nextNode;
    }

    head = nullptr;

}

std::vector<FoodItem> LinkedList::returnFoodVector()
{
    std::vector<FoodItem> foodVector;
    
    if (head != nullptr){
        Node* tempNode = head;
        while (tempNode != nullptr){
            foodVector.push_back(tempNode ->data);
            tempNode = tempNode -> next;
        }
    }

    return foodVector;
}
