// student.cpp - Student implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "student.h"

// Default constructor
Student::Student(){
  Affiliate();
  major = "";
  gpa = -1.0;
  advisorID = -1;
}

// Overloaded constructor
Student::Student(int i, string n, string l, string m, double g, int aID){
  IDNum = i;
  name = n;
  level = l;
  major = m;
  gpa = g;
  advisorID = aID;
}

// Destructor
Student::~Student(){}


// Prints the Student's information to standard output
void Student::printInformation(){
  Affiliate::printInformation();
  cout << "Major: " << major << endl;
  cout << "GPA: " << gpa << endl;
  cout << "Advisor ID: " << advisorID << endl;
  cout << endl;
}

// Returns a string of the student information that is comma separated
string Student::stringCommaSeparated(){
  string ret = Affiliate::stringCommaSeparated() + major + "," + to_string(gpa)
    + "," + to_string(advisorID);
  return ret;
}

// Returns the Student's major
string Student::getMajor(){
  return major;
}

// Returns the Student's GPA
double Student::getGPA(){
  return gpa;
}

// Returns the Student's advisor's ID
int Student::getAdvisorID(){
  return advisorID;
}


// Sets Student's major as given string parameter m
void Student::setMajor(string m){
  major = m;
}

// Sets Student's GPA as given double parameter g
void Student::setGPA(double g){
  gpa = g;
}

// Sets Student's advisor's ID number as given int parameter aID
void Student::setAdvisorID(int aID){
  advisorID = aID;
}
