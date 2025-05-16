#include "CaesarEncryption.h"

int 
main() {
  string texto;
  int desplazo;

  cout << "Escribe el mensaje a encriptar: " << endl;;
  getline(cin, texto);

  cout << "Escribe el valor de desplazamiento: " << endl;;
  cin >> desplazo;

  CaesarEncryption cifrado;
  string mensjaeCifrado = cifrado.EncryptionCaesar(texto, desplazo);
  cout << "El mensaje cifrado es: " << mensjaeCifrado << endl;

  string descifrado = cifrado.DecodeCaesar(mensjaeCifrado, desplazo);
  cout << "El mensaje descifrado es: " << descifrado << endl;

  return 0;
}