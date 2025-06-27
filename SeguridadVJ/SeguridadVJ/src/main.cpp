#include "CrytoGenerator.h"

int
main() {
  // 1) Initialize the random number generator
  CryptoGenerator cryptoGen;
  cryptoGen.generatePassword(16); // Generate a password of length 16

  // 2) Genereate 16 generic random bytes
  auto randomBytes = cryptoGen.generateBytes(16);
  std::cout << "Random Bytes (hex): " << cryptoGen.toHex(randomBytes) << std::endl;

  // 3) AES Key of 128 buts
  auto key128 = cryptoGen.generateKey(128);
  std::cout << "Key 128-bit (hex): "<< cryptoGen.toHex(key128) << std::endl;

  // 4) IV of 128 bits (16 bytes)
  auto iv = cryptoGen.generateIV(16);
  std::cout << "IV 128-bit (hex): " << cryptoGen.toHex(iv) << "\n";

  // 5) Salt of 16 bytes
  auto salt = cryptoGen.generateSalt(8);
  std::cout << "Salt (Base64): " << cryptoGen.toBase64(salt) << "\n";

  return 0;
}