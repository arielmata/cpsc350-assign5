// ListNode.h - Generic List Node for Doubly Linked List

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include <stddef.h>
using namespace std;

template <typename T>
class ListNode{
  public:
    ListNode(T d);
    ~ListNode();

    T data; // Value stored in node
    ListNode<T> *next; // Pointer to next node
    ListNode<T> *prev; // Pointer to previous node
};

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  delete next;
  delete prev;
}
