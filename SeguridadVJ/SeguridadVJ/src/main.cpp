#include "CaesarEncryption.h"

int 
main() {
  string texto;

  cout << "Escribe el mensaje a encriptar: " << endl;;
  cin >> texto;

  CaesarEncryption cifrado;
  string mensjaeCifrado = cifrado.EncryptionCaesar(texto, 4);
  cout << "El mensaje cifrado es: " << mensjaeCifrado << endl;

  return 0;
}