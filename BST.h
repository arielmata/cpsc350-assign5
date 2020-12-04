// BST.h - Binary Search tree template class

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "TreeNode.h"
#include <iostream>

template <typename T>
class BST{
  private:
    TreeNode<T> *root; // Root node
  public:
    BST();
    ~BST();

    bool searchNode(int k);
    void insertNode(int k, T* value);
    bool deleteNode(int k);
    T* returnValue(int k);
    void printEntireTree();

    //helper functions
    bool isEmpty();
    unsigned int getSize();
    TreeNode<T>* getMin(); //can return value but here we are returning tree node
    TreeNode<T>* getMax();
    void recPrint(TreeNode<T> *node);

    TreeNode<T>* getSuccessor(TreeNode<T> *d);//returns successor of node we will delete d
    TreeNode<T>* getRoot();
};

// Default constructor
template <typename T>
BST<T>::BST(){
  root = NULL;
}

// Destructor
template <typename T>
BST<T>::~BST(){
  delete root;
}

// Recursively prints out all the nodes in order to the standard output
template <typename T>
void BST<T>::recPrint(TreeNode<T> *node){
  if(node != NULL){
    recPrint(node->left);
    cout << node->key << endl; //=> cout << node->value << endl;
    recPrint(node->left);
  }
}

// Prints out the entire tree to standard output
template <typename T>
void BST<T>::printEntireTree(){
  recPrint(root); // i don't understand
}


// Returns the minimum node
template <typename T>
TreeNode<T>* BST<T>::getMin(){
  TreeNode<T> *current = root;

  if(isEmpty())
    return NULL;

  while(current->right != NULL){
    current = current->left;
  }

  return current;
}


// Returns the maximum key
template <typename T>
TreeNode<T>* BST<T>::getMax(){
  TreeNode<T> *current = root;

  if(isEmpty())
    return NULL;

  while(current->right != NULL){
    current = current->right;
  }

  return current;
}

// Inserts node into the treee
template <typename T>
void BST<T>::insertNode(int k, T* value){
  TreeNode<T> *node = new TreeNode<T>(k, value);

  if(isEmpty()){
    root = node;
  }else{
    //tree is not empty
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;///idkidkidk

    while(true){
      parent = current;

      if(k < current->key){
        current = current->left;
        if(current == NULL){
          //found insertion point
          parent->left = node;
          break;
        }
      }else{
        //we go right
        current = current->right;
        if(current == NULL){
          parent->left = node;
          break;
        }
      }
    }
  }
}

// Returns true if they are able to find the node, otherwise returns false
template <typename T>
bool BST<T>::searchNode(int k){

  if(isEmpty())
    return false;
  else{
    //tree is not empty, let's and find k
    TreeNode<T> *current = root;
    while (current->key != k){
      if(k < current->key)
        current = current->left;
      else
        current = current->right;

      if(current == NULL)
        return false;
    }
  }
  return true;
}

// Returns true if node is able to be delete, otherwise returns false if node
// is not in tree
template <typename T>
bool BST<T>::deleteNode(int k){

  if(isEmpty())
    return false;
  //you can leverage search to determine whether value before proceeding

  TreeNode<T> *current = root;
  TreeNode<T> *parent = root;
  bool isLeftNode = true;

  //usual code to find a TreeNode

  while(current->key != k){
    parent = current;

    if(k < current->key){
      //go left
      isLeftNode = true;
      current = current->left;
    }else{
      //go right
      isLeftNode = false;
      current = current->right;
    }

    if(current == NULL){
      return false;
    }
  }

  //if we make here, we found our key/value
  //let's proceed to delete

  //case: node to deleted has no children, AKA leaf node
  if(current->left == NULL && current->right == NULL){
    if(current == root){
      root = NULL;
    }else if(isLeftNode){
      parent->left = NULL;
    }else{
      //right child
      parent->right = NULL;
    }
  }
  //case: node to be deleted has one child. need to determine whether node has
  //left or right child
  else if(current->right == NULL){
    //node has one childe and it's a left
    //no right child

    if(current == root){
      root = current->left;
    }
    else if (isLeftNode){
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }
  else if(current->left == NULL){
    //node has one childe and it's a right
    //no left child

    if(current == root){
      root = current->right;
    }
    else if (isLeftNode){
      parent->left = current->right;
    }
    else{
      parent->right = current->right;
    }
  }
  else{
    //node to be deleted has two children
    TreeNode<T> *successor = getSuccessor(current);

    if(current == root){
      root = successor;
    }
    else if(isLeftNode){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }

    successor->left = current->left;
  }
  //delete current; //QUESTION do WE garbage collect in the delete function?????
  return true;
}

// Returns the value of the node given the key
template <typename T>
T* BST<T>::returnValue(int k){
  TreeNode<T> *current = root;
  while (current->key != k){
    if(k < current->key){
      current = current->left;
    }else{
      current = current->right;
    }
  }
  return current->value;
}


// Returns true if empty, otherwise returns false
template <typename T>
bool BST<T>::isEmpty(){
  return (root == NULL);
}

// Returns the successor of Tree Node *d
template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){

  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;
  TreeNode<T> *current = d->right;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }
  //once we exit the while loop, pointers should be in correct positions

  //we need to check whether or not successor is descendant of right child
  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

template <typename T>
TreeNode<T>* BST<T>::getRoot(){
  return root;
}
