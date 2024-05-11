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
    
    if (head != nullptr){
        Node* deletedNode = head;
        head = head -> next;
        delete deletedNode;
    }
    
    
}

void LinkedList::deleteFromEnd(){
    if (head != nullptr){
        Node* lastNode = head;
        Node* deletedNode = head;
        while(lastNode -> next -> next != nullptr){
            lastNode = lastNode -> next;
        }
        deletedNode = lastNode -> next;
        lastNode -> next = nullptr;
        delete deletedNode;
    }
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
