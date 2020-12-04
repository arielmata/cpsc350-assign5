// faculty.cpp - Faculty implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "faculty.h"

// Default constructor
Faculty::Faculty(){
  Affiliate();
  department = "";
}

// Overloaded constructor
Faculty::Faculty(int i, string n, string l, string d, DoublyLinkedList<int> al){
  IDNum = i;
  name = n;
  level = l;
  department = d;
  adviseeList = al;
}

// Destructor
Faculty::~Faculty(){}

// Prints the Faculty's information to standard output
void Faculty::printInformation(){
  Affiliate::printInformation();
  cout << "Department: " << department << endl;
  //  NOT SURE IF WE PRINT OUT ADVISEES
  cout << "Advisee IDs: ";
  adviseeList.printListCommaSeparated();
  cout << endl;
}

//Prints out list of advisee ID numbers
void Faculty::printAdvisees(){
  cout << "Advisee IDs: ";
  adviseeList.printListCommaSeparated();
}

// Returns a string of the faculty information that is comma separated
string Faculty::stringCommaSeparated(){
  string ret = Affiliate::stringCommaSeparated() + department + "," +
    adviseeList.stringListCommaSeparated();
  return ret;
}

// Returns true if we were able to remove student from Advisee list
int Faculty::removeAdvisee(int sID){
  return adviseeList.removeNode(sID);
}

void Faculty::addAdvisee(int sID){
  adviseeList.insertBack(sID);
}

// Returns the department the Faculty works in
string Faculty::getDepartment(){
  return department;
}

// Returns a doubly linked list with ID numbers of student advisees
DoublyLinkedList<int> Faculty::getAdviseeList(){
  return adviseeList;
}


// Sets Faculty's department as given string parameter d
void Faculty::setDepartment(string d){
  department = d;
}

// Sets Faculty's doubly linked list of student advisees as given paramater al
void Faculty::setAdviseeList(DoublyLinkedList<int> al){
  adviseeList = al;
}
