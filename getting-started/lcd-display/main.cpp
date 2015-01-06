#include <iostream>
#include <sstream>
#include <string>

#define DEBUG false
#define _DEBUG if(DEBUG)
#define _TODO if(false)

using namespace std;

void print(unsigned int size, const string& str);
void printUpperBody(unsigned int size, const string& str);
void printMiddleBody(unsigned int size, const string& str);
void printLowerBody(unsigned int size, const string& str);
void printTail(unsigned int size, const string& str);

void print(unsigned int size, const string& str) {
  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    if(it != str.begin()) cout << " ";
    switch (*it) {
    case '1':
    case '4':
      cout << " " << string(size, ' ') << " ";
      break;
    default:
      cout << " " << string(size, '-') << " ";
      break;
    }
  }
  cout << endl;
  printUpperBody(size, str);
}

void printUpperBody(unsigned int size, const string& str) {
  ostringstream oss(ostringstream::out);

  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    if(it != str.begin()) oss << " ";
    switch (*it) {
    case '1':
    case '2':
    case '3':
    case '7':
      oss << " " << string(size, ' ') << "|";
      break;
    case '5':
    case '6':
      oss << "|" << string(size, ' ') << " ";
      break;
    default:
      oss << "|" << string(size, ' ') << "|";
      break;
    }
  }
  for (unsigned int i = 0; i < size; i++) {
    cout << oss.str() << endl;
  }
  printMiddleBody(size, str);
}

void printMiddleBody(unsigned int size, const string& str) {
  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    if(it != str.begin()) cout << " ";
    switch (*it) {
    case '1':
    case '7':
    case '0':
      cout << " " << string(size, ' ') << " ";
      break;
    default:
      cout << " " << string(size, '-') << " ";
      break;
    }
  }
  cout << endl;

  printLowerBody(size, str);
}

void printLowerBody(unsigned int size, const string& str) {
  ostringstream oss(ostringstream::out);

  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    if(it != str.begin()) oss << " ";

    switch (*it) {
    case '6':
    case '8':
    case '0':
      oss << "|" << string(size, ' ') << "|";
      break;
    case '2':
      oss << "|" << string(size, ' ') << " ";
      break;
    default:
      oss << " " << string(size, ' ') << "|";
      break;
    }
  }
  for (unsigned int i = 0; i < size; i++) {
    cout << oss.str() << endl;
  }

  printTail(size, str);
}

void printTail(unsigned int size, const string& str) {
  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    if(it != str.begin()) cout << " ";

    switch (*it) {
    case '1':
    case '4':
    case '7':
      cout << " " << string(size, ' ') << " ";
      break;
    default:
      cout << " " << string(size, '-') << " ";
      break;
    }
  }
  cout << endl;
}

int main() {
  unsigned int testcase = 0;
  unsigned int size;
  string displayNo;
  while (cin >> size >> displayNo) {
    if (size == 0 && displayNo == "0")
      break;

    //to separate diff testcase
    testcase++;
    /*
    if (testcase > 1)
      cout << endl;
      */

    print(size, displayNo);
    cout << endl;
  }
  return 0;
}
