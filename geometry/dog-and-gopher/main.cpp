#include<iostream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>

using namespace std;

struct point2D {
  float x, y;
};

istream& operator>> (istream& is, point2D& v){
  return is >> v.x >> v.y;
}

ostream& operator<< (ostream& os, point2D v){
  return os << fixed << setprecision(3) << "(" << v.x << "," <<  v.y << ")";
}

float euclideanDistance(point2D p1, point2D p2){
  return sqrt(pow(p2.x-p1.x, 2.0) + pow(p2.y-p1.y, 2.0));
}

int main(int argc, char** argv){
  int holeCount;
  point2D gopherPosition, dogPosition;
  while(!(cin >> holeCount).eof()){
    cin >> gopherPosition >> dogPosition;
    
    vector<point2D> holes;
    point2D hole;
    for(int count = 0; count < holeCount; count++){
      cin >> hole;
      holes.push_back(hole);
    }

    auto canEscape = [gopherPosition, dogPosition](point2D hole) -> bool {return euclideanDistance(hole, gopherPosition) * 2.0 <= euclideanDistance(hole, dogPosition);};

    vector<point2D>::iterator escapeHole = find_if(holes.begin(), holes.end(), canEscape);
    if (escapeHole == holes.end()) {
      cout << "The gopher cannot escape." << endl;
    } else {
    cout << "The gopher can escape through the hole at " << *escapeHole << "." << endl;
    }
  }

  return 0;
}
