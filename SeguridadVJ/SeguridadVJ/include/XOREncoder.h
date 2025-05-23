#pragma once
#include "Prerequisites.h"

class 
XOREncoder {
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

  void
  printHex(const string& input) {
    for (unsigned char c : input) {
      cout << hex << setw(2) << setfill('0') << (int)c << " ";
    }
  }

  bool 
  isValidText(const string& data) {
    return all_of(data.begin(), data.end(), [](unsigned char c) {
      return isprint(c) || isspace(c) || c == '\n' || c == ' ';
      });
  }

  void
  bruteForce_1Byte(const vector<unsigned char>& cifrado) {
    for (int clave = 0; clave < 256; clave++) {
      string result;

      for (unsigned char c : cifrado) {
        result += c ^ clave;
      }

      if (isValidText(result)) {
        cout << "============================\n";
        cout << "Clave 1 bytes: " << static_cast<char>(clave)
          << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
        cout << "Texto posible: " << result << "\n";
      }
    }
  }

  void
  bruteForce_2Byte(const vector<unsigned char>& cifrado) {
    for (int b1 = 0; b1 < 256; b1++) {
      for (int b2 = 0; b2 < 256; b2++) {
        string result;
        unsigned char key[2] = { static_cast<unsigned char>(b1), static_cast<unsigned char>(b2) };

        for (int i = 0; i < cifrado.size(); i++) {
          result += cifrado[i] ^ key[i % 2];
        }
        
        if (isValidText(result)) {
          cout << "============================\n";
          cout << "Clave 2 bytes: " << static_cast<char>(b1) << static_cast<char>(b2)
            << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
            << "0x " << std::setw(2) << std::setfill('0') << b2 << ")\n";
          cout << "Texto posible: " << result << "\n";
        }
      }
    }
  }

  void bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
    std::vector<std::string> clavesComunes = {
      "clave", "admin", "1234", "root", "test", "abc", "hola", "user",
      "pass", "12345", "0000", "password", "default", "Koromaru", "Sans e e e e e"
    };

    for (const auto& clave : clavesComunes) {
      std::string result;
      for (int i = 0; i < cifrado.size(); i++) {
        result += static_cast<unsigned char>(cifrado[i] ^ clave[i & clave.size()]);
      }

      if (isValidText(result)) {
        cout << "============================\n";
        cout << "Clave de diccionario: " << clave << "\n";
        cout << "Texto posible: " << result << "\n";
      }
    }
  }


private:

};
