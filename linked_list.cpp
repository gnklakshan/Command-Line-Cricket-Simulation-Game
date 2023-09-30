#include "linked_list.h"

// Function Definitions----------------------------------------------------------------
void LinkList::add(int num_node)
{
    if (num_node == 0)
    {
        start = nullptr;
    }
    else
    {
        // start->data=1;
        Node* TEMP = NULL;
        for (int i = 1; i <= num_node; i++)
        {
            Node* node = new Node;
            node->data = i;
            node->data = (i - 1);
            //cout << "Enter element " << i << " in the list : ";
            //cin >> node->data;

            if (i == 1)
            {
                node->next = NULL;
                node->prev = nullptr;
                start = node;
            }
            else
            {
                TEMP->next = node;
                node->prev = TEMP;
                node->next = nullptr;
            }
            TEMP = node;
        }
    }
}

int LinkList::printfirstelement()
{
    Node* temp;
    if (start == nullptr)
        return -1;
    else
    {
        return start->data;
    }
}

void LinkList::insertBeg(int x)
{
    Node* node = new Node;
    node->data = x;
    if (start == nullptr)
    {
        node->prev = nullptr;
        node->next = nullptr;
        start = node;
    }
    else
    {
        node->prev = nullptr;
        node->next = start;
        start->prev = node;
        start = node;
    }
}

int LinkList::deleteBeg()
{
    int value;
    if (start == nullptr)
        return -1;
    else if (start->next == nullptr)
    {
        value = start->data;
        Node* temp = start;
        delete temp;
        start = nullptr;
    }
    else
    {
        value = start->data;
        Node* temp = start->next;
        temp->prev = nullptr;
        start->next = nullptr;
        delete start;
        start = temp;
    }
    return value;
}
