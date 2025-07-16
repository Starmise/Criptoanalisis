#include "SensitiveInfoCypher.h"

bool
SensitiveInfoCypher::LoadFile(const std::string& filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "No se pudo abrir el archivo: " << filePath << "\n";
    return false;
  }

  data.clear();
  SensitiveData entry;
  std::string line;

  while (std::getline(file, line)) {
    if (!line.empty()) {
      entry.lines.push_back(line);
    }
  }

  if (!entry.lines.empty()) {
    data.push_back(entry);
  }

  file.close();
  return true;
}

void
SensitiveInfoCypher::printData() const {
  for (size_t i = 0; i < data.size(); i++) {
    std::cout << "Register" << i + 1 << ":\n";
    for (const auto& line : data[i].lines) {
      std::cout << "-" << line << "\n";
    }
  }
}

void
SensitiveInfoCypher::encodeByVigenere(Vignere& vige, const std::string& outputFile) {
  std::ofstream out(outputFile);
  if (!out.is_open()) {
    std::cerr << "Cannot Open file for encoding _Vig_" << outputFile << "\n";
    return;
  }

  for (const auto& record : data) {
    for (const auto& line : record.lines) {
      out << vige.encode(line) << std::endl;
    }
  }

  out.close();
}

void
SensitiveInfoCypher::decodeByVigenere(Vignere& vige,
                                      const std::string& inputFile,
                                      const std::string& outputFile) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!out.is_open() || !in.is_open()) {
    std::cerr << "Cannot Open file for decoding 'Vig'" << "\n";
    return;
  }

  std::string line;
  while (std::getline(in, line)) {
    out << vige.decode(line) << "\n";
  }

  in.close();
  out.close();
}

void
SensitiveInfoCypher::encodeByDES(DES& des, const std::string& outputFile) {
  std::ofstream out(outputFile);
  if (!out.is_open()) {
    std::cerr << "Cannot Open file for encoding 'DES'" << outputFile << "\n";
    return;
  }

  for (const auto& record : data) {
    for (const auto& line : record.lines) {
      std::string planeLine = line;

      while (planeLine.size() % 8 != 0) {
        planeLine += '\0';
      }

      for (size_t i = 0; i < planeLine.size(); i += 8) {
        std::string block = planeLine.substr(i, 8);
        auto bits = des.stringToBitset64(block);
        auto encrypted = des.encode(bits);
        out << encrypted.to_ullong() << "\n";
      }

      out << "-----------------" << "\n";
    }
  }
  out.close();
}

void
SensitiveInfoCypher::decodeByDES(DES& des,
                                const std::string& inputFile,
                                const std::string& outputFile,
                                const std::bitset<64>& key) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!out.is_open() || !in.is_open()) {
    std::cerr << "Cannot Open file for decoding 'DES'" << "\n";
    return;
  }

  DES des_dec(key);
  std::string line;
  std::string decodedLine;

  while (std::getline(in, line)) {
    if (line == "-----------------") {
      out << decodedLine << "\n";
      decodedLine.clear();
    }
    else {
      try {
        uint64_t encryptedBlock = std::stoull(line);
        std::bitset<64> bits(encryptedBlock);
        std::bitset<64> decodedBits = des.decode(bits);
        std::string block = des.bitset64ToString(decodedBits);

        for (char c : block) {
          if (c != '\0' && std::isprint(static_cast<unsigned char>(c))) {
            decodedLine += c;
          }
        }
      }
      catch (...) {
        std::cerr << "Error in line: " << line << "\n";
      }
    }
  }

  in.close();
  out.close();
}

void SensitiveInfoCypher::encodeByXOR(const std::string& inputFile,
                                      const std::string& outputFile,
                                      const std::string& key) {
                                      std::ifstream in(inputFile);
                                      std::ofstream out(outputFile);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot Open file for encoding 'XOR'" << "\n";
    return;
  }

  XOREncoder xorEncoder;
  std::string line;
  while (std::getline(in, line)) {
    std::string encrypted = xorEncoder.encode(line, key);

    // Escribimos en hexadecimal para que sea legible
    for (unsigned char c : encrypted) {
      out << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    }

    out << "\n-----------------\n";
  }

  in.close();
  out.close();
}

void
SensitiveInfoCypher::decodeByXOR(const std::string& inputFile,
                                const std::string& outputFile,
                                const std::string& key) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot Open file for decoding 'XOR'" << "\n";
    return;
  }

  XOREncoder xorEncoder;
  std::string line;
  std::string hexContent;

  while (std::getline(in, line)) {
    if (line == "-----------------") {
      std::vector<unsigned char> bytes = xorEncoder.HexToBytes(hexContent);
      std::string encryptedStr(bytes.begin(), bytes.end());
      std::string decrypted = xorEncoder.encode(encryptedStr, key);

      out << decrypted << "\n";
      hexContent.clear();
    }
    else {
      hexContent += line + " ";
    }
  }

  in.close();
  out.close();
}

void
SensitiveInfoCypher::encodeByBinary(const std::string& inputFile,
                                    const std::string& outputFile) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot Open file for encoding 'Bin'" << "\n";
    return;
  }

  AsciiBinary binEncoder;
  std::string line;
  while (std::getline(in, line)) {
    std::string encoded = binEncoder.stringToBinary(line);
    out << encoded << "\n";
    out << "-----------------\n";
  }

  in.close();
  out.close();
}

void
SensitiveInfoCypher::decodeByBinary(const std::string& inputFile,
                                    const std::string& outputFile) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot Open file for decoding 'Bin'" << "\n";
    return;
  }

  AsciiBinary binEncoder;
  std::string line;
  std::string binaryBlock;

  while (std::getline(in, line)) {
    if (line == "-----------------") {
      std::string decoded = binEncoder.binaryToString(binaryBlock);
      out << decoded << "\n";
      binaryBlock.clear();
    }
    else {
      binaryBlock += line + " ";
    }
  }

  in.close();
  out.close();
}

void
SensitiveInfoCypher::encodeByCaesar(const std::string& inputFile,
                                    const std::string& outputFile,
                                    int shift) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot Open file for encoding 'Ces'" << "\n";
    return;
  }

  CaesarEncryption caesar;
  std::string line;
  while (std::getline(in, line)) {
    std::string encrypted = caesar.EncryptionCaesar(line, shift);
    out << encrypted << "\n";
    out << "-----------------\n";
  }

  in.close();
  out.close();
}

void
SensitiveInfoCypher::decodeByCaesar(const std::string& inputFile,
                                    const std::string& outputFile,
                                    int shift) {
  std::ifstream in(inputFile);
  std::ofstream out(outputFile);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot Open file for decoding 'Ces'" << "\n";
    return;
  }

  CaesarEncryption caesar;
  std::string line;
  std::string decodedBlock;

  while (std::getline(in, line)) {
    if (line == "-----------------") {
      std::string decrypted = caesar.DecodeCaesar(decodedBlock, shift);
      out << decrypted << "\n";
      decodedBlock.clear();
    }
    else {
      decodedBlock += line;
    }
  }

  in.close();
  out.close();
}

void 
SensitiveInfoCypher::encodeByStarmise(const std::string& inputfile, 
                                      const std::string& outputfile, 
                                      const std::string& key, 
                                      unsigned int seed) {
  std::ifstream in(inputfile);
  std::ofstream out(outputfile);

  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot open file for encoding 'Starmise'\n";
    return;
  }

  std::ostringstream oss;
  std::string line;
  while (std::getline(in, line)) {
    oss << line << '\n';
  }

  StarmiseCypher starmise;
  std::string fullText = oss.str();
  std::string encrypted = starmise.encrypt(fullText, key, seed);

  // Hexadecimal
  for (unsigned char c : encrypted) {
    out << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
  }
  out << "\n-----------------\n";

  in.close();
  out.close();
}

void 
SensitiveInfoCypher::decodeByStarmise(const std::string& inputfile, 
                                      const std::string& outputfile, 
                                      const std::string& key, 
                                      int seed) {
  std::ifstream in(inputfile);
  std::ofstream out(outputfile);

  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Cannot open file for decoding 'Starmise'\n";
    return;
  }

  StarmiseCypher starmise;
  starmise.encrypt("koro", key, seed); // Wave Function

  std::string line;
  std::string block;

  std::vector<unsigned char> buffer;
  std::string hex;
  while (in >> hex) {
    if (hex == "-----------------") {
      // Decodificamos el bloque acumulado
      std::string encrypted(buffer.begin(), buffer.end());
      StarmiseCypher starmise;
      std::string decrypted = starmise.decrypt(encrypted, key, seed);
      out << decrypted;
      buffer.clear();
    }
    else {
      unsigned int byte;
      std::stringstream ss;
      ss << std::hex << hex;
      ss >> byte;
      buffer.push_back(static_cast<unsigned char>(byte));
    }
  }

  in.close();
  out.close();
}