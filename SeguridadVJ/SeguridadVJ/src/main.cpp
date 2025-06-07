#include "CaesarEncryption.h"
#include "Des.h"

int
main() {
  // std::bitset<64> plaintext("0001001000110100010101100111100010011010101111001101111011110001");
  std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");

  string phrase = "$good_faith$";

  // Asegurar que la frase tenga longitus múltiplo de 8
  while (phrase.size() % 8 != 0) {
    phrase += '\0'; // Espacio vacio
  }

  vector<bitset<64>> cipherBlocks;
  cout << "Texto origunal" << phrase << endl;
  cout << "Cifrado en hexadecimal: " << endl;

  // Cifrado DES
  DES des(key);
  for (size_t i = 0; i < phrase.size(); i += 8) {
    string block = phrase.substr(i, 8);
    auto blockBits = des.stringToBitset64(block);
    auto encrypted = des.encode(blockBits);
    cipherBlocks.push_back(encrypted);
    cout << std::hex << std::uppercase << std::setw(16) << std::setfill('0') << encrypted.to_ullong() << " ";
  }

  // Descifrado DES
  string output;
  for (const auto& block : cipherBlocks) {
    auto decrypted = des.decode(block);
    output += des.bitset64ToString(decrypted);
  }
  cout << "\n""Texto descifrado: " << phrase << endl;

  return 0;
}