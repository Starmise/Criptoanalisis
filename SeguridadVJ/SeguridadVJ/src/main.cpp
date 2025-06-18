#include "Vignere.h"

int
main() {
  std::string text = "For Those Who Come After";
  std::string key = "R3v3rs0";

  std::cout << "Texto original: " << text << std::endl;
  std::cout << "Clave: " << key << std::endl;

  Vignere vignere(key);
  std::string encrypted = vignere.encode(text);
  std::cout << "Texto cifrado: " << encrypted << std::endl;

  std::string decrypted = vignere.decode(encrypted);
  std::cout << "Texto descifrado: " << decrypted << std::endl;

  return 0;
}