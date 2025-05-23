#include "CaesarEncryption.h"
#include "XOREncoder.h"

int
main() {
  string mensaje = "Sans e e e e e";
  string clave = "clave";

  XOREncoder XORencoder;

  cout << "Mensaje original: " << mensaje << endl << "\n";

  cout << endl;
  string cifrado = XORencoder.encode(mensaje, clave);
  cout << "Mensaje cifrado: " << cifrado << endl;
  cout << endl;

  cout << "Texto cifrado (hex): ";
  XORencoder.printHex(cifrado);
  cout << endl;
  cout << endl << "\n";

  string descifrado = XORencoder.encode(cifrado, clave);
  cout << "Mensaje descifrado: " << descifrado << std::endl;

  vector<unsigned char> bytesCifrados(cifrado.begin(), cifrado.end());

  cout << "\n--- Fuerza bruta (1 byte) con filtro ---\n";
  XORencoder.bruteForce_1Byte(bytesCifrados);

  cout << "\n--- Fuerza bruta (2 byte) con filtro ---\n";
  XORencoder.bruteForce_2Byte(bytesCifrados);

  cout << "\n--- Fuerza bruta (diccionario de claves) ---\n";
  XORencoder.bruteForceByDictionary(bytesCifrados);

  return 0;
}