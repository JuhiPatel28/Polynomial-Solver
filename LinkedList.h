//Juhi Patel
//jmp170130

#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED
#include "Node.h"

class LinkedList
{
private:
    Node* head; //node head
public:
    LinkedList(); //default constructor
    LinkedList(Node*&); //overloaded constructor
    ~LinkedList(); //destructor

    //accessor
    Node *getHead() {return head;};

    //mutator
    void SetHead(Node *h) {head = h;};


    void Insert(double, int);
    void Print(long double, double);

};

#endif // LINKED_LIST_H_INCLUDED
