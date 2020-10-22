#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "LinkedList.h"
#include "Node.h"

long double calcualte(double, LinkedList*);


int main()
{
    std::fstream file("poly3.txt", std::ios::in | std::ios::binary); //open file
    //variables
    int position;
    int par1, par2, eq, x, ex, space, sindex;
    int error = -1;
    double xval, coeff;
    int exp;

    if(!file.fail()) //if file doesnt open
    {
        while(!file.fail()) //while not at end of file
        {
            LinkedList *saveme = new LinkedList(); //create class object

            std::string line;
            getline(file, line); //read in line of file
            position = file.tellg(); //store pointer location
            par1 = line.find('('); //find first parantheses
            par2 = line.find(')'); //find second paranteses
            std::string xvalue = line.substr(par1 + 1, par2 - 2); //take out the x value
            xval = stod(xvalue); //convert it to a double
            line = line.substr(par2 + 1); //cut off the part that we have already parsed
            eq = line.find('='); //find the equals sign
            space = line.find(' '); //find space
            std::string substring = line.substr(eq + 2); //start a substring section
            if((int)substring.find(' ') != error) //if there is more that one term
            {
                space = substring.find(' '); //section off the first term
                substring = substring.substr(0, space + 1);
            }

            if((int)substring.find('x') != error) //if there is an x in the term
            {
                x = substring.find('x'); //find the x
                std::string co = substring.substr(0, x); //section off the coefficient

                //if(co != " ") //if there is a coefficient

                if(co!= "")  //regrage
                {
                    coeff = stod(co); //convert it to an int
                }
                else
                {
                    coeff = 1; //make it one
                }

                if((int)substring.find('^') != error) //look for carrot thing
                {
                    ex = substring.find('^'); //index the carrot thing
                    space = substring.find(' '); //look for space
                    std::string exponent = substring.substr(ex + 1, space); //create substring
                    //if((int)exponent.find('-') != error)
                    //{
                        //int m = exponent.find('-');
                        //exponent = exponent.substr(m + 1)
                    //}
                    exp = stoi(exponent); //convert to int
                }
                else
                {
                    exp = 1; //set exponent to 1
                }
            }
            else //if there isnt an x in the term
            {
                coeff = stod(substring); //convert string to double
                exp = 0; //set exponent to 0
            }
            sindex = line.find(substring); //find the substring in the original line
            line = line.substr(sindex + substring.length()); //cut the substring from the line
            saveme->Insert(coeff, exp); //fill the node
            while(line.length() > 1)
            {
                std::string sub = line.substr(2); //take out what we have already parsed
                if((int)sub.find(' ') != error) //if there is another term
                {
                    space = sub.find(' '); //split the term
                    sub = sub.substr(0, space + 1);
                }
                if((int)sub.find('x') != error) //if there is an x in the term
                {
                    x = sub.find('x'); //index the x
                    space = line.find(' ');
                    std::string coef = sub.substr(0, x); //split off the coeffiecient
                    std::string sign = line.substr(0, space); //split off the sign
                    if(sign == "+") //if the sign is a plus
                    {
                        if(coef == "") //if there is no coefficient
                        {
                            coeff = 1; //set the coefficient to one
                        }
                        else //if there is a coefficient
                        {
                            coeff = stod(coef); //convert it to a double
                        }
                    }
                    else if(sign == "-") //if the sign is a minus
                    {
                        if(coef == "") //if there is no coefficient
                        {
                            coeff = -1; //set it to -1
                        }
                        else //if there is a coeffiencient
                        {
                            coeff = stod(coef) * -1; //set it to the
                        }
                    }

                    if((int)sub.find('^') != error) //if there is a carrot thing
                    {
                        ex = sub.find('^'); //index the carrot thing
                        if((int)sub.find(' ') != error) //if there is another term
                        {
                            space = sub.find(' '); //index the space
                            std::string exponent = sub.substr(ex + 1, space - 1); //extract the exponent
                            exp = stoi(exponent); //convert it to an int
                        }
                        else //if there is not another term
                        {
                            int endline = sub.find('\r'); //index the endline symbol
                            std::string exponent = sub.substr(ex + 1, endline); //extract the exponent
                            exp = stoi(exponent); //convert it to an int
                        }
                    }
                    else //if there isnt a carrot thing
                    {
                        exp = 1; //set the exponent to one
                    }
                    sindex = line.find(sub); //cut off what we already parsed
                    line = line.substr(sindex + sub.length());

                }
                else //if there is no x
                {
                    x = sub.find('x'); //same as above
                    space = line.find(' ');
                    std::string coef = sub.substr(0, x);
                    std::string sign = line.substr(0, space);
                    if(sign == "-")
                    {
                        coeff = stod(sub) * -1;
                    }
                    else
                    {
                        coeff = stod(sub);
                    }

                    exp = 0; //set exponent to zero

                    int idk = line.find(sub);
                    line = line.substr(idk + sub.length());
                }
                saveme->Insert(coeff, exp);
            }
            long double t = calcualte(xval, saveme); //calculate the function
            saveme->Print(t, xval); //send to file
            delete saveme; //delete object
        }
    }
    else //if file doesnt open
    {
        std::cout << "File failed." << std::endl;
    }
    file.close(); //close file
    return 0;
}

long double calcualte(double x, LinkedList *hi)
{
    //variables
    long double calc;
    long double fin = 0;

    Node* cpy = hi->getHead();
    while(cpy != nullptr) //while not end of linked list
    {
        if(cpy->getE() != 0) //if the exponent is not zero
        {
            calc = pow(x, cpy->getE()); //calculate total
            calc = calc * cpy->getC();
            fin += calc;
        }
        else //if exponent is zero
        {
            calc = cpy->getC(); //calculate total
            fin += calc;
        }
        cpy = cpy->next; //move to next node
    }
    return fin; //return total
}

