#include "CrytoGenerator.h"
#include "SensitiveInfoCypher.h"
#include "StarmiseCipher.h"

int
main() {
  // 1. Instancia del cifrado personalizado
  StarmiseCypher starmise;

  // 2. Texto original
  std::string originalText = "Usuario:Koromaru | Clave:Persona3 | PIN:0420";
  std::string key = "Starmise";

  // 3. Cifrado
  std::string encrypted = starmise.encrypt(originalText, key, 10);
  std::cout << "Texto cifrado:\n" << encrypted << "\n";

  // 4. Descifrado (debe restaurar el original)
  std::string decrypted = starmise.decrypt(encrypted, key);
  std::cout << "Texto descifrado:\n" << decrypted << "\n";

  //SensitiveInfoCypher sensReader;
  //std::string stringKey = "K0r0_7357_C14v3";
  //std::string inputFile = "bin/SensInfo.txt";

  //if (!sensReader.LoadFile(inputFile)) {
  //  return 0;
  //}
  //std::cout << "Data loaded succesfully" << std::endl;
  //sensReader.printData();

  //// VIGENERE
  //Vignere vig(stringKey);
  //sensReader.encodeByVigenere(vig, "bin/vigenere_encrypted.txt");
  //sensReader.decodeByVigenere(vig, "bin/vigenere_encrypted.txt", "bin/vigenere_decoded.txt");

  //// DES
  //std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");
  //DES des(key);
  //sensReader.encodeByDES(des, "bin/des_encrypted.txt");
  //sensReader.decodeByDES(des, "bin/des_encrypted.txt", "bin/des_decoded.txt", key);

  //// XOR
  //sensReader.encodeByXOR(inputFile, "bin/xor_encrypted.txt", stringKey);
  //sensReader.decodeByXOR("bin/xor_encrypted.txt", "bin/xor_decoded.txt", stringKey);

  //// Ascii Binary
  //sensReader.encodeByBinary(inputFile, "bin/binary_encrypted.txt");
  //sensReader.decodeByBinary("bin/binary_encrypted.txt", "bin/binary_decoded.txt");

  //// Caesar
  //int shift = 4;
  //sensReader.encodeByCaesar(inputFile, "bin/Caesar_encrypted.txt", shift);
  //sensReader.decodeByCaesar("bin/Caesar_encrypted.txt", "bin/Caesar_decoded.txt", shift);

  return 0;
}
