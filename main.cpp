#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <array>

using namespace std;

//Hash Table. Ryan Thammakhoune. 

struct Student{
  char fname[100];
  char lname[100];
  int id;
  float gpa;
  Student* next;
  int hashNumber;
};


Student** addStudent(Student** &array, Student* ptrStu, int &size);
void deleteStu(vector<Student*>* stuList);
void print(Student** &array, int size);
int hashFunction(Student* stu, int size);
Student* randomStu(vector<char*> first, vector<char*> last);
Student* endList(Student* &start);
void printRow(Student* start);
int checkCollision(Student* start, int count);
Student** rehash(Student** array, int &size);
int checkRehash(Student** array, int size);


int main() {


  vector<char*> randFirst;
  ifstream file;
  file.open("fname.txt"); //Open the inputted file name
  char* output = new char[999];
  int i = 0;
  while(!file.eof()) { //If has not reached end of file
    file.get(output[i]);
    i++;
  }
  char* split = strtok(output, " ");
  while (split != NULL) {
    randFirst.push_back(split);
    split = strtok(NULL, " ");
  }
  cout << "First done" << endl;
  
  vector<char*> randLast;
  ifstream file2;
  file2.open("lname.txt"); //Open the inputted file name
  char* out = new char[999];
  int j = 0;
  while(!file2.eof()) { //If has not reached end of file
    file2.get(out[j]);
    j++;
  }
  char* split2 = strtok(out, " ");
  while (split2 != NULL) {
    randLast.push_back(split2);
    split2 = strtok(NULL, " ");
  }


  int size = 100;
  Student** array = new Student*[size];
  bool start = true;
  while (start == true) {
    char input[100];
    cout << "Enter a command" << endl;
    cin.getline(input, 100);
    if (strcmp(input, "ADD") == 0) {
      Student* ptrStu = new Student();
      cout << "Enter student first name" << endl;
      cin.getline(ptrStu->fname, 100);
      cout << "Enter student last name" << endl;
      cin.getline(ptrStu->lname, 100);
      cout << "Enter student id" << endl;
      char getId[100];
      cin.getline(getId, 100);
      ptrStu->id = atoi(getId);
      cout << "Enter student gpa" << endl;
      char getGpa[100];
      cin.getline(getGpa, 100);
      ptrStu -> gpa =  atof(getGpa);
      array = addStudent(array, ptrStu, size);
      cout << "Done" << endl;
    }
    else if (strcmp(input, "ADD RANDOM") == 0) {
      cout << "How many random students?" << endl;
      char inNum[9];
      cin.getline(inNum, 9);
      int stuNum = atoi(inNum);
      for (int q = 0; q < stuNum; q++) {
        array = addStudent(array, randomStu(randFirst, randLast), size);
      }
    }
    else if (strcmp(input, "HELP") == 0) {
      cout << "Type ADD to add a student\nType PRINT to print list\nType DELETE to delete student\nType QUIT to quit" << endl; 
    }
    else if (strcmp(input, "PRINT") == 0) {
      cout << "Printing" << endl;
      print(array, size);
    }
    else if (strcmp(input, "DELETE") == 0) {
      
    }
    else if (strcmp(input, "QUIT") == 0) {
      start = false;
      break;
    }
    else if (strcmp(input, "TEST") == 0) {

    }
  }
}

Student** rehash(Student** array, int &size) {
  cout << "Rehashing" << endl;
  size = size * 2;
  Student** newArray = new Student*[size];
  for (int b = 0; b <= size/2; b++) {
    if (array[b] != NULL) {
      cout << "Found at: " << b << endl;
      newArray = addStudent(newArray, array[b], size);
    }
  }
  return newArray;
}

int checkCollision(Student* start, int count) {
  int newCount = count + 1;
  if (start->next != NULL) {
    return checkCollision(start->next, newCount);
  }
  else {
    return newCount;
  }
}

Student* endList(Student* &start) {
  if (start -> next != NULL) {
    return endList(start->next);
  }
  else {
    return start;
  }
}

void printRow(Student* start) {
  cout << start->fname << " " << start->lname << " ID: " << start->id << " GPA: " << start->gpa << endl;
  if (start->next != NULL) {
    printRow(start->next);
  }
}

int hashFunction(Student* stu, int size) {
  int hashNum = 0;
  char* first = stu->fname;
  int a = 0;
  while (isalpha(first[a])) {
    hashNum = hashNum + (int) first[a];
    a++;
  }
  char* last = stu->lname;
  int b = 0;
  while (isalpha(last[b])) {
    hashNum = hashNum + (int) last[b];
    b++;
  }
  hashNum = hashNum + round(stu->gpa);
  hashNum = hashNum + stu->id;
  cout << "Gross index: " << hashNum << endl;
  int retNum = hashNum % size;
  return retNum;
}



Student** addStudent(Student** &array, Student* ptrStu, int &size) {
  int index = hashFunction(ptrStu, size);
  cout <<"Index: " << index << endl;
  if (array[index] == NULL) {
    cout << "New spot" << endl;
    array[index] = ptrStu;
    if (ptrStu -> next != NULL) {
      return (addStudent(array, ptrStu -> next, size));
    }
    else {
      return array;
    }
  }
  else {
    cout << "Collisions: " << checkCollision(array[index], 0) << endl;
    if (checkCollision(array[index], 0) == 2) {
      return rehash(array, size);
    }
    else {
      endList(array[index])-> next = ptrStu;
      return array;
    }
  }
}

void deleteStu(vector<Student*>* stuList) {
  int del;
  cout<< "Enter id of student to delete" << endl;
  cin >> del;
}

void print(Student** &array, int size) {
  for (int c = 0; c <= size; c++) {
    if (array[c] != NULL) {
      cout << "Found at index: " << c << endl;
      printRow(array[c]);
    }
  }
}


Student* randomStu(vector<char*> first, vector<char*> last) {
  Student* newStu = new Student();
  int fSize = first.size();
  int lSize = last.size();
  int randF = rand() % fSize;
  int randL = rand() % lSize;
  cout << randF << randL << endl;
  int fIndex = 0;
  int lIndex = 0;
  vector<char*> :: iterator i;
  for ( i = first.begin(); i != first.end(); i++) {
    if (fIndex == randF) {
      cout << (*i) << endl;
      strcpy(newStu -> fname, (*i));
    }
    fIndex++;
  }
  vector<char*> :: iterator it;
  for ( it = last.begin(); it != last.end(); it++) {
    if (lIndex == randL) {
      cout << (*it) << endl;
      strcpy(newStu -> lname, (*it));
    }
    lIndex++;
  }
  int newID = rand() % 3000 + 2000;
  newStu -> id = newID;
  float newGPA = ((float) rand()) / ((float) RAND_MAX) + 3.0;
  newGPA = (int) (newGPA * 10 + 0.5);
  newGPA = (float) newGPA / 10;
  newStu -> gpa = newGPA;
  return newStu;
}
