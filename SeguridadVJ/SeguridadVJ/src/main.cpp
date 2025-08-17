#include "CrytoGenerator.h"
#include "SensitiveInfoCypher.h"
#include "StarmiseCipher.h"

int
main() {

  SensitiveInfoCypher sensReader;
  std::string stringKey = "K0r0_7357_C14v3";
  std::string inputFile = "bin/CIFData.txt";

  if (!sensReader.LoadFile(inputFile)) {
    return 0;
  }
  std::cout << "Data loaded succesfully" << std::endl;

  // Starmise
  unsigned int seed = 357;
  sensReader.encodeByStarmise(inputFile, "bin/Starmise_encrypted.txt", stringKey, seed);
  sensReader.decodeByStarmise("bin/Starmise_encrypted.txt", "bin/Starmise_decoded.txt", stringKey, seed);

  return 0;
}
