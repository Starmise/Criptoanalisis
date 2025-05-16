#pragma once
#include "Prerequisites.h"

class
  CaesarEncryption {
public:
  CaesarEncryption() = default;
  ~CaesarEncryption() = default;

  string
  EncryptionCaesar(const string& texto, int desplazamiento) {
    std::string result = "";

    for (char c : texto) {
      if (c >= 'A' && c <= 'Z') {
        result += (char)(((c - 'A' + desplazamiento) % 26) + 'A');
      }
      else if (c >= 'a' && c <= 'z') {
        result += (char)(((c - 'a' + desplazamiento) % 26) + 'a');
      }
      else if (c >= '0' && c <= '9') {
        result += (char)(((c - '0' + desplazamiento) % 10) + '0');
      }
      else {
        result += c;
      }
    }
    return result;
  }

  string
  DecodeCaesar(const string& texto, int desplazamiento) {
    return EncryptionCaesar(texto, 26 - (desplazamiento % 26));
  }

  void
  bruteForce(const string& texto) {
    for (int i = 0; i < 26; i++) {
      string attempt = EncryptionCaesar(texto, 26 - i);
      cout << "Inteto: " << i << ": " << attempt << endl;
    }
  }


  int
  evaluatePossibleKey(const std::string& texto) {
    int frecuencias[26] = { 0 };

    for (char c : texto) {
      if (c >= 'A' && c <= 'Z') {
        frecuencias[c - 'A']++;
      }
      else if (c >= 'a' && c <= 'z') {
      
      frecuencias[c - 'a']++;
      }
    }

    int indexMax = 0;
    for (int i = 0; i < 26; i++) {
      if (frecuencias[i] > frecuencias[0]) {
        indexMax = i;
      }
    }

    int possibleKey = (indexMax - ('e' - 'a') + 26) % 26;
    return possibleKey;
  }

private:

};

/*
* ----------2nd Attempt-----------
* for (int i = 0; i < texto.size(); i++) {
      char posActual = texto[i];

      char posNueva = ((posActual + desplazamiento)) % alfabeto.size() + 'a';

      respuesta += posNueva;
    }
    return respuesta;
*/