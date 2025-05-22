#pragma once
#include "Prerequisites.h"

class XOREncoder
{
public:
  XOREncoder() = default;
  ~XOREncoder() = default;

  // Encodes the input string using XOR with the provided key.
  // Input: The string to be encoded. -> Hola Mundo
  // Key: The key to be used for encoding. -> clave
  string
  encode(const std::string& input, const std::string& key) {
    string output = input;
    for (int i = 0; i < input.size(); i++) {
      output[i] = input[i] ^ key[i % key.size()];
    }

    return output;
  }

  // Transform text to decimal(hex) representation
  vector<unsigned char> 
  HexToBytes(const string& input) {
    vector<unsigned char> bytes;
    istringstream iss(input);
    string hexVal;

    while (iss >> hexVal) {
      if (hexVal.size() == 1) {
        hexVal = "0" + hexVal;
      }
      unsigned int byte;
      stringstream ss;
      ss << hex << hexVal;
      ss >> byte;
      bytes.push_back(static_cast<unsigned char>(byte));
    }
    return bytes;
  }

private:

};
