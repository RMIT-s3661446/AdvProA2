#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   count = 0;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
}

void LinkedList::insertAtBeginning(const FoodItem& item){
    Node* newNode = new Node(item); //creates new node
    newNode -> next = head; //pushes the head
    head =  newNode; //designeates new node as the head
    head -> next = nullptr;
    count += 1;
    //std::cout << "node added" << std::endl;
}

void LinkedList::insertAtEnd(const FoodItem& item){
    Node* newNode = new Node(item); //creates new node
    if (head == nullptr){ //if list is empty, makes the new node the head
        head = newNode;
        head -> next = nullptr;
        //std::cout << "Added " << head -> data.name << " at the start" << std::endl; 
    }

    else{
        Node* tempNode = head;
        while (tempNode -> next != nullptr){ //iterates throughout the list, until founds empty
            tempNode = tempNode -> next;
        }
        tempNode -> next = newNode;
        newNode -> next = nullptr;
        //std::cout << "Added " << tempNode -> data.name << " at the start" << std::endl; 
    }
    count += 1;

}

//method to get the next available ID
int LinkedList::getNextID() {
    if (head == nullptr) return 1; // Return the first ID if list is empty

    Node* current = head;
    int maxID = 0; // Variable to track the maximum ID found

    // Loop through all nodes to find the highest ID
    while (current != nullptr) {
        int currentID = std::stoi(current->data.id.substr(1)); // Assuming ID format 'Fxxxx'
        if (currentID > maxID) {
            maxID = currentID;
        }
        current = current->next;
    }
    return maxID + 1; // Return the next highest ID
}

void LinkedList::add(FoodItem item) {
    Node* newNode = new Node(item);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
 
}

void LinkedList::insertInPosition(){
    //TODO
}

void LinkedList::insertSorted(const FoodItem& item) {
    Node* newNode = new Node(item);
    Node* current;

    // Special case for the head end or an empty list
    if (head == nullptr || head->data.name >= item.name) {
        newNode->next = head;
        head = newNode;
    } else {
        // Locate the node before the point of insertion
        current = head;
        while (current->next != nullptr && current->next->data.name < item.name) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

void LinkedList::deleteFromBeginning(){
    
    if (head != nullptr){
        Node* deletedNode = head;
        head = head -> next; //desigates next node as the head node
        delete deletedNode; //deletes first node
        count -= 1;
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
            count -= 1;
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

void LinkedList::deleteByID(std::string ID)
{
    if (head != nullptr){
        Node* tempNode;
        Node* deletedNode = nullptr;

        if (head -> data.id == ID){
            deletedNode = head;
            tempNode = head -> next;
            delete deletedNode;
            head = tempNode;
        }
        else{
            tempNode = head;
            while (tempNode != nullptr && tempNode -> next != nullptr){
                if (tempNode -> next ->data.id == ID){
                    deletedNode = tempNode -> next;
                    tempNode -> next = tempNode -> next -> next;
                    delete deletedNode;
                }
                tempNode = tempNode -> next;
            }
        }  

    }
}

void LinkedList::traverse()
{
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
    //std::cout << head -> data.name << std::endl;
    return count;
}


void LinkedList::sortByName(){
    mergeSort(head);
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
            //std::cout << "Added " << tempNode -> data.name << "To the vector" << std::endl; 
            tempNode = tempNode -> next;
        }
    }

    return foodVector;
}

Node *LinkedList::mergeSort(Node *head)
{
    Node* result = nullptr;
    if (head == nullptr || head -> next == nullptr){
        result = head;
    }
    else {
        Node* slow = head;
        Node* fast = head -> next;
        while (fast != nullptr && fast -> next != nullptr){
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        Node* mid = slow -> next;
        slow -> next = nullptr;

        Node* left = mergeSort(head);
        Node* right = mergeSort(mid);

        result = merge(left, right);

        //return result;
    }
    
    
    return result;
}

Node *LinkedList::merge(Node *left, Node *right)
{
    Node* result = nullptr;

    if (left == nullptr){
        result = right;
    }
    else if (right == nullptr){
        result = left;
    }
    else if(left -> data.name <= right -> data.name){
        result = left;
        result -> next = merge(left -> next, right);
    }
    else if(right -> data.name <= left -> data.name){
        result = right;
        result -> next = merge (left, right -> next);
    }

    return result;
    
}
