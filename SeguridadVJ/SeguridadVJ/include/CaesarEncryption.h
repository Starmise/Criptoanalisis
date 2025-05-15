#pragma once
#include "Prerequisites.h"

class
CaesarEncryption {
public:
  CaesarEncryption() = default;
  ~CaesarEncryption() = default;

  string
  EncryptionCaesar(const string& texto, int desplazamiento) {
    for (int i = 0; i < texto.size(); i++) {
      char posActual = texto[i];
      char posNueva = (posActual + desplazamiento) % alfabeto.size();

      respuesta += posNueva;
    }
    return respuesta;
  }

private:
  string alfabeto = "abcdefghijklmnopqrstuvwxyz";
  string respuesta = "";
};