#include "Vignere.h"

int
main() {
  std::string text = "For Those Who Come After";
  std::string key = "Devida";

  std::cout << "Texto original: " << text << std::endl;
  std::cout << "Clave: " << key << std::endl;

  Vignere vignere(key);
  std::string encrypted = vignere.encode(text);
  std::cout << "Texto cifrado: " << encrypted << std::endl;

 /* std::string decrypted = vignere.decode(encrypted);
  std::cout << "Texto descifrado: " << decrypted << std::endl;*/

  std::string brute = vignere.breakEncode(encrypted, 5);
  std::cout << "Texto descifrado: " << brute << std::endl;

  return 0;
}