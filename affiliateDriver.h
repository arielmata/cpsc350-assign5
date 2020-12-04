// affiliateDriver.h - header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "BST.h"
#include "student.h"
#include "faculty.h"
#include "GenStack.h"
#include <iostream> //input and output
#include <fstream> //read and open files
#include <sstream> //stringstream
using namespace std;

class AffiliateDriver{
  public:
    AffiliateDriver();
    ~AffiliateDriver();

    void menuDriver();
    void openDisks();
    void saveDisks();
    void outputFT(TreeNode<Faculty> *n, ofstream& ofs);
    void outputST(TreeNode<Student> *n, ofstream& ofs);

    void printStudents(TreeNode<Student> *n); // prints all students
    void printFaculty(TreeNode<Faculty> *n); // prints all faculty
    void printStudentInfo();
    void printFacultyInfo();
    void printAdvisees();
    void printAdvisor();

    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisor();
    int checkID(string type);
    void removeAdviseeF();

    void rollback();
  private:
    int numFaculty;
    int numStudents;
    BST<Student> *masterStudent;
    BST<Faculty> *masterFaculty;
    GenStack<int> *rollbackStack; //don't know what we should save here
};
