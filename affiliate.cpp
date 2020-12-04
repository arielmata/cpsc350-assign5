// affiliate.cpp - Affiliate base class implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "affiliate.h"

// Default constructor
Affiliate::Affiliate(){
  IDNum = -1;
  name = "";
  level = "";
}

// Overloaded constructor
Affiliate::Affiliate(int i, string n, string l){
  IDNum = i;
  name = n;
  level = l;
}

// Destructor
Affiliate::~Affiliate(){}


// Returns the Affiliate's ID number
int Affiliate::getID(){
  return IDNum;
}

// Returns the Affiliate's name
string Affiliate::getName(){
  return name;
}

// Returns the Affiliate's level
string Affiliate::getLevel(){
  return level;
}


// Prints information of Affiliate to standard output
void Affiliate::printInformation(){
  cout << "Name: " << name << endl;
  cout << "ID: " << IDNum << endl;
  cout << "Level: " << level << endl;
}

// Returns a string of the affiliate's information that is comma separated
string Affiliate::stringCommaSeparated(){
  string ret = to_string(IDNum) + "," + name + "," + level + ",";
  return ret;
}

// Sets Affiliate's ID number as given int parameter i
void Affiliate::setID(int i){
  IDNum = i;
}

// Sets Affiliate's name as given string parameter n
void Affiliate::setName(string n){
  name = n;
}

// Sets Affiliate's level as given string parameter l
void Affiliate::setLevel(string l){
  level = l;
}
