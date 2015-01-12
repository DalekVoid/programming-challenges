#include<iostream>
using namespace std;

struct image{
  unsigned int width;
  unsigned int height;
  char *canvas;
};

bool checkBound(int value, int limit){
  return value >=1 && value <= limit;
}

void paint(char* image, int width, int height, int x, int y, char color){
  if(checkBound(x, width) && checkBound(y, height))
    *(image + y*width + x) = color;
}
 
void print(char* image, int width, int height){
  for(unsigned j = 0; j < height; j++){
    for(unsigned i = 0; i < width; i++){
      cout << *(image + j*width + width);
    }
    cout << endl;
  }
}

void clear(image img){
  if (img.canvas != NULL){
    memset((void*)img.canvas, 'O', img.width*img.height);
  }
}


int main(int argc, char** argv){
  char *image;
  char command;
  char color;
  unsigned int width, height;
  unsigned int x, y;
  bool terminate = false;

  while(!terminate && cin >> command){
    switch(command){
      case 'I':
        cin >> width >> height;
        image = new char[width*height];
        memset((void*)image, 'O', width*height);
        break;
      case 'C':

      case 'L':
        cin >> x >> y >> color;
        paint(image, width, height, x, y, color);
        break;
      case 'V':
        break;
      case 'H':
        break;
      case 'K':
        break;
      case 'F':
        break;
      case 'S':
        break;
      case 'X':
        terminate = true;
        break;
      default:
        break;
        // do nothing
    }
  }
  return 0;
}
