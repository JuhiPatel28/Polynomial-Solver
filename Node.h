//Juhi Patel
//jmp170130

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node
{
private:
    double coefficient; //variables
    int exponent;

public:
    Node* next;
    Node(); //default constructor
    Node(double, double); //overloaded constructor

    //mutators
    void SetN(Node *n) {next = n;};
    void SetC(double c) {coefficient = c;};
    void SetE(int e) {exponent = e;};

    //accessors
    Node* getN() {return next;};
    double getC() {return coefficient;};
    int getE() {return exponent;};
};

#endif // NODE_H_INCLUDED
