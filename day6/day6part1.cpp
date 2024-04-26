#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string>& split(const string&, char, vector<string>&);
vector<string>  split(const string&, char);

int main() {
  string inputLine;
  std::ifstream file("input.txt");

  int* lightGrid = (int*)calloc(1000*1000,sizeof(int));
  int numLights = 0;

  while(getline(file, inputLine)) {
    vector<string> spaceParsedInputLine = split(inputLine, ' ');
    string dir1 = spaceParsedInputLine.at(0);
    if(dir1 == "turn") {
      string dir2 = spaceParsedInputLine.at(1);
      string xy1 = spaceParsedInputLine.at(2);
      string xy2 = spaceParsedInputLine.at(4);
      vector<string> parsedXY1 = split(xy1, ',');
      vector<string> parsedXY2 = split(xy2, ',');
      int x1 = stoi(parsedXY1.at(0));
      int y1 = stoi(parsedXY1.at(1));
      int x2 = stoi(parsedXY2.at(0));
      int y2 = stoi(parsedXY2.at(1));
      for(int x = x1; x <= x2; ++x) {
        for(int y = y1; y <= y2; ++y) {
          if(dir2 == "on") {
            *(lightGrid + x + (1000*y)) = 1;
          } else if(dir2 == "off") {
            *(lightGrid + x + (1000*y)) = 0;
          } else {
            cout << "ERROR2" << endl;
          }
        }
      }
    } else if(dir1 == "toggle") { // [dir1 coord1 through coord2]
      string xy1 = spaceParsedInputLine.at(1);
      string xy2 = spaceParsedInputLine.at(3);
      vector<string> parsedXY1 = split(xy1, ',');
      vector<string> parsedXY2 = split(xy2, ',');
      int x1 = stoi(parsedXY1.at(0));
      int y1 = stoi(parsedXY1.at(1));
      int x2 = stoi(parsedXY2.at(0));
      int y2 = stoi(parsedXY2.at(1));
      for(int x = x1; x <= x2; ++x) {
        for(int y = y1; y <= y2; ++y) {
          *(lightGrid + x + (1000*y)) ^= 1; // Logical Exclusive-OR (XOR) flipping
        }
      }
    } else {
      cout << "ERROR1" << endl;
    }
  }

  for(int i = 0; i < 1000*1000; ++i) {
    if((*(lightGrid + i)) == 1) {
      ++numLights;
    }
  }

  cout << "Num lights: " << numLights << endl;

  free(lightGrid);
  return 0;
}

vector<string>& split(const string& s, char delim, vector<string>& elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string& s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}