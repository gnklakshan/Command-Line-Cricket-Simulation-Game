#include <iostream>
#include <stdlib.h>
using namespace std;

// Declare Node----------------------------------------------------------------
struct Node
{
    int data;
    Node* next;
    Node* prev;
};

// Declare Link list----------------------------------------------------------------
class LinkList
{
private:
    Node* start;

public:
    void add(int num_node);
    int printfirstelement();          // Print first element
    void insertBeg(int x); // Insert a new node at the beginning
    int deleteBeg();      // Delete a node from the beginning

};
