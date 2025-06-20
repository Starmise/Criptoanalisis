#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

class
Vignere {
public:
  Vignere() = default;

  Vignere(const std::string& key) : key(normalizeKey(key)) {
    if (key.empty()) {
      throw std::invalid_argument("No hay una llave con letras o puede estar vacia");
    }
  }

  static std::string
  normalizeKey(const std::string& rawKey) {
    std::string k;
    for (char c : rawKey) {
      if (isalpha(static_cast<unsigned char>(c))) {
        k += std::toupper(static_cast<unsigned char>(c)); // Convert to uppercase and append
      }
    }
    return k;
  }

  std::string 
  encode(const std::string& text) {
    std::string result;
    result.reserve(text.size()); // Reserve space for efficiency
    unsigned int i = 0; // Index for the key

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A'; // Determine base based on case

        // Desplazamiento de la key
        int shift = key[i % key.size()] - 'A'; // Calculate shift based on key character mod26
        // Encode
        char encodedChar = static_cast<char>((c - base + shift) % 26 + base);
        result += encodedChar; // Append encoded character to result
        i++; // Increment key index
      }
      else {
        result += c; // Non-alphabetic characters are added unchanged
      }
    }
    return result; // Return the encoded string
  }

  std::string 
  decode(const std::string& text) {
    std::string result;
    result.reserve(text.size()); // Reserve space for efficiency
    unsigned int i = 0; // Index for the key

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A'; // Determine base based on case

        // Desplazamiento de la key
        int shift = key[i % key.size()] - 'A'; // Calculate shift based on key character mod26
        // Encode
        char decodedChar = static_cast<char>(((c - base) - shift + 26) % 26 + base);
        result += decodedChar; // Append encoded character to result
        i++; // Increment key index
      }
      else {
        result += c; // Non-alphabetic characters are added unchanged
      }
    }
    return result; // Return the encoded string
  }

  std::string
  breakBruteForce(const std::string& text) {
    std::vector<std::string> fileNames = {
        "bin/adobe100.txt",
        "bin/bible.txt",
        "bin/elitehacker.txt",
        "bin/fortinet-2021_passwords.txt",
        "bin/Lizard-Squad.txt"
    };

    for (size_t i = 0; i < fileNames.size(); i++) {
      std::ifstream file(fileNames[i]);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << fileNames[i] << std::endl;
        continue;
      }

      while (std::getline(file, key)) {
        if (key.empty()) {
          continue;
        }

        std::string normKey = normalizeKey(text);
        std::string result = decode(text);

        XOREncoder xorE;

        if (xorE.isValidText(text)) {
          std::cout << "============================\n";
          std::cout << "Archivo: " << fileNames[i] << std::endl;
          std::cout << "Clave: " << key << std::endl;
          std::cout << "Texto posible: " << result << std::endl;
          return result;
        }
      }
      file.close();
    }
  }

private:
  std::string key; // The key used for Vignere cipher
};