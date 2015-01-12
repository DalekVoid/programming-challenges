#include<iostream>
#include<vector>
#include<numeric>
#include<iterator>
#include<sstream>
// #include<stdio.h>  
using namespace std;

int main(int argc, char** argv){
  unsigned int numberOfStudents;
  while (cin >> numberOfStudents && numberOfStudents != 0) {
  vector<unsigned int> students(numberOfStudents);

  int dollars, cents;
  istringstream iss;
  string buffer;
  
  // get the remaining
  getline(cin, buffer);
  for (unsigned int i = 0; i < numberOfStudents; i++){
    getline(cin, buffer);
    // sanitize input
    // cout << buffer << endl;
    for(int i=0; i< buffer.length(); i++){
      char& c = buffer[i];
      if(c == '$' || c == '.')
        c = ' ';
    }
   // cout << buffer << endl;

    iss.clear();
    iss.str(buffer);
    iss >> dollars >> cents; 
    
    // cout << dollars << ',' << cents << endl;
    // scanf("%d.%d", &dollars, &cents);
    students.push_back(dollars*100 + cents);
  }

  unsigned int sum = accumulate(students.begin(), students.end(), 0);
//  cout << sum << endl;
  unsigned int mean = sum / numberOfStudents;

  unsigned int exchange = 0;
  unsigned int numberOfPaidMore = 0;
  for (vector<unsigned int>::iterator it = students.begin(); it!= students.end(); it++){
    if (*it> mean){
      numberOfPaidMore++;
      exchange += *it- mean;
    }
  }
  
  // if it is an uneven split
  unsigned int remain = sum % numberOfStudents;
  if (remain != 0){
    // retain amount for paid more students
    if (remain < numberOfPaidMore){
      // the excess can only satisfy a number of paid more students
      exchange -= remain;
    } else{
      // the excess cen satisfy paid more students plus may be some paid less/even students
      exchange -= numberOfPaidMore;
    }
  }

  cout.precision(2);
  cout << "$" << fixed << (double) exchange / 100.0 << endl;
  }

}

