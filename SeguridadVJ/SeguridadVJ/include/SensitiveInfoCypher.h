#pragma once
#include "Prerequisites.h"
#include "Vignere.h"
#include "Des.h"
#include "XorEncoder.h"
#include "AsciiBinary.h"
#include "CaesarEncryption.h"
#include "StarmiseCipher.h"

class
SensitiveInfoCypher {
public:
  /*
  * @brief Default constructor and destructor.
  */
  SensitiveInfoCypher() = default;
  ~SensitiveInfoCypher() = default;

  /*
  * @brief Loads the contents of a file line by line.
  * @param filePath Path of the input file.
  * @return true on success, false on error.
  */
  bool
  LoadFile(const std::string& filePath);

  /*
  * @brief Returns the stored data.
  */
  const 
  std::vector<SensitiveData>& getData() const {
    return data;
  }

  /*
  * @brief Shows the stored data (For debugging only).
  */
  void
  printData() const;

  /*
  * @brief Encrypts data using the Vigenere method.
  * @param vige Vigenere's configured object.
  * @param outputFile Path of the encrypted file.
  */
  void
  encodeByVigenere(Vignere& vige, const std::string& outputFile);

  /*
  * @brief Decodes the data using the Vigenère method.
  * @param vige Vigenere configured object.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the decoded file.
  */
  void
  decodeByVigenere(Vignere& vige, 
                  const std::string& inputFile, 
                  const std::string& outputFile);

  /*
  * @brief Encrypts the data using the DES method.
  * @param des DES configured object.
  * @param outputFile Path of the encrypted file.
  */
  void
  encodeByDES(DES& des, const std::string& outputFile);

  /*
  * @brief Decodes the data using the DES method.
  * @param des DES configured object.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the decoded file.
  * @param key bitset64 key used to decode the file.
  */
  void
  decodeByDES(DES& des,
              const std::string& inputFile,
              const std::string& outputFile,
              const std::bitset<64>& key);


  /*
  * @brief Encrypts the data using the XOR method.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the encrypted file.
  * @param key string key used to encode the file.
  */
  void
  encodeByXOR(const std::string& inputFile, 
              const std::string& outputFile, 
              const std::string& key);


  /*
  * @brief Decodes the data using the XOR method.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the decoded file.
  * @param key string key used to decode the file.
  */
  void
  decodeByXOR(const std::string& inputFile, 
              const std::string& outputFile, 
              const std::string& key);

  /*
 * @brief Encrypts the data using the Ascii Binary method.
 * @param inputFile Path of the encrypted file.
 * @param outputFile Path of the encrypted file.
 */
  void
  encodeByBinary(const std::string& inputFile, const std::string& outputFile);

  /*
  * @brief Decodes the data using the Ascii Binary method.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the decoded file.
  */
  void
  decodeByBinary(const std::string& inputFile, const std::string& outputFile);

  /*
  * @brief Encrypts the data using the Caesar method.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the decoded file.
  * @param shift Displacement value.
  */
  void
  encodeByCaesar(const std::string& inputFile, const std::string& outputFile, int shift);

  /*
  * @brief Decodes the data using the Caesar method.
  * @param inputFile Path of the encrypted file.
  * @param outputFile Path of the decoded file.
  * @param shift Displacement value
  */
  void
  decodeByCaesar(const std::string& inputFile, const std::string& outputFile, int shift);

  void
  encodeByStarmise(const std::string& inputfile, 
                  const std::string& outputfile,
                  const std::string& key, 
                  unsigned int seed);

  void
  decodeByStarmise(const std::string& inputfile, 
                  const std::string& outputfile, 
                  const std::string& key, 
                  int seed);

private:
  std::vector<SensitiveData> data;
};