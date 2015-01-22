#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<vector>
#include<iterator>

using namespace std;

bool caseInsensitivePredicate(char i, char j){
  if (i == j){
    return true;
  } else{
    char diff;
    diff = (i < j)? (j - i) : (i - j);
    return diff == 'a' - 'A';
  }
}

int main(int argc, char** argv){
  int numberOfCase;
  cin >> numberOfCase;
  while(numberOfCase > 0){
    int row;
    int column;
    cin >> row >> column;
    
    int numberOfWords;

    vector<string> grid(row, "");

    string buffer;

    cin.ignore(256, '\n'); //eat the linebreak after row and column input.

    // read character grid
    for( int i = 0; i < grid.size(); i++){
      getline(cin, buffer);
      grid[i] = buffer;
    }
    
    /*
    for(vector<string>::iterator it = grid.begin(); it != grid.end(); it++){
      cout << *it << endl;
    }
    */

    cin >> numberOfWords;
    vector<string> words(numberOfWords, "");

    cin.ignore(256, '\n'); // ignore newline after numebrOfWord from input
    // read words
    for(vector<string>::iterator it = words.begin(); it != words.end(); it++){
      getline(cin, buffer);
      *it = buffer;
    }

    
    // Construct a vertical grid
    vector<string> vGrid(column, string(row, 0));
    for( int i = 0; i < column; i++){
      for( int j = 0; j < row; j++){
        vGrid[i][j] = grid[j][i];
      }
    }

    // Construct a diagonal grid along NE
    vector<string> dGridNE(row + column - 1, "");
    int rowCounter = row;
    int columnCounter = 0;
    for( int i = 0; i < dGridNE.size(); i++) {
      if( rowCounter > 0){
        // starting with row triangle
        rowCounter--;

        int r = rowCounter;
        int c = columnCounter;
        while( r < row && c < column){
          // cout << grid[r][c];
          dGridNE[i] += grid[r][c];
          r++;
          c++;
        }
        // cout << endl;
      } else {
        // then column triangle
        columnCounter++;

        int r = rowCounter;
        int c = columnCounter;
        while( r < row && c < column){
          dGridNE[i] += grid[r][c];
          r++;
          c++;
        }
      }
    }

    
    for(vector<string>::iterator it = dGridNE.begin(); it != dGridNE.end(); it++){
      cout << *it << endl;
    }
    // Construct a diagonal grid along SW
   
    vector<string> dGridSW(row + column - 1, "");
    rowCounter = 0;
    columnCounter = 0;
    for( int i = 0; i < dGridSW.size(); i++) {
      if( columnCounter < column){
        // starting with row triangle
        int r = rowCounter;
        int c = columnCounter;
        while( r < row && c >= 0){
          // cout << grid[r][c];
          dGridSW[i] += grid[r][c];
          r++;
          c--;
        }
        columnCounter++;
        // cout << endl;
      } else {
        // then column triangle
        rowCounter++;

        int r = rowCounter;
        int c = column - 1;
        while( r < row && c >= 0 ){
          dGridSW[i] += grid[r][c];
          r++;
          c--;
        }
      }
    }

    for(vector<string>::iterator it = dGridSW.begin(); it != dGridSW.end(); it++){
      cout << *it << endl;
    }
    // Conduct search from top to bottom, left to right.
    // Find row match
    string::iterator location;
    string::reverse_iterator rlocation;
    for( int i = 0; i < words.size(); i++){
      // find row match
      for( int j = 0; j < grid.size(); j++){
        location = search(grid[j].begin(), grid[j].end(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (location != grid[j].end()){
          cout << j+1 << " " << location - grid[j].begin() +1 << endl;
          break;
        }

        rlocation = search(grid[j].rbegin(), grid[j].rend(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (rlocation != grid[j].rend()){
          cout << j+1 << " " << grid[j].rend() - rlocation << endl;
          break;
        }
      }

      // find column match
      for( int j = 0; j < vGrid.size(); j++){
        location = search(vGrid[j].begin(), vGrid[j].end(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (location != vGrid[j].end()){
          cout << location - vGrid[j].begin() + 1 << " " << j+1 << endl;
          break;
        }

        rlocation = search(vGrid[j].rbegin(), vGrid[j].rend(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (rlocation != vGrid[j].rend()){
          cout << vGrid[j].rend() - rlocation << " " << j+1 << endl;
          break;
        }
      }

      // find diagonal match
      // find diagonal NE match
      for( int j = 0; j < dGridNE.size(); j++){
        location = search(dGridNE[j].begin(), dGridNE[j].end(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (location != dGridNE[j].end()){
          cout << "NE " << j+1 << " " << location - dGridNE[j].begin() << endl;
          break;
        }

        rlocation = search(dGridNE[j].rbegin(), dGridNE[j].rend(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (rlocation != dGridNE[j].rend()){
          cout << "NE " << j+1 << " " << dGridNE[j].rend() - rlocation << endl;
          break;
        }
      }
      // find diagonal SW match
      for( int j = 0; j < dGridSW.size(); j++){
        location = search(dGridSW[j].begin(), dGridSW[j].end(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (location != dGridSW[j].end()){
          cout << "SW " << j+1 << " " << location - dGridSW[j].begin() << endl;
          break;
        }

        rlocation = search(dGridSW[j].rbegin(), dGridSW[j].rend(), words[i].begin(), words[i].end(), caseInsensitivePredicate);
        if (rlocation != dGridSW[j].rend()){
          cout << "SW " << j+1 << " " << dGridSW[j].rend() - rlocation << endl;
          break;
        }
      }

    }

    numberOfCase--;
  }
  return 0;
}
