#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

struct candidate{
  string name;
  bool eliminated;
  int votes;
};

ostream& operator<< (ostream& os, const candidate& c){
  return os << c.name;
}

int main(int argc, char** argv){
  unsigned int numberOfCases;
  cin >> numberOfCases;
//  cout << "number of cases: " << numberOfCases << endl;
  while (numberOfCases > 0){
    string buffer;

    unsigned int numberOfCandidates;
    cin >> numberOfCandidates;
//    cout << "number of candidates: " << numberOfCandidates << endl;

    getline(cin, buffer);
    vector<candidate> candidates(numberOfCandidates);
    for (int i = 0; i < numberOfCandidates; i++){
      getline(cin, buffer);
      candidates[i] = candidate{buffer, false, 0};
    }

    /*
    for(vector<candidate>::const_iterator ii = candidates.begin(); ii != candidates.end(); ii++){
      cout << *ii << endl;
    }
    */

    istringstream iss;
    vector< vector<int> > votes;
    while(getline(cin, buffer)){
      if(buffer.compare("") == 0)
        break;

      iss.clear();
      iss.str(buffer);

      int selected;
      vector<int> vote;
      while(iss>>selected){
        vote.push_back(selected);
      }

      votes.push_back(vote);
    }

    /*
    for(int i = 0; i < votes.size(); i++){
      for(int j=0; j < votes[i].size(); j++){
        cout << votes[i][j] << " ";
      }
      cout << endl;
    }
    */

    bool no_found = true;
    while(no_found){
    // clean up
    for(int i =0; i < candidates.size(); i++)
      candidates[i].votes = 0;

    for(int i =0; i < votes.size(); i++)
      for(int j=0; j < votes[i].size(); j++)
        if(!candidates[votes[i][j]-1].eliminated){
          candidates[votes[i][j]-1].votes++;
          break;
        }
 
    // find max, min
    int max = 0;
    int min = 1001;
    for(int i = 0; i < candidates.size(); i++){
      if (candidates[i].votes > max){
        max = candidates[i].votes;
      }
      if (!candidates[i].eliminated && candidates[i].votes < min){
        min = candidates[i].votes;
      }
    }

    // if max > 50% vote
    // output candidate with max score
    if ( votes.size() - max < max){
      for(int i = 0; i < candidates.size(); i++){
        if(candidates[i].votes == max){
          cout << candidates[i] << endl;
          no_found = false;
          break;
        }
      }
    }
    // else
    // find # of candidates with max score
    // find # of cadidates eliminated
    else{
      int max_count = 0; 
      int elim_count = 0;
      for(int i = 0; i < candidates.size(); i++){
        if(candidates[i].eliminated){
          elim_count++;
        }
        else if(candidates[i].votes == max){
          max_count++;
        }
      }

    // if #max == total - #elim => output all names
        if( max_count == votes.size() - elim_count){
          for(int i = 0; i < candidates.size(); i++)
            if(!candidates[i].eliminated && candidates[i].votes == max){
              cout << candidates[i] << endl;
            }
          no_found = false;
        }
        else{
          for(int i = 0; i < candidates.size(); i++)
            if(!candidates[i].eliminated && candidates[i].votes == min){
              candidates[i].eliminated = true;
            }
        }
      }
    }
    
    if (numberOfCases-- > 1){
      cout << endl;
    }
  }
  return 0;
}
