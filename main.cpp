// main.cpp - main file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "affiliateDriver.h"

int main(int argc, char **argv){
  AffiliateDriver *ad = new AffiliateDriver();

  ad->openDisks();
  ad->menuDriver();
  ad->saveDisks();

  delete ad;
  return 0;
}
