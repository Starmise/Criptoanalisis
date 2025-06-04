#include "CaesarEncryption.h"
#include "Des.h"

int
main() {
  std::bitset<64> plaintext("0001001000110100010101100111100010011010101111001101111011110001");
  std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");

  DES des(key);
  bitset<64> ciphertext = des.encode(plaintext);
  cout << "Cifrado: " << ciphertext << endl;

  return 0;
}