#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <math.h>

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

struct HashTable {
  int size;
  Student** array = new Student*[size];
};

void addStudent(HashTable* &table);
void deleteStu(vector<Student*>* stuList);
void print(HashTable* table);
int hashFunction(Student* stu, int size);
Student* randomStu();
Student* endList(Student* start);
void printRow(Student* start);


int main() {
  HashTable* table = new HashTable();
  table -> size = 100;
  for (int x = 0; x <= 100; x++) {
    table->array[x] = NULL;
  }
  bool start = true;
  while (start == true) {
    char input[100];
    cout << "Enter a command" << endl;
    cin.getline(input, 100);
    if (strcmp(input, "ADD") == 0) {
      addStudent(table);
      cout << "Done" << endl;
    }
    else if (strcmp(input, "ADD RANDOM") == 0) {
      cout << "How many random students?" << endl;
    }
    else if (strcmp(input, "HELP") == 0) {
      cout << "Type ADD to add a student\nType PRINT to print list\nType DELETE to delete student\nType QUIT to quit" << endl; 
    }
    else if (strcmp(input, "PRINT") == 0) {
      print(table);
    }
    else if (strcmp(input, "DELETE") == 0) {
      
    }
    else if (strcmp(input, "QUIT") == 0) {
      start = false;
      break;
    }
    else if (strcmp(input, "TEST") == 0) {
      Student* newStu = new Student();
      strncpy(newStu -> fname, "Walter", 100);
      strncpy(newStu -> lname, "Hagerman", 100);
      newStu -> gpa = 3.9;
      newStu -> id = 23424;
      cout << hashFunction(newStu, 100) << endl;
    }
  }
}

Student* endList(Student* start) {
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
  int retNum = hashNum % size;
  return retNum;
}

void addStudent(HashTable* &table) {
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
  ptrStu -> gpa =  atoi(getGpa);
  int s = table -> size;
  int index = hashFunction(ptrStu, s);
  cout << index << endl;
  Student** arr = table -> array;
  if (arr[index] == NULL) {
    cout << "New" << endl;
    arr[index] = ptrStu;
  }
  else {
    endList(arr[index])-> next = ptrStu;
  }
  table->array = arr;
}

void deleteStu(vector<Student*>* stuList) {
  int del;
  cout<< "Enter id of student to delete" << endl;
  cin >> del;
}

void print(HashTable* table) {
  Student** arr = table->array;
  for (int c = 0; c <= table->size; c++) {
    if (arr[c] != NULL) {
      cout << "Found at index: " << c << endl;
      printRow(arr[c]);
    }
  }
}


Student* randomStu() {/*
  ifstream file;
  file.open(fname.txt); //Open the inputted file name
  char* output = new char[999];
  char* out = new char[999];
  int i = 0;
  while(!file.eof()) { //If has not reached end of file
    file.get(output[i]);
    i++;
  }
  int a = 0;
  if (output[a].isalpha() == true) {
    
  }
  else {
    
  }*/
}
