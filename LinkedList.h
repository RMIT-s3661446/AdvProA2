#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <vector>


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    int getNextID();  //  method to get the next available ID
    void add(FoodItem item);

    //Insertion functions
    void insertAtBeginning(const FoodItem& item);
    void insertAtEnd(const FoodItem& item);
    void insertInPosition();
    void insertSorted(const FoodItem& item);

    void deleteFromBeginning();
    void deleteFromEnd();
    void deleteFromPostion();
    void deleteNode(Node* node);
    void deleteByID(std::string ID);

    void traverse();

    void sortByName();

    Node* searchByID(std::string item);

    int size();
    bool isEmpty();
    Node* getHead();
    void clear();

    std::vector<FoodItem> returnFoodVector();

    

private:
    // the beginning of the list
    Node* head;

    Node* mergeSort(Node* head);
    Node* merge(Node* left, Node* right);


  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


