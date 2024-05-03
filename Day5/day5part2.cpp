
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int checkForRepeatWithOneLetterBetween(string);
int checkForPairOfLettersThatAppearsAtLeastTwiceWithoutOverlapping(string);

int main() {
    std::ifstream file("input.txt");

  string inputLine;

  int nice = 0;
  while(getline(file, inputLine)) {
    if((checkForRepeatWithOneLetterBetween(inputLine) == 1) && (checkForPairOfLettersThatAppearsAtLeastTwiceWithoutOverlapping(inputLine) == 1)) {
      ++nice;
    }
  }

  cout << nice << endl;
  return 0;
}

int checkForRepeatWithOneLetterBetween(string inputString) {
  int flag = 0;
  string::size_type inputStringSize = inputString.size();
  for(string::size_type i = 0; i < (inputStringSize-2); ++i) {
    char currLetter = inputString[i];
    char nextLetter = inputString[i+2];
    if(currLetter == nextLetter) {
      flag = 1;
      break;
    }
  }

  return flag;
}

int checkForPairOfLettersThatAppearsAtLeastTwiceWithoutOverlapping(string inputString) {
  int flag = 0;
  string::size_type inputStringSize = inputString.size();
  for(string::size_type i = 0; i < (inputStringSize-3); ++i) {
    char currLetter = inputString[i];
    char nextLetter = inputString[i+1];
    for(string::size_type j = i+2 ; j < (inputStringSize-1); ++j) {
      char secondCurrLetter = inputString[j];
      char secondNextLetter = inputString[j+1];
      if((currLetter == secondCurrLetter) && (nextLetter == secondNextLetter)) {
        flag = 1;
        break;
      }
    }
    if(flag == 1) {
      break;
    }
  }

  return flag;
}
