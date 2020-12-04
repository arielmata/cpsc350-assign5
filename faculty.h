// faculty.h - Faculty header file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "affiliate.h"
#include "DoublyLinkedList.h"

class Faculty : public Affiliate{
  public:
    Faculty();
    Faculty(int i, string n, string l, string d, DoublyLinkedList<int> al);
    ~Faculty();

    void printInformation();
    void printAdvisees();
    int removeAdvisee(int sID);
    void addAdvisee(int sID);
    string stringCommaSeparated();

    // accessors
    string getDepartment();
    DoublyLinkedList<int> getAdviseeList();

    // mutators
    void setDepartment(string d);
    void setAdviseeList(DoublyLinkedList<int> al);
  private:
    string department;

    // Doubly Linked List of advisees Student ID numbers
    DoublyLinkedList<int> adviseeList;
};
