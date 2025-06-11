#pragma once
#include "Prerequisites.h"

class
AsciiBinary {
public:
  /**
  * @brief Constructor y Destructor por defecto
  */
  AsciiBinary() = default;
  ~AsciiBinary() = default;

  /**
   * @brief Convierte un car�cter ASCII a su representaci�n binaria de 8 bits.
   * @param c Caracter a convertir.
   * @return Cadena de 8 caracteres que representa cada valor binario.
   */
  std::string
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

  /**
   * @brief Convierte una cadena de texto a su representaci�n binaria.
   * @param input Texto a convertir.
   * @return Cadena con valores binarios separados donde cada caracter vale 8 bits.
   */
  std::string
  stringToBinary(const std::string input) {
    std::ostringstream oss;
    for (char c : input) {
      oss << bitset(c) << " ";
    }
    return oss.str();
  }

  /**
   * @brief Convierte una cadena de 8 bits a su car�cter ASCII equivalente.
   * @param binary Cadena de 8 bits a convertir.
   * @return Caracter correspondiente al valor binario ingresado.
   */
  char 
  binaryToChar(const std::string& binary) {
    int value = 0;
    for (char bit : binary) {
      value = value * 2 + (bit - '0');
    }

    return static_cast<char>(value);
  }

  /**
   * @brief Convierte una cadena completa de m�ltiples bloques de 8 bits a texto ASCII.
   * @param binaryInput Cadena de binarios (ej.: "01001000 01101111 ...").
   * @return Texto resultante de convertir cada bloque a su caracter correspondiente.
   */
  std::string
  binaryToString(const std::string& binaryInput) {
    std::istringstream iss(binaryInput);
    std::string result;
    std::string binary;

    while (iss >> binary) {
      result += binaryToChar(binary);
    }
    return result;
  }

private:

};