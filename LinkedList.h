#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...

    //Insertion functions
    void insertAtBeginning(FoodItem item);
    void insertAtEnd(FoodItem item);
    void insertInPosition();

    void deleteFromBeginning();
    void deleteFromEnd();
    void deleteFromPostion();
    void deleteNode(Node* node);

    void traverse();

    Node* searchByID(std::string item);

    int size();
    bool isEmpty();
    Node* getHead();
    void clear();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


