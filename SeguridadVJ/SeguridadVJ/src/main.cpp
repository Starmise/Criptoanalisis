#include "CaesarEncryption.h"
#include "XOREncoder.h"
#include "AsciiBinary.h"

int
main() {
  string mensaje = "Sans e e e e e";
  string clave = "jackinthebox69";

  XOREncoder XORencoder;

  cout << "Mensaje original: " << mensaje << endl << "\n";

  cout << endl;
  string cifrado = XORencoder.encode(mensaje, clave);
  vector<unsigned char> bytesCifrados(cifrado.begin(), cifrado.end());

  XORencoder.bruteForceByFile(bytesCifrados, mensaje);


  /*AsciiBinary AB;

  string input = "Una vida para pintar";
  string binary = AB.stringToBinary(input);
  cout << "Texto a binario: " << binary << endl;

  string message = AB.binaryToString(binary);
  cout << "Binario a texto: " << message << endl;*/

  return 0;
}