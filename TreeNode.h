// TreeNode.h - Tree node template class

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include <stddef.h>
using namespace std;

template <typename T>
class TreeNode{
  public:
    TreeNode();
    TreeNode(int k, T* v); // k is the key, v is value
    ~TreeNode();

    int key; // key that we are using to index
    T* value; // object that we are storing

    TreeNode<T> *left;
    TreeNode<T> *right;
};

// Default constructor
template <typename T>
TreeNode<T>::TreeNode(){
  left = NULL;
  right = NULL;
}

// Overloaded constructor
template <typename T>
TreeNode<T>::TreeNode(int k, T* v){
  key = k;
  value = v;
  left = NULL;
  right = NULL;
}

// Destructor
template <typename T>
TreeNode<T>::~TreeNode(){
  //character development
  delete value;
  delete left;
  delete right;
}
