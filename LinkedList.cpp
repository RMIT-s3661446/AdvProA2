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
    Node* newNode = new Node(item);
    newNode -> next = head;
    head =  newNode;
}

void LinkedList::insertAtEnd(FoodItem item){
    Node* newNode = new Node(item);
    if (head == nullptr){
        head = newNode;
    }

    else{
        Node* tempNode = head;
        while (tempNode -> next != nullptr){
            tempNode = tempNode -> next;
        }
        tempNode -> next = newNode;
    }
}



void LinkedList::insertInPosition(){
    //TODO
}

void LinkedList::deleteFromBeginning(){

}


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





