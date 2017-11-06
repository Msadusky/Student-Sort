//=============================================================================
// Mike Sadusky
// Outputs class roster in requested format.
//=============================================================================

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;  using std::sort;
using std::unique;

void readRoster(vector<string>& roster, string fileName);  // reading a list from a fileName
void printRosterVect(const vector<string>& roster); //printing vector out

int main(){
   vector <string> courseStudents; // vector of courses of students
   vector <string> finalStudents;
   vector <string> roster;
   vector<string> cs1Names;
   vector<string> cs2Names;
   vector<string> cs3Names;
   string firstName;
   string lastName;
   string fullName;
   string cs1 = "CS1\t";
   string cs2 = "CS2\t";
   string cs3 = "CS3\t";
   ifstream file;

   // reading in rosters per course and printing them out
   readRoster(roster, "cs1.txt");
   readRoster(roster, "cs2.txt");
   readRoster(roster, "cs3.txt");
   courseStudents = move(roster);
   roster.clear();

   // reading in dropouts
   vector<string> dropouts;
   readRoster(dropouts, "dropouts.txt");

   vector<string> allStudents;  // master vector of students
   for(vector<string>::const_iterator lst = courseStudents.begin(); lst != courseStudents.end(); ++lst) // inserting individual courses
      allStudents.push_back(*lst);

   sort(allStudents.begin(), allStudents.end()); // sorting master list

   vector<string>::iterator iter;
   iter = unique(allStudents.begin(), allStudents.end()); // eliminating duplicates
   allStudents.resize(std::distance(allStudents.begin(), iter));

   for (int i = 0; i < dropouts.size(); ++i)  // removing individual dropouts
   {
      string str = dropouts[i];
      allStudents.erase(remove(allStudents.begin(), allStudents.end(), str), allStudents.end());
      str.clear();
   }

   for(vector<string>::const_iterator vct = allStudents.begin(); vct != allStudents.end(); ++vct)
      finalStudents.push_back(*vct);

   for(unsigned int it = 0; it < finalStudents.size(); ++it)
   {
      string temp;
      string fname;
      string lname;
      int i = 0;
      temp = finalStudents[it];
      while(temp[i] != ' ')
      {
         lname += temp[i];
         ++i;
      }
      ++i;
      while(temp[i] != ' ')
      {
         fname += temp[i];
         ++i;
      }
      temp.clear();
      if(fname.size() >= 8)
      {
         fname += "\t";
      }
      else
      {
         fname += "\t\t";
      }
      if(lname.size() >= 8)
      {
         lname += "\t";
      }
      else
      {
         lname += "\t\t";
      }
      temp = fname + lname;
      finalStudents[it] = temp;
   }

// ============================================================================

   file.open("cs1.txt", std::ifstream::in);
   while(!file.eof())
    {
        file >> firstName;
        file >> lastName;
      if(firstName.size() >= 8)
      {
         firstName += "\t";
      }
      else
      {
         firstName += "\t\t";
      }
      if(lastName.size() >= 8)
      {
         lastName += "\t";
      }
      else
      {
         lastName += "\t\t";
      }
        fullName = firstName + lastName;
        cs1Names.push_back(fullName);
    }
    file.close();

    file.open("cs2.txt", std::ifstream::in);
    while(!file.eof())
    {
        file >> firstName;
        file >> lastName;
      if(firstName.size() >= 8)
      {
         firstName += "\t";
      }
      else
      {
         firstName += "\t\t";
      }
      if(lastName.size() >= 8)
      {
         lastName += "\t";
      }
      else
      {
         lastName += "\t\t";
      }
        fullName = firstName + lastName;
        cs2Names.push_back(fullName);
    }
    file.close();

    file.open("cs3.txt", std::ifstream::in);
    while(!file.eof())
    {
        file >> firstName;
        file >> lastName;
      if(firstName.size() >= 8)
      {
         firstName += "\t";
      }
      else
      {
         firstName += "\t\t";
      }
      if(lastName.size() >= 8)
      {
         lastName += "\t";
      }
      else
      {
         lastName += "\t\t";
      }
        fullName = firstName + lastName;
        cs3Names.push_back(fullName);
    }
    file.close();

// ============================================================================

   for(unsigned int i = 0; i < finalStudents.size(); ++i)
    {
        for(unsigned int it = 0; it < cs1Names.size(); ++it)
        {
            if(cs1Names[it] == finalStudents[i])
            {
                finalStudents[i] = finalStudents[i] + cs1;
            }
        }

        for(unsigned int it = 0; it < cs2Names.size(); ++it)
        {
            if(cs2Names[it] == finalStudents[i] || cs2Names[it] + cs1 == finalStudents[i])
            {
                finalStudents[i] = finalStudents[i] + cs2;
            }
        }

        for(unsigned int it = 0; it < cs3Names.size(); ++it)
        {
            if(cs3Names[it] == finalStudents[i] || cs3Names[it] + cs2 == finalStudents[i] || cs3Names[it] + cs1 == finalStudents[i] || cs3Names[it] + cs1 + cs2 == finalStudents[i])
            {
                finalStudents[i] = finalStudents[i] + cs3;
            }
        }
    }

    cout << "All Students" << endl;
    cout << "First Name\tLast Name\tCourses Enrolled" << endl;
    cout << endl;
   printRosterVect(finalStudents);
   cout << endl;
   cout << "Type anything and press return to exit" << endl;

   char c;
   std::cin >> c;
}

// reading a list from fileName
void readRoster(vector<string>& roster, string fileName){
   ifstream course(fileName.c_str());
   while(!course.eof()){
      string firstName;
      string lastName;
      string fullName;
      course >> firstName;
      course >> lastName;
      fullName = lastName + " " + firstName + " ";
      roster.push_back(fullName);
   }
   course.close();
}

void printRosterVect(const vector<string>& roster){
   for(vector<string>::const_iterator str = roster.begin(); str != roster.end(); ++str)
   {
      cout << *str << endl;
   }
}
