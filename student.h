// student.h - Student header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "affiliate.h"

class Student : public Affiliate{
public:
    Student();
    Student(int i, string n, string l, string m, double g, int aID);
    ~Student();

    void printInformation();
    string stringCommaSeparated();

    // accessors
    string getMajor();
    double getGPA();
    int getAdvisorID();

    // mutators
    void setMajor(string m);
    void setGPA(double g);
    void setAdvisorID(int aID);
private:
  string major;
  double gpa;
  int advisorID;
};
