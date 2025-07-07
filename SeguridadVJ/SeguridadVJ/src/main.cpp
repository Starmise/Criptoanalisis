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

  // 6) Safe release
  cryptoGen.secureWipe(iv);
  cryptoGen.secureWipe(salt);

  // 7) from Base64
  std::string base64String = cryptoGen.toBase64(salt); // Example Base64 string
  std::cout << "Base64: " << base64String << "\n";

  auto fromBase64 = cryptoGen.fromBase64(base64String);
  std::cout << "From Base64: " << cryptoGen.toHex(fromBase64) << "\n";

  // 8) Estimated Entropy
  auto entropy = cryptoGen.estimateEntropy(cryptoGen.generatePassword(16));
  std::cout << "Password 1: " << cryptoGen.generatePassword(16) << "\n";
  std::cout << "Estimated Entropy 1: " << entropy << "\n";
  auto entropy2 = cryptoGen.estimateEntropy("K0r0%Maru_Band8");
  std::cout << "Password 2: " << "K0r0%Maru_Band&" << "\n";
  std::cout << "Estimated Entropy 2: " << entropy2 << "\n";

  // 9) Best 3 passwords
  std::cout << "\n";
  auto best3 = cryptoGen.Best3ByEntropy(10);

  return 0;
}
