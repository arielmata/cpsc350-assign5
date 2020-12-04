//headerfile - EmptyStackException.h

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include <stdexcept>
using namespace std;

//EmptyStackException: Exception for throwing an error when stack is empty
class EmptyStackException : public runtime_error{
  public:
    EmptyStackException(const char* message) : runtime_error(message){}
};
