#include "CrytoGenerator.h"
#include "SensitiveInfoCypher.h"

int
main() {
  // 1) Initialize the random number generator
  CryptoGenerator cryptoGen;
  cryptoGen.generatePassword(16); // Generate a password of length 16

  // 2) Best 3 passwords
  std::cout << "\n";
  auto best3 = cryptoGen.Best3ByEntropy(10);

  std::cout << "----------------------------------------------------------------" << "\n";

  SensitiveInfoCypher sensReader;

  if (sensReader.LoadFile("bin/SensInfo.txt")) {
    std::cout << "Data loaded succesfully" << std::endl;
    sensReader.printData(sensReader.getData());
  }
  else {
    std::cerr << "Failed while loading the file" << std::endl;
  }

  return 0;
}
