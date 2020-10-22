//Juhi Patel
//jmp170130
#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <iomanip>
#include <fstream>

LinkedList::LinkedList() //default constructor
{
    head = nullptr; //set head to null
}

LinkedList::LinkedList(Node*& h) //overloaded constructor
{
    head = h; //set head to node
}

LinkedList::~LinkedList() //deconstructor
{
   if(head == nullptr) //delete list recursively
    {
        return;
    }
    delete head->next;
}

void LinkedList::Insert(double cof, int ex) //insert a node in order
{
    Node *n = new Node; //new node
    n->SetC(cof); //fill node
    n->SetE(ex);

    if(!head) //if empty list
    {
        head = n; //add node to list
    }
    else if(n->getE() > head->getE()) //if the exponent is greater that the head exponent
    {
        n->next = head; //add in the front of the head
        head = n;
    }
    else if (n->getE() < head->getE())//if not greater than head exponent
    {
        Node* cpy = head;
        while(cpy->next && (cpy->next->getE() >= n->getE()))
        {
            cpy = cpy->next; //increment until greater than next node

            //CHANGED CODE
            if(cpy->getE() == n->getE()) //if the values of the exponents are the same break out of loop
            {
                break;
            }
        }

        if(cpy->getE() == n->getE()) //if the values of the exponents are the same, combine like terms
        {
            //CHANGED CODE
            //double total = cpy->next->getC() + n->getC();
            //cpy->next->SetC(total);

            double total = cpy->getC() + n->getC(); //changed from next
            cpy->SetC(total);
        }
        else
        {
            n->next = cpy->next; //add to list
            cpy->next = n;
        }
    }
    else if(n->getE() == head->getE())
    {
        double total = head->getC() + n->getC();
        head->SetC(total);
    }
}

void LinkedList::Print(long double total, double x) //send to file
{
    std::fstream outfile("answers.txt", std::ios::out | std::ios::app); //open file
    Node *cpy = head; //copy of head
    outfile << "f(" << x << ") = "; //print out f(x) =
    if(cpy->getC() != 1 && cpy->getC() != -1) //if coefficient is not 1 or -1
    {
        outfile << cpy->getC(); //print out the coeffiecient
    }
    else if(cpy->getC() == -1) //if it is -1
    {
        outfile << "- "; //print -
    }
    else if(cpy->getC() == 1 && cpy->getE() == 0) //if it is 1 and the exponent is 0 print out 1
    {
        outfile << "1 ";
    }
    else if(cpy->getC() == -1 && cpy->getE() == 0) //if it is 1 and the exponent is 0 print out -1
    {
        outfile << "1 ";
    }

    if(cpy->getE() != 0 && cpy->getE() != 1) //if the exponent is not 0 or 1
    {
        outfile << "x^" << cpy->getE() << " "; //print out the exponent
    }
    else if(cpy->getE() == 0) //if exponent is zero
    {
        outfile << " "; //print space
    }
    else if(cpy->getE() == 1) //if exponent is 1
    {
        outfile << "x "; //print out x
    }
    cpy = cpy->next;
    while(cpy != nullptr) //print until end of list
    {
        if(cpy->getC() > 0 && cpy->getC() == 1) //same as above
        {
            outfile << "+ ";
            if(cpy->getE() != 0 && cpy->getE() != 1)
            {
                outfile << "x^" << cpy->getE() << " ";
            }
            else if(cpy->getE() == 0)
            {
                outfile << "1 ";
            }
            else if(cpy->getE() == 1)
            {
                outfile << "x ";
            }
        }
        else if(cpy->getC() > 0 && cpy->getC() != 1)
        {
            outfile << "+ " << cpy->getC();
            if(cpy->getE() != 0 && cpy->getE() != 1)
            {
                outfile << "x^" << cpy->getE() << " ";
            }
            else if(cpy->getE() == 0)
            {
                outfile << " ";
            }
            else if(cpy->getE() == 1)
            {
                outfile << "x ";
            }
        }
        else if(cpy->getC() < 0 && cpy->getC() != -1)
        {
            outfile << "- " << (cpy->getC() * -1);
            if(cpy->getE() != 0 && cpy->getE() != 1)
            {
                outfile << "x^" << cpy->getE() << " ";
            }
            else if(cpy->getE() == 0)
            {
                outfile << " ";
            }
            else if(cpy->getE() == 1)
            {
                outfile << "x ";
            }
        }
        else if(cpy->getC() < 0 && cpy->getC() == -1)
        {
            outfile << "- ";
            if(cpy->getE() != 0 && cpy->getE() != 1)
            {
                outfile << "x^" << cpy->getE() << " ";
            }
            else if(cpy->getE() == 0)
            {
                outfile << "1 ";
            }
            else if(cpy->getE() == 1)
            {
                outfile << "x ";
            }
        }
        cpy = cpy->next; //move to next node
    }
    outfile << "= " << std::setprecision(3) << std::fixed << total; //print out total
    outfile << std::endl;
}

/*
LinkedList::~LinkedList() //deconstructor
{
    Node *del = head; //copy of head
    Node *cpy = del->next;

    while(del != nullptr) //delete the whole linked list
    {
        cpy = del->next;
        delete del;
        del = cpy;
    }
    head = nullptr; //set head back to null
}
*/
