// DoublyLinkedList.h - Generic Doubly Linked List

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 4

// Assignment 4: A C++ program that simulates and calculate metrics on student
// wait times and window idle times given a specific traffic flow of students.

#include "ListNode.h"
#include "EmptyDoublyException.h"
#include <iostream>

template <typename T>
class DoublyLinkedList{
  public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(T d);
    void insertBack(T d);
    void insertAfter(ListNode<T> *curr, T d);
    T removeFront();
    T removeBack();
    int find(T value); // AKA search()
    T deletePos(int pos);
    T removeNode(T key); // Key represents the value we are going to search for and delete

    void printList();
    void printListCommaSeparated();
    string stringListCommaSeparated();
    void printListReverse();
    bool isEmpty();
    int getSize();
    T getFront();
    T getBack();
    void listInsertionSortDoublyLinked();
  private:
    ListNode<T> *front;
    ListNode<T> *back;
    int size;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
  // Start with an empty doubly linked list
  front = NULL;
  back = NULL;
  size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
  delete front;
  delete back;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);

  if(size == 0){
    back = node;
  }else{
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d);

  if(front == NULL){
    front = node;
  }else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(ListNode<T> *curr, T d){
  ListNode<T> *node = new ListNode<T>(d);

  if(front == NULL){
    front = node;
    back = node;
  }else if (curr == back){
    back->next = node;
    node->prev = back;
    back = node;
  }else{
    ListNode<T> *suc = curr->next;
    node->next = suc;
    node->prev = curr;
    curr->next = node;
    suc->prev = node;
  }
}

template <typename T>
T DoublyLinkedList<T>::removeFront(){
  ListNode<T> *node = front;

  if(isEmpty()){
    //throw excepetion
    throw EmptyDoublyException("Doubly Linked List is empty.");
  }else{
    if(front->next == NULL){
      back = NULL;
    }else{
      front->next->prev = NULL;
    }
    front = front->next;
    --size;
    node->next = NULL;
    T temp = node->data;

    delete node;
    return temp;
  }
}

template <typename T>
T DoublyLinkedList<T>::removeBack(){
  ListNode<T> *node = back;
  if(isEmpty()){
    //throw excepetion
    throw EmptyDoublyException("Doubly Linked List is empty.");
  }
  else{
    if(back->prev == NULL){
      front == NULL;
    }else{
      back->prev->next = NULL;
    }
    back = node->prev;
    --size;
    node->prev = NULL;
    T temp = node->data;

    delete node;
    return temp;
  }
}

template <typename T>
int DoublyLinkedList<T>::find(T value){
  int pos = -1;
  ListNode<T> *curr = front;

  while(curr != NULL){
    ++pos;
    if(value == curr->data)
      break;
    curr = curr->next;
  }
  // Did not find value
  if(curr == NULL)
    pos = -1;

  return pos;
}

template <typename T>
T DoublyLinkedList<T>::removeNode(T key){
  ListNode<T> *curr = front;

  //Loop through list to find the key/value
  while(curr->data != key){
    curr = curr->next;

    if(curr == NULL)
      return key;
  }

  //now if we get here, we found it, let's proceed to delete

  // Let's start with the front
  if(curr == front){
    front = curr->next;
    front->prev = NULL;
  }else if(curr == back){
    back = curr->prev;
    back->next = NULL;
  }else{
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }

  curr->prev = NULL;
  curr->next = NULL;
  --size;
  T temp = curr->data;
  delete curr;

  return temp;
}

/*
int DoublyLinkedList<T>::deletePos(int pos){
  int p = 0;
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;
  //erorr check if pos is not negative
  while(p != pos){
    //iterate and update my pointers
    prev = curr;
    curr = curr->next;
    p++;
  }
  // we found our target, all pointers shoudl be in the correct locations
  prev->next = curr->next;
  curr->next = NULL;
  int temp = curr->data;
  size--;

  delete curr;
  return temp;
}
*/

template <typename T>
void DoublyLinkedList<T>::printList(){
  ListNode<T> *curr = front;

  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }

}

template <typename T>
void DoublyLinkedList<T>::printListCommaSeparated(){
  ListNode<T> *curr = front;

  while(curr != NULL){
    if(curr != back){
      cout << curr->data << ", ";
    } else{
      cout << curr->data << endl;
    }

    curr = curr->next;
  }

}

template <typename T>
string DoublyLinkedList<T>::stringListCommaSeparated(){
  string ret = "";
  ListNode<T> *curr = front;

  while(curr != NULL){
    if(curr != back){
      ret += to_string(curr->data) + ",";
    }else{
      ret += to_string(curr->data);
    }
    curr = curr->next;
  }
  return ret;
}

template <typename T>
void DoublyLinkedList<T>::printListReverse(){
  ListNode<T> *curr = back;

  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->prev;
  }

}

template <typename T>
bool DoublyLinkedList<T>::isEmpty(){
  return (front == NULL && back == NULL);
}

template <typename T>
int DoublyLinkedList<T>::getSize(){
  return size;
}

template <typename T>
T DoublyLinkedList<T>::getFront(){
  return front->data;
}

template <typename T>
T DoublyLinkedList<T>::getBack(){
  return back->data;
}

template <typename T>
void DoublyLinkedList<T>::listInsertionSortDoublyLinked(){
  ListNode<T> *curr = front->next;
  while (curr != NULL){
    ListNode<T> *nextNode = curr->next;
    ListNode<T> *searchNode = curr->prev;
    while ((searchNode != NULL) && (searchNode->data > curr->data)){
      searchNode = searchNode->prev;
    }

    // Remove and re-insert curr
    removeNode(curr->data);
    if(searchNode == NULL){
      curr->prev = NULL;
      insertFront(curr->data);
    }
    else{
      insertAfter(searchNode, curr->data);
    }
    //advance to next node
    curr = nextNode;
  }
}
