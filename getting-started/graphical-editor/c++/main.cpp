#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

class Image{
public:
  Image(unsigned int width, unsigned int height){
    if (width>0 && height>0){
      for (int i = 0; i < height; i++){
        this->canvas.push_back(vector<char>(width, 'O'));
      }
    }
  }

  ~Image(){
  }

  // convenience methods
  unsigned int width() const{
    return this->canvas[0].size();
  }

  unsigned int height() const{
    return this->canvas.size();
  }

  bool checkHeightBound(int value) const{
    return value >= 0 && value < height();
  }

  bool checkWidthBound(int value) const{
    return value >= 0 && value < width();
  }

  void paint(int x, int y, char color){
    if(checkHeightBound(y) && checkWidthBound(x))
      canvas[y][x] = color;
  }
  
  void fill(int x, int y, char color){
    if(checkHeightBound(y) && checkWidthBound(x))
      fillImp(x, y, canvas[y][x], color);
  }

  void clear(){
    for(unsigned j = 0; j < height(); j++){
      for(unsigned i = 0; i < width(); i++){
        canvas[j][i] = 'O';
      }
    }
  }

friend ostream& operator<< (ostream& os, const Image& img);

private:
  vector< vector<char> > canvas;

  void fillImp(int x, int y, char fromColor, char toColor){
    if (checkHeightBound(y) && checkWidthBound(x) && canvas[y][x] == fromColor && fromColor != toColor){
      canvas[y][x] = toColor;
      fillImp(x-1, y, fromColor, toColor);
      fillImp(x, y-1, fromColor, toColor);
      fillImp(x+1, y, fromColor, toColor);
      fillImp(x, y+1, fromColor, toColor);
    }
  }
};

ostream& operator<< (ostream& os, const Image& img){
  if (img.canvas.size() != 0){
    for(unsigned j = 0; j < img.height(); j++){
      for(unsigned i = 0; i < img.width(); i++){
        os << img.canvas[j][i]; 
      }
      os << endl;
    }
  }
  return os;
}

int main(int argc, char** argv){
  Image* img = NULL;
  char code;
  char color;
  unsigned int width, height;
  unsigned int x, y, x1, x2, y1, y2;
  bool terminate = false;
  string name;

  istringstream iss;
  string command;
  while(!terminate){
    getline(cin, command);
    iss.clear();
    iss.str(command);

    iss >> code;
    switch(code){
      case 'I':
        iss >> width >> height;
        if (img != NULL)
          delete img;
        img = new Image(width, height);
        break;
      case 'C':
        if (img != NULL)
          img->clear();
        break;
      case 'L':
        iss >> x >> y >> color;
        if (img != NULL)
          img->paint(x-1, y-1, color);
        break;
      case 'V':
        iss >> x >> y1 >> y2 >> color;
        if (img != NULL){
          for (int y = y1;;){
            img->paint(x-1, y-1, color);
            if (y == y2)
              break;
            else if (y1 < y2)
              y++;
            else
              y--;
          }
        }
        break;
      case 'H':
        iss >> x1 >> x2 >> y >> color;
        if (img != NULL){
          for (int x = x1;;){
            img->paint(x-1, y-1, color);
            if (x == x2)
              break;
            else if (x1 < x2)
              x++;
            else
              x--;
          }
        }
        break;
      case 'K':
        iss >> x1 >> y1 >> x2 >> y2 >> color;
        if (img != NULL){
          for (int x = x1;;){
            for (int y = y1;;){
              img->paint(x-1, y-1, color);
              if (y == y2)
                break;
              else if (y1 < y2)
                y++;
              else
                y--;
            }
            if (x == x2)
              break;
            else if (x1 < x2)
              x++;
            else
              x--;
          }
        }
        break;
      case 'F':
        iss >> x >> y >> color;
        if (img != NULL){
          img->fill(x-1, y-1, color);
        }
        break;
      case 'S':
        iss >> name;
        if (img != NULL){
          cout << name << endl;
          cout << *img;
        }
        break;
      case 'X':
        if (img != NULL)
          delete img;
        terminate = true;
        break;
      default:
        break;
        // do nothing
    }
  }
  return 0;
}
