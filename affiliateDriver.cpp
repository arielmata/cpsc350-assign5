// affiliateDriver.cpp - implementation file

// Full name: Ariel Gutierrez
// Student ID: 2318163
// Chapman email: arigutierrez@chapman.edu
// Course number and section: CPSC 350-01
// Assignment or exercise number: Assignment 5

// Assignment 5: A C++ program that implements a simple database system using
// binary search trees. The databases will allow the user to insert, delete,
// and query data.

#include "affiliateDriver.h"

// Default constructor
AffiliateDriver::AffiliateDriver(){
  numFaculty = 0;
  numStudents = 0;
  masterStudent = new BST<Student>;
  masterFaculty = new BST<Faculty>;
  rollbackStack = new GenStack<int>; //stores deletes and inserts
}

// Destructor
AffiliateDriver::~AffiliateDriver(){
  delete masterStudent;
  delete masterFaculty;
  delete rollbackStack;
}


// Displays the menu to the user, makes sure that the user input is correct,
// and returns false if user wants to quit
void AffiliateDriver::menuDriver(){
  int userInput;
  string userInputStr;
  bool isRunning = true;

  while(isRunning){
    cout << '\n'<< endl;
    cout << "Please choose one of the options by typing its corresponding number: \n" << endl;
    cout << "1.  Print all students and their information (sorted by ascending ID#)" << endl;
    cout << "2.  Print all faculty and their information (sorted by ascending ID#)" << endl;
    cout << "3.  Find and display student information" << endl;
    cout << "4.  Find and display faculty information" << endl;
    cout << "5.  Display the name and info of a student's faculty advisor" << endl;
    cout << "6.  Display all the names and info of a faculty's advisees." << endl;
    cout << "7.  Add a new student" << endl;
    cout << "8.  Delete a student" << endl;
    cout << "9.  Add a new faculty member" << endl;
    cout << "10. Delete a faculty number" << endl;
    cout << "11. Change a student's advisor" << endl;
    cout << "12. Remove an advisee from a faculty member" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;

    cin >> userInputStr;
    cout << endl;
    try{
      userInput = stoi(userInputStr);
    }
    catch(invalid_argument ia){
      cerr << "You did not enter an integer option. Try again." << endl;
    }

    switch (userInput){
      case 1:
        printStudents(masterStudent->getRoot());
        break;
      case 2:
        printFaculty(masterFaculty->getRoot());
        break;
      case 3:
        printStudentInfo();
        break;
      case 4:
        printFacultyInfo();
        break;
      case 5:
        printAdvisor();
        break;
      case 6:
        printAdvisees();
        break;
      case 7:
        addStudent();
        break;
      case 8:
        deleteStudent();
        break;
      case 9:
        addFaculty();
        break;
      case 10:
        deleteFaculty();
        break;
      case 11:
        changeAdvisor();
        break;
      case 12:
        removeAdviseeF();
        break;
      case 13:
        rollback();
        break;
      case 14:
        saveDisks();
        cout << "\nExiting Program..." << endl;
        isRunning = false;
        break;
      default:
        cout << "You did not select a correct integer option. Please try again." << endl;
        cout << endl;
    }
  }
}

// Checks the current directory for the existence of "facultyTable.txt" and
// "studentTable.txt" to populate BST trees. If either of the files don't exist,
// then masterFaculty or masterStudent will be new, empty trees.
//MAYBE NEED TO DELETE WHOLE STUDENT TABLE IF FILE ISN'T IN CORRECT FORMAT
void AffiliateDriver::openDisks(){
  ifstream infileFT;
  ifstream infileST;

  //Faculty variables
  int fID;
  string fName;
  string fLevel;
  string department;
  DoublyLinkedList<int> adviseeList;
  int adviseeID;

  //Student variables
  int sID;
  string sName;
  string sLevel;
  string major;
  double gpa;
  int advisorID;

  infileFT.open("facultyTable.txt");

  // FacutyTable doesn't exist so create new file "facultyTable.txt"
  if (infileFT.fail()){
    infileFT.close();
    ofstream outfileFT;
    outfileFT.open("facultyTable.txt");
    outfileFT.close();
  }else{
    bool fileFormatIsCorrect = true;
    string line;
    while (getline(infileFT, line) && fileFormatIsCorrect){
      stringstream ss(line);
      int count = 0;
      string section;
      while (getline(ss, section, ',') && fileFormatIsCorrect){
        switch (count){
          case 0:
            try{
              fID = stoi(section);
            }catch(invalid_argument ia){
              cerr << "facultyTable.txt is not in the correct format." << endl;
              fileFormatIsCorrect = false;
              break;
            }
            break;
          case 1:
            fName = section;
            break;
          case 2:
            fLevel = section;
            break;
          case 3:
            department = section;
            break;
          default:
            //add advisees to adviseelist
            try{
              adviseeID = stoi(section);
            }catch(invalid_argument ia){
              cerr << "facultyTable.txt is not in the correct format." << endl;
              fileFormatIsCorrect = false;
              break;
            }
            adviseeList.insertFront(adviseeID);
            break;
          }
          ++count;
        }
        Faculty *f = new Faculty(fID, fName, fLevel, department, adviseeList);
        masterFaculty->insertNode(fID, f); //Add faculty to BST
      }
      ++numFaculty;
    }

    infileFT.close();

    infileST.open("studentTable.txt");

    // studentTable doesn't exist so create new file "facultyTable.txt"
  if (infileST.fail()){
    infileST.close();
    ofstream outfileST;
    outfileST.open("studentTable.txt");
    outfileST.close();
  }else{
    bool fileFormatIsCorrect = true;
    string line;
    while (getline(infileST, line) && fileFormatIsCorrect){
      if (numStudents == 0){
        if (line != "Student Table")
          cerr << "studentTable.txt is not in the correct format." << endl;
          fileFormatIsCorrect = false;
          break;
      }else{
        stringstream ss(line);
        int count = 0;
        string section;
        while (getline(ss, section, ',') && fileFormatIsCorrect){
          switch (count){
            case 0:
              try{
                fID = stoi(section);
              }catch(invalid_argument ia){
                cerr << "studentTable.txt is not in the correct format." << endl;
                fileFormatIsCorrect = false;
                break;
              }
              break;
            case 1:
              sName = section;
              break;
            case 2:
              sLevel = section;
              break;
            case 3:
              major = section;
              break;
            case 4:
              try{
                gpa = stod(section);
              }catch(invalid_argument ia){
                cerr << "studentTable.txt is not in the correct format." << endl;
                fileFormatIsCorrect = false;
                break;
              }
              break;
            case 5:
              try{
                fID = stoi(section);
              }catch(invalid_argument ia){
                cerr << "studentTable.txt is not in the correct format." << endl;
                fileFormatIsCorrect = false;
                break;
              }
              break;
          }
          ++count;
        }
        Student *s = new Student(sID, sName, sLevel, major, gpa, advisorID);
        masterStudent->insertNode(sID, s); //Add student to BST
      }
      ++numStudents;
    }
  }
  infileST.close();
}

// Writes the faculty and student tables back out to "facultyTable.txt" and
// "studentTable.txt"
void AffiliateDriver::saveDisks(){
  ofstream outfileFT;
  ofstream outfileST;

  //writing faculty tree to file
  outfileFT.open("facultyTable.txt");
  outputFT(masterFaculty->getRoot(), outfileFT);
  outfileFT.close();

  //writing student tree to file
  outfileST.open("studentTable.txt");
  outputST(masterStudent->getRoot(), outfileST);
  outfileST.close();
}

void AffiliateDriver::outputFT(TreeNode<Faculty> *n, ofstream& ofs){
  if(!masterFaculty->isEmpty()){
    if(n != NULL){
      ofs << n->value->stringCommaSeparated() << '\n';
      outputFT(n->left, ofs);
      outputFT(n->right, ofs);
    }
  }
}

void AffiliateDriver::outputST(TreeNode<Student> *n, ofstream& ofs){
  if(!masterFaculty->isEmpty()){
    if(n != NULL){
      ofs << n->value->stringCommaSeparated() << '\n';
      outputST(n->left, ofs);
      outputST(n->right, ofs);
    }
  }
}

// Prints all students and their information (sorted by ascending ID#)
// TreeNode in paramater should be root of masterStudent
void AffiliateDriver::printStudents(TreeNode<Student> *n){
  if(masterStudent->isEmpty()){
    cout << "There are no students in the database. " << endl;
  }else{
    if (n != NULL){
      printStudents(n->left);
      n->value->printInformation();
      printStudents(n->right);
    }
  }
}

// Print all faculty and their information (sorted by ascending ID#)
// TreeNode in paramater should be root of masterFaculty
void AffiliateDriver::printFaculty(TreeNode<Faculty> *n){

  if(masterFaculty->isEmpty()){
    cout << "There are no faculty in the database. " << endl;
  }else{
    if (n != NULL){
      printFaculty(n->left);
      n->value->printInformation();
      cout << endl;
      printFaculty(n->right);
    }
  }

}

// Prompts user for student ID and prints out the student's info
void AffiliateDriver::printStudentInfo(){
  int sID = checkID("student");
  if(masterStudent->searchNode(sID)){
    masterStudent->returnValue(sID)->printInformation();
  }
  else{
    cout << "The student ID given does not exist in the database. " << endl;
  }
}

// Prompts user for faculty ID and prints out the student's info
void AffiliateDriver::printFacultyInfo(){
  int fID = checkID("faculty");
  if(masterFaculty->searchNode(fID)){
    masterFaculty->returnValue(fID)->printInformation();
  }
  else{
    cout << "The faculty ID given does not exist in the database. " << endl;
  }
}

// Prompts user for a Student’s ID# and prints the name and info of their
// faculty advisor
void AffiliateDriver::printAdvisor(){
  int sID = checkID("student");
  if (masterStudent->searchNode(sID)){
    //found student so print name and info of faculty advisor
    int fID = masterStudent->returnValue(sID)->getAdvisorID();
    masterFaculty->returnValue(fID)->printInformation();
  }else{
    //didn't find student
    cout << "No student with that ID exists. " << endl;
  }
}

// Prompts user for a Faculty's ID#, and prints all the names and info of
// their advisees
void AffiliateDriver::printAdvisees(){
  int fID = checkID("faculty");
  if (masterFaculty->searchNode(fID)){
    //found student so print name and info of faculty advisor
    cout << "Advisees: " << endl;
    DoublyLinkedList<int> temp;
    temp = masterFaculty->returnValue(fID)->getAdviseeList();
    int sID;
    while (temp.getSize() > 0){
      sID = temp.removeFront();
      masterStudent->returnValue(sID)->printInformation();
      cout << endl;
    }
  }else{
    //didn't find student
    cout << "No faculty with that ID exists. " << endl;
  }
}


// Adds a new student to the database
void AffiliateDriver::addStudent(){
  int studentID;
  string name;
  string level;
  string major;
  string gpaStr;
  double gpa;
  string advisorIDStr;
  int advisorID;

  studentID = checkID("student");

  bool isAsking = true;
  while (isAsking){
    cout << "Enter the student's name: ";
    cin.ignore();
    getline(cin, name, '\n');
    while(true){
      cout << "Verify: Is the student's name " << name << "?  (y/n)" << endl;
      string userIn;
      cin >> userIn;
      if (userIn == "y" || userIn == "Y"){
        isAsking = false;
        break;
      }
      else if(userIn == "n" || userIn == "N"){
        break;
      }
      else{
        cout << "Incorrect option. Please type in 'y' or 'n'. Try again." << endl;
      }
    }
  }

  bool askingLevel = true;
  while (askingLevel){
    cout << "Enter the student's level (freshman, sophmore, junior, senior, super senior): ";
    cin.ignore();
    getline(cin, level, '\n');
    //make lowercase
    for(int i = 0; i < level.length(); ++i){
      level[i] = tolower(level[i]);
    }
    if(level == "freshman"){
      level = "Freshman";
      askingLevel = false;
    }else if(level == "sophmore"){
      level = "Sophmore";
      askingLevel = false;
    }else if(level == "junior"){
      level = "Junior";
      askingLevel = false;
    }else if(level == "senior"){
      level = "Senior";
      askingLevel = false;
    }else if(level == "super senior"){
      level = "Super Senior";
      askingLevel = false;
    }else{
      cout << "You did not enter a correct level. Try again." << endl;
    }
  }

  isAsking = true;
  while(isAsking){
    cout << "Enter the student's major: ";
    cin.ignore();
    getline(cin, major, '\n');
    for(int i = 0; i < major.length(); ++i){
      if (i == 0){
        major[i] = toupper(major[i]);
      }else{
        major[i] = tolower(major[i]);
      }
    }

    while(true){
      cout << "Verify: Is the student's major " << major << "? (y/n)" << endl;
      string userAns;
      cin >> userAns;
      if (userAns == "y" || userAns == "Y"){
        isAsking = false;
        break;
      } else if (userAns == "n" || userAns == "N"){
        break;
      }else{
        cout << "Incorrect input. Enter only 'y' or 'n'." << endl;
      }
    }
  }

  while(true){
    cout << "Enter the student's GPA?: ";
    cin >> gpaStr;

    try{
      gpa = stod(gpaStr);
      break;
    }
    catch(invalid_argument ia){
      cerr << "GPA was not in correct format. Try again." << endl;
      continue;
    }
  }


  while(true){
    cout << "Enter the ID number of the student's faculty advisor: ";
    cin >> advisorIDStr;

    try{
      advisorID = stoi(advisorIDStr);
    }
    catch(invalid_argument ia){
      cerr << "ID number was not in correct format. Try again." << endl;
      continue;
    }
    //check if advisor exists
    if(masterFaculty->searchNode(advisorID)){
      //add student to list of advisees
      masterFaculty->returnValue(advisorID)->addAdvisee(studentID);
      break;
    }
    else{
      cout << "No faculty with that ID exists. Try again." << endl;
    }
  }

  Student *s = new Student(studentID, name, level, major, gpa, advisorID);
  masterStudent->insertNode(studentID, s); //int key, Student value
}

// Prompts for a student's ID#, and deletes a student from database as well as
// removing the student from a faculty advisor
void AffiliateDriver::deleteStudent(){
  int sID = checkID("student");
  if (masterStudent->searchNode(sID)){
    int aID = masterStudent->returnValue(sID)->getAdvisorID();
    cout << "fuck" << endl;
    masterFaculty->returnValue(aID)->removeAdvisee(sID);
    cout << "you" << endl;
    masterStudent->deleteNode(sID);
  }
  else{
    cout << "No student with that ID exists. " << endl;
  }
}


// Adds a new faculty member to the database
void AffiliateDriver::addFaculty(){
  int facultyID;
  string name;
  string level;
  string department;
  string advisee;

  facultyID = checkID("faculty");

  bool isAsking = true;
  while (isAsking){
    cout << "Enter the faculty's name: ";
    cin.ignore();
    getline(cin, name, '\n');
    while(true){
      string userIn;
      cout << "Verify: Is the faculty's name " << name << "?  (y/n) ";
      cin >> userIn;
      if (userIn == "y" || userIn == "Y"){
        isAsking = false;
        break;
      }else if(userIn == "n" || userIn == "N"){
        break;
      }else{
        cout << "Incorrect option. Please type in 'y' or 'n'. Try again." << endl;
      }
    }
  }

  isAsking = true;
  while(isAsking){
    cout << "Enter the faculty's level: ";
    cin.ignore();
    getline(cin, level, '\n');
    //make lowercase
    for(int i = 0; i < level.length(); ++i){
      if (i == 0){
        level[i] = toupper(level[i]);
      }else{
        level[i] = tolower(level[i]);
      }
    }

    while(true){
      cout << "Verify: Is the faculty's level " << level << "? (y/n)" << endl;
      string userAns;
      cin >> userAns;
      if (userAns == "y" || userAns == "Y"){
        isAsking = false;
        break;
      } else if (userAns == "n" || userAns == "N"){
        break;
      }else{
        cout << "Incorrect input. Enter only 'y' or 'n'." << endl;
      }
    }
  }


  isAsking = true;
  while(isAsking){
    cout << "Enter the faculty's department: ";
    cin.ignore();
    getline(cin, department, '\n');

    while(true){
      cout << "Verify: Is the faculty's department " << department << "? (y/n)" << endl;
      string userAns;
      cin >> userAns;
      if (userAns == "y" || userAns == "Y"){
        isAsking = false;
        break;
      } else if (userAns == "n" || userAns == "N"){
        break;
      }else{
        cout << "Incorrect input. Enter only 'y' or 'n'." << endl;
      }
    }
  }

  DoublyLinkedList<int> adviseeList;
  bool asking = true;
  while(asking){
    cout << "Does this faculty have any advisees? (y/n) ";
    string userAns;
    cin >> userAns;
    if (userAns == "y" || userAns == "Y"){
      //make linked list of advisees
      isAsking = true;
      while(isAsking){
        int adviseeID = checkID("advisee");
        adviseeList.insertBack(adviseeID);

        while(true){
          cout << "Does this faculty have any more advisees? (y/n) ";
          string userAns;
          cin >> userAns;
          if (userAns == "y" || userAns == "Y"){
            break;
          } else if (userAns == "n" || userAns == "N"){
            isAsking = false;
            asking = false;
            break;
          }else{
            cout << "Incorrect input. Enter only 'y' or 'n'." << endl;
          }
        }
      }
    }else if (userAns == "n" || userAns == "N"){
      asking = false;
      break;
    }else{
      cout << "Incorrect input. Enter only 'y' or 'n'." << endl;
    }
  }

  Faculty *f = new Faculty(facultyID, name, level, department, adviseeList);
  masterFaculty->insertNode(facultyID, f);
}

// Deletes a faculty member given the ID# and reassigns students faculty adviors
void AffiliateDriver::deleteFaculty(){
  int fID = checkID("faculty");
  if (masterFaculty->searchNode(fID)){
    Faculty *f = new Faculty();
    f = masterFaculty->returnValue(fID);

    while(true){
      cout << "WARNING: REMOVING FACULTY FROM DATABASE WILL REQUIRE REASSIGNING " << endl;
      cout << "NEW FACULTY ADVISORS FOR THE STUDENT ADVISEES. " << endl;
      cout << endl;
      cout << "Would you like to continue? (y/n) ";
      string userAns;
      cin >> userAns;

      if (userAns == "y" || userAns == "Y"){
        //iterate through list of advisees and give students new faculty advisors
        while (f->getAdviseeList().getSize() > 0){
          int sID = f->getAdviseeList().removeFront();

          Student *s = new Student();
          s = masterStudent->returnValue(sID);
          cout << s->getName() << " (ID#: " << sID <<") needs a new advisor" << endl;
          while (true){
            int aID = checkID("new advisor");
            //check if faculty exists
            if (masterFaculty->searchNode(aID)){
              //set new advisor for student and add student to advisee List for
              //new advisor
              s->setAdvisorID(aID);
              masterFaculty->returnValue(aID)->addAdvisee(sID);
              break;
            }else{
              cout << "No faculty with that ID number exists in the database. Try Again." << endl;
            }
          }
        }
        //All the students have been removed from advisee list so now we
        //remove the faculty member from database
        masterFaculty->deleteNode(fID);
        break;
      }else if (userAns == "n" || userAns == "N"){
        break;
      }else{
        cout << "Incorrect input. Enter only 'y' or 'n'." << endl;
      }
    }
  }
  else{
    cout << "No faculty with that ID exists." << endl;
  }
}

// Changes a Student’s advisor given the student ID and the new faculty ID
void AffiliateDriver::changeAdvisor(){
  int sID = checkID("student");
  int fID;

  //Student is found
  if(masterStudent->searchNode(sID)){
    fID = checkID("new advisor");

    //Faculty member exists so change student's advisor
    if(masterFaculty->searchNode(fID)){
      masterStudent->returnValue(sID)->setAdvisorID(fID);
    }else{
      //Faculty member does not exist
      cout << "The faculty ID given does not exist in the database. " << endl;
    }
  }else{
    //Student was not found
    cout << "The student ID given does not exist in the database. " << endl;
  }
}

// Prompts user for ID until a correct format is recieved
int AffiliateDriver::checkID(string type){
  string IDStr;
  int IDNum;
  while(true){
    cout << "Enter the " << type << "'s ID number: ";
    cin >> IDStr;
    try{
      IDNum = stoi(IDStr);
      return IDNum;
    }
    catch(invalid_argument ia){
      cerr << "ID number is not in the correct format. Try again." << endl;
    }
  }
}

void AffiliateDriver::removeAdviseeF(){
  int fID = checkID("faculty");
  masterFaculty->returnValue(fID)->printAdvisees();
  int aID = checkID("advisee");
  masterFaculty->returnValue(fID)->removeAdvisee(aID);

  //assign student new advisor
  cout << "You need to reassign the student, " << masterStudent->returnValue(aID)->getName()
  <<"(ID: " << masterStudent->returnValue(aID)->getID() << ") a new advisor." << endl;
  int advisorID = checkID("advisor");
  masterStudent->returnValue(aID)->setAdvisorID(advisorID);
}

// Undo's the previous action that has changed the shape of BST
void AffiliateDriver::rollback(){
  //NOT DONE
}
