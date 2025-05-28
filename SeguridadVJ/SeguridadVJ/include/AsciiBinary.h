#pragma once
#include "Prerequisites.h"

class
AsciiBinary {
public:
  AsciiBinary() = default;
  ~AsciiBinary() = default;

  string 
  bitset(char c) {
    std::string result(8, '0');
    int value = static_cast<unsigned char>(c);
    for (int i = 7; i >= 0; --i) {
      if (value % 2 == 1) {
        result[i] = '1';
      }
      value /= 2;
    }
    return result;
  }

  string 
  stringToBinary(const string input) {
    std::ostringstream oss;
    for (char c : input) {
      oss << bitset(c) << " ";
    }
    return oss.str();
  }

  char 
  binaryToChar(const string& binary) {
    int value = 0;
    for (char bit : binary) {
      value = value * 2 + (bit - '0');
    }

    return static_cast<char>(value);
  }

  string
  binaryToString(const string& binaryInput) {
    std::istringstream iss(binaryInput);
    string result;
    string binary;

    while (iss >> binary) {
      result += binaryToChar(binary);
    }
    return result;
  }

private:

};