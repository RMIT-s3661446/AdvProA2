#include "LinkedList.h"
#include <iostream>
// Default constructor for LinkedList
LinkedList::LinkedList() {
   head = nullptr;
   count = 0;

 
}
// Destructor for LinkedList
LinkedList::~LinkedList() {
}
// Insert a FoodItem at the beginning of the list
void LinkedList::insertAtBeginning(const FoodItem& item){
    //creates new node
    Node* newNode = new Node(item); 
    //pushes the head
    newNode -> next = head; 
    //designeates new node as the head
    head =  newNode; 
    // Ensure the head node's next is nullptr
    head -> next = nullptr;
     // Increment the count
    count += 1;
}

// Insert a FoodItem at the end of the list
void LinkedList::insertAtEnd(const FoodItem& item){
   //creates new node
    Node* newNode = new Node(item); 
   //if list is empty, makes the new node the head
    if (head == nullptr){ 
        head = newNode;
        head -> next = nullptr;
    }

    else{
        // Iterate through the list to find the last node
        Node* tempNode = head;
        while (tempNode -> next != nullptr){ 
            tempNode = tempNode -> next;
        }
        // Set the last node's next to the new node
        tempNode -> next = newNode;
        newNode -> next = nullptr;
        //std::cout << "Added " << tempNode -> data.name << " at the start" << std::endl; 
    }
    // Increment the count
    count += 1;

}

//method to get the next available ID
int LinkedList::getNextID() {
    // Return the first ID if list is empty
    if (head == nullptr) return 1;

    Node* current = head;
   // Variable to track the maximum ID found
    int maxID = 0; 

    // Loop through all nodes to find the highest ID
    while (current != nullptr) {
        int currentID = std::stoi(current->data.id.substr(1)); 
        if (currentID > maxID) {
            maxID = currentID;
        }
        current = current->next;
    }
    // Return the next highest ID
    return maxID + 1; 
}

// Add a FoodItem to the end of the list
void LinkedList::add(FoodItem item) {
    // Create a new node with the given item
    Node* newNode = new Node(item);
    // Check if the list is empty
    if (head == nullptr) {
        // Set the new node as the head
        head = newNode;
    } else {
        // Iterate through the list to find the last node
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
         // Set the last node's next to the new node
        current->next = newNode;
    }
    // Increment the count
    count++;
 
}

void LinkedList::insertInPosition(){
    //TODO
}

// Insert a FoodItem in a sorted order based on name
void LinkedList::insertSorted(const FoodItem& item) {
     // Create a new node with the given item
    Node* newNode = new Node(item);
    Node* current;

    // Special case for the head end or an empty list
    if (head == nullptr || head->data.name >= item.name) {
         // Set the new node's next to the current head
        newNode->next = head;
         // Set the new node as the head
        head = newNode;
    } else {
        // Locate the node before the point of insertion
        current = head;
        while (current->next != nullptr && current->next->data.name < item.name) {
            current = current->next;
        }
           // Insert the new node in the correct position
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

void LinkedList::deleteFromBeginning(){
    
    if (head != nullptr){
        Node* deletedNode = head;
       //desigates next node as the head node
        head = head -> next; 
       //deletes first node
        delete deletedNode; 
        // Decrement the count
        count -= 1;
    }
    
    
}

void LinkedList::deleteFromEnd(){
    if (head != nullptr){
        if (head -> next == nullptr){
            //deletes head node
            delete head; 
            //designates null pointer as the head
            head = nullptr; 
        }
        else{
            Node* lastNode = head; 
            Node* deletedNode;
           //starts looking for the second last node
            while(lastNode -> next -> next != nullptr){ 
                lastNode = lastNode -> next;
            }
         //designates the last node as the node to be deleted
            deletedNode = lastNode -> next; 
         //sets the null pointer to the last node
            lastNode -> next = nullptr; 
         //deletes from the memory
            delete deletedNode; 
         // Decrement the count
            count -= 1;
        }

    }
}


void LinkedList::deleteByID(std::string ID)
{
    // Check if the list is not empty
    if (head != nullptr){
        Node* tempNode;
        Node* deletedNode = nullptr;
        // Check if the head node is the one to delete
        if (head -> data.id == ID){
            deletedNode = head;
            // Move to the next node
            tempNode = head -> next; 
            // Delete the head node
            delete deletedNode;
            // Update the head to the next node
            head = tempNode;
        }
        else{
            // Iterate to find the node with the given ID
            tempNode = head;
            while (tempNode != nullptr && tempNode -> next != nullptr){
                if (tempNode -> next ->data.id == ID){
                     // Node to be deleted
                    deletedNode = tempNode -> next;
                    // Bypass the deleted node
                    tempNode -> next = tempNode -> next -> next;
                    // Delete the node
                    delete deletedNode;
                }
                // Move to the next node
                tempNode = tempNode -> next;
            }
        }  

    }
}

// Traverse the list and print the data of each node
void LinkedList::traverse()
{
    // Start from the head node
    Node* tempNode = head; 
    while(tempNode != nullptr){
        std::cout << "ID: " << tempNode -> data.id 
        << " Name: " << tempNode -> data.name 
        << " Description: " << tempNode -> data.description
        << " Price: $" << tempNode -> data.Price << std::endl;
      // Move to the next node
        tempNode = tempNode -> next;
    }
}

Node *LinkedList::searchByID(std::string itemID)
{
    // Start from the head node
    Node* searchedNode = head;
    // Pointer to the node to be returned
    Node* returnNode = nullptr;
    // Iterate through the list to find the node with the given ID
    while(searchedNode != nullptr){
        if (itemID == (searchedNode->data.id)){
            returnNode = searchedNode;
        }
        searchedNode = searchedNode -> next;
    }
     // Return the found node or nullptr
    return returnNode;
}

// Return the size of the list
int LinkedList::size()
{
    //std::cout << head -> data.name << std::endl;
    return count;
}

// Sort the list by the name of the FoodItem
void LinkedList::sortByName(){
    // Sort the list using merge sort
    mergeSort(head);
}

// Get the head node of the list
Node *LinkedList::getHead()
{
    // Return the head node
    return head;
}


// Clear the entire list
void LinkedList::clear()
{
    // Start from the head node
    Node* current = head;
    // Pointer to the next node
    Node* nextNode;

    // Iterate through the list and delete each node
    while (current != nullptr){
        // Store the next node
        nextNode = current -> next;
        // Delete the current node
        delete current;
        // Move to the next node
        current = nextNode;
    }
    // Set head to nullptr
    head = nullptr;

}

// Return a vector of FoodItems from the list
std::vector<FoodItem> LinkedList::returnFoodVector()
{
     // Vector to store FoodItems
    std::vector<FoodItem> foodVector;
     // Iterate through the list and add each FoodItem to the vector
    if (head != nullptr){
        // Start from the head node
        Node* tempNode = head;
        while (tempNode != nullptr){
            // Add the FoodItem to the vector
            foodVector.push_back(tempNode ->data);
             // Move to the next node
            tempNode = tempNode -> next;
        }
    }
    // Return the vector of FoodItems
    return foodVector;
}

// Merge sort the list
Node *LinkedList::mergeSort(Node *head)
{
    // Pointer to the sorted list
    Node* result = nullptr;
     // Check if the list is empty or has only one node
    if (head == nullptr || head -> next == nullptr){
        // Return the head node if list is empty or single node
        result = head;
    }
    else {
        // Split the list into two halves
        // Slow pointer
        Node* slow = head;
        // Fast pointer
        Node* fast = head -> next;
        while (fast != nullptr && fast -> next != nullptr){
            // Move slow pointer one step
            slow = slow -> next;
            // Move fast pointer two steps
            fast = fast -> next -> next;
        }
        // Middle of the list
        Node* mid = slow -> next;
         // Split the list
        slow -> next = nullptr;

        // Recursively sort the two halves
        Node* left = mergeSort(head);
        Node* right = mergeSort(mid);

        // Merge the sorted halves
        result = merge(left, right);

        //return result;
    }
    
    // Return the sorted list
    return result;
}

// Merge two sorted lists
Node *LinkedList::merge(Node *left, Node *right)
{
     // Pointer to the merged list
    Node* result = nullptr;
    // Merge the nodes in sorted order
    if (left == nullptr){
        // If left is empty, return right
        result = right;
    }
    else if (right == nullptr){
        // If right is empty, return left
        result = left;
    }
    else if(left -> data.name <= right -> data.name){
         // If left node is smaller or equal, set result to left
        result = left;
        // Recursively merge the rest
        result -> next = merge(left -> next, right);
    }
    else if(right -> data.name <= left -> data.name){
        // If right node is smaller, set result to right
        result = right;
        // Recursively merge the rest
        result -> next = merge (left, right -> next);
    }
    // Return the merged list
    return result;
    
}
