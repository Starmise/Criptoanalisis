#pragma once
#include "Prerequisites.h"

class
CaesarEncryption {
public:
  /**
  * @brief Constructor y Destructor por defecto
  */
  CaesarEncryption() = default;
  ~CaesarEncryption() = default;

  /**
   * @brief Cifra un texto usando el cifrado C�sar con un valor de desplazamiento dado.
   * @param texto Texto original que se debe cifrar.
   * @param desplazamiento N�mero de posiciones a desplazar cada letra.
   * @return Texto cifrado.
   */
  std::string
  EncryptionCaesar(const std::string& texto, int desplazamiento) {
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

  /**
   * @brief Descifra un texto cifrado con el cifrado C�sar usando un desplazamiento dado.
   * @param texto Texto cifrado que se desea descifrar.
   * @param desplazamiento Desplazamiento usado originalmente para cifrar.
   * @return Texto descifrado.
   */
  std::string
  DecodeCaesar(const std::string& texto, int desplazamiento) {
    return EncryptionCaesar(texto, 26 - (desplazamiento % 26));
  }

  /**
   * @brief Ataque por fuerza bruta probando todas las posibles claves para descifrar un texto.
   * @param texto Texto cifrado sobre el cual se va a aplicar fuerza bruta.
   */
  void
  bruteForce(const std::string& texto) {
    for (int i = 0; i < 26; i++) {
      std::string attempt = EncryptionCaesar(texto, 26 - i);
      std::cout << "Inteto: " << i << ": " << attempt << std::endl;
    }
  }

  /**
   * @brief Calcula una posible clave analizando las frecuencias de letras en el texto.
   * @param texto Texto cifrado donde la clave es desconocida.
   * @return Clave Probable valor de desplazamiento usado para cifrar el texto.
   */
  int
  evaluatePossibleKey(const std::string& texto) {
    int frecuencias[26] = { 0 }; // Arreglo de frecuencias para contar cu�ntas veces aparece cada letra

    // Se recorre todo el texto y aumenta la frecuencia sin importar si es may�scula o min�scula
    for (char c : texto) {
      if (c >= 'A' && c <= 'Z') {
        frecuencias[c - 'A']++;
      }
      else if (c >= 'a' && c <= 'z') {
      
      frecuencias[c - 'a']++;
      }
      // No se aumenta la frecuencia si no es una letra
    }

    int indexMax = 0; // Indice de la letra con mayor frecuencia
    // Se busca la letra m�s com�n en el arreglo de frecuencia
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