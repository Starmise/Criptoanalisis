#include "CrytoGenerator.h"
#include "SensitiveInfoCypher.h"
#include "StarmiseCipher.h"

int
main() {

  SensitiveInfoCypher sensReader;
  std::string stringKey = "K0r0_7357_C14v3";
  std::string inputFile = "bin/SensInfo.txt";

  if (!sensReader.LoadFile(inputFile)) {
    return 0;
  }
  std::cout << "Data loaded succesfully" << std::endl;

  // VIGENERE
  Vignere vig(stringKey);
  sensReader.encodeByVigenere(vig, "bin/vigenere_encrypted.txt");
  sensReader.decodeByVigenere(vig, "bin/vigenere_encrypted.txt", "bin/vigenere_decoded.txt");

  // DES
  std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");
  DES des(key);
  sensReader.encodeByDES(des, "bin/des_encrypted.txt");
  sensReader.decodeByDES(des, "bin/des_encrypted.txt", "bin/des_decoded.txt", key);

  // XOR
  sensReader.encodeByXOR(inputFile, "bin/xor_encrypted.txt", stringKey);
  sensReader.decodeByXOR("bin/xor_encrypted.txt", "bin/xor_decoded.txt", stringKey);

  // Ascii Binary
  sensReader.encodeByBinary(inputFile, "bin/binary_encrypted.txt");
  sensReader.decodeByBinary("bin/binary_encrypted.txt", "bin/binary_decoded.txt");

  // Caesar
  int shift = 4;
  sensReader.encodeByCaesar(inputFile, "bin/Caesar_encrypted.txt", shift);
  sensReader.decodeByCaesar("bin/Caesar_encrypted.txt", "bin/Caesar_decoded.txt", shift);

  // Starmise
  unsigned int seed = 357;
  sensReader.encodeByStarmise(inputFile, "bin/Starmise_encrypted.txt", stringKey, seed);
  sensReader.decodeByStarmise("bin/Starmise_encrypted.txt", "bin/Starmise_decoded.txt", stringKey, seed);

  return 0;
}
