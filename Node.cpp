//Juhi Patel
//jmp170130
#include "Node.h"

Node::Node() //default constructor
{
    next = nullptr; //set next to null
}

Node::Node(double c, double e) //node fill function
{
    coefficient = c;
    exponent = e;
}
