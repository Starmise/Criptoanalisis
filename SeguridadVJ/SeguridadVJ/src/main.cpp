#include "CrytoGenerator.h"

int
main() {
  // 1) Initialize the random number generator
  CryptoGenerator cryptoGen;
  cryptoGen.generatePassword(16); // Generate a password of length 16

  // 2) Genereate 16 generic random bytes
  auto randomBytes = cryptoGen.generateBytes(16);
  //std::cout << "Random Bytes (hex): " <<< cryptoGen.toHex(randomBytes) << std::endl;

  return 0;
}