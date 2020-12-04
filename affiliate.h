// affiliate.h - Affiliate base class

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include <iostream>
#pragma once
using namespace std;

class Affiliate{
  public:
    Affiliate();
    Affiliate(int i, string n, string l);
    ~Affiliate();

    void printInformation();
    string stringCommaSeparated();

    // accessors
    int getID();
    string getName();
    string getLevel();

    // mutators
    void setID(int i);
    void setName(string n);
    void setLevel(string l);
  protected:
    int IDNum;
    string name;
    string level;
};
