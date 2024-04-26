#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

struct wrappingBox{

    int length;
    int width;
    int height;

     wrappingBox(int length, int width, int height) : length(length), width(width), height(height) {}

};

int getSmallestSideArea(int l, int w, int h) {
  int side1 = l*w;
  int side2 = w*h;
  int side3 = h*l;
  
  int smallestSideArea = side1;
  
  if(side2 < smallestSideArea) {
    smallestSideArea = side2;
  }
  if(side3 < smallestSideArea) {
    smallestSideArea = side3;
  }
  
  return smallestSideArea;
}

int getSmallestSidePerimeter(wrappingBox box) {
  int side1 = box.length + box.length + box.width + box.width;
  int side2 = box.width + box. width + box.height + box.height;
  int side3 = box.height + box.height + box.length + box.length;
  
  int smallestSidePerimeter = side1;
  
  if(side2 < smallestSidePerimeter) {
    smallestSidePerimeter = side2;
  }
  if(side3 < smallestSidePerimeter) {
    smallestSidePerimeter = side3;
  }
  
  return smallestSidePerimeter;
}

int getVolume(wrappingBox box){
    return box.length*box.width*box.height;
}

int main() {
    // Open the file for reading
    std::ifstream file("input.txt");
    std::vector<wrappingBox> vec;

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1; // Exit the program with an error code
    }

    // Read the file line by line
    std::string line;
  while (std::getline(file, line)) {
        std::istringstream iss(line);
        int length, width, height;
        char delimiter;
        if (iss >> length >> delimiter >> width >> delimiter >> height) {
            vec.push_back(wrappingBox(length, width, height));
        } else {
            std::cerr << "Error: Invalid line format." << std::endl;
        }
    }

    long long sum{0};
        for (const auto& box : vec) {
            sum += getSmallestSidePerimeter(box);
            sum += getVolume(box);
    }
        std::cout << "ribbon: " << sum << std::endl;


    // Close the file
    file.close();

    return 0;
}
