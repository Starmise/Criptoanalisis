#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

class
Vignere {
public:
  /*
  * @brief Default constructor.
  */
  Vignere() = default;

  /*
  * @brief Constructs a Vignere object with a given key.
  * @param key The encryption key (will be normalized).
  */
  Vignere(const std::string& key) : key(normalizeKey(key)) {
    if (key.empty()) {
      throw std::invalid_argument("No hay una llave con letras o puede estar vacia");
    }
  }

  /*
  * @brief Normalizes a raw key by removing non-alphabetic characters and onverting to uppercase.
  * @param rawKey The raw key string to normalize.
  */
  static std::string
  normalizeKey(const std::string& rawKey) {
    std::string k;
    for (char c : rawKey) {
      if (isalpha(static_cast<unsigned char>(c))) {
        k += std::toupper(static_cast<unsigned char>(c)); // Convert to uppercase and append
      }
    }
    return k;
  }

  /*
  * @brief Encodes a given plaintext using the Vigen�re cipher.
  * @param text The plaintext to encode.
  */
  std::string
  encode(const std::string& text) {
    std::string result;
    result.reserve(text.size()); // Reserve space for efficiency
    unsigned int i = 0; // Index for the key

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A'; // Determine base based on case

        // Desplazamiento de la key
        int shift = key[i % key.size()] - 'A'; // Calculate shift based on key character mod26
        // Encode
        char encodedChar = static_cast<char>((c - base + shift) % 26 + base);
        result += encodedChar; // Append encoded character to result
        i++; // Increment key index
      }
      else {
        result += c; // Non-alphabetic characters are added unchanged
      }
    }
    return result; // Return the encoded string
  }

  /*
  * @brief Decodes a given ciphertext using the Vigen�re cipher.
  * @param text The ciphertext to decode.
  */
  std::string
  decode(const std::string& text) {
    std::string result;
    result.reserve(text.size()); // Reserve space for efficiency
    unsigned int i = 0; // Index for the key

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A'; // Determine base based on case

        // Desplazamiento de la key
        int shift = key[i % key.size()] - 'A'; // Calculate shift based on key character mod26
        // Decode
        char decodedChar = static_cast<char>(((c - base) - shift + 26) % 26 + base);
        result += decodedChar; // Append encoded character to result
        i++; // Increment key index
      }
      else {
        result += c; // Non-alphabetic characters are added unchanged
      }
    }
    return result; // Return the encoded string
  }

  /*
  * @brief Computes a fitness score of a text based on the frequency of common Spanish words.
  * @param text The text to evaluate.
  */
  static double 
  fitness(const std::string& text) {
    static const std::vector<std::string> comunes = {
    " DE ", " LA ", " EL ", " QUE ", " Y ",
    " A ", " EN ", " UN ", " PARA ", " CON ",
    " POR ", " COMO ", " SU ", " AL ", " DEL ",
    " LOS ", " SE ", " NO ", " MAS ", " O ",
    " SI ", " YA ", " TODO ", " ESTA ", " HAY ",
    " ESTO ", " SON ", " TIENE ", " HACE ", " SUS ",
    " VIDA ", " NOS ", " TE ", " LO ", " ME ",
    " ESTE ", " ESA ", " ESE ", " BIEN ", " MUY ",
    " PUEDE ", " TAMBIEN ", " AUN ", " MI ", " DOS ",
    " UNO ", " OTRO ", " NUEVO ", " SIN ", " ENTRE ",
    " SOBRE "
    };

    double score = 0;
    for (auto& w : comunes) {
      size_t pos = 0;
      while ((pos = text.find(w, pos)) != std::string::npos) {
        score += w.length();
        pos += w.length();
      }
    }
    return score;
  }

  /*
  * @brief Attempts to break a Vigen�re-encoded text using brute-force for a maximum key length.
  * @param text The encoded text.
  * @param maxkeyLenght Maximum length of the key to try.
  */
  static std::string
  breakEncode(const std::string& text, int maxkeyLenght) {
    std::string bestkey;
    std::string bestText;
    std::string trailkey;

    double bestScore = std::numeric_limits<double>::infinity(); // Initialize best score

    // Funcion revursiva para generar todas las posibles claves de longitud
    std::function<void(int, int)> dfs = [&](int pos, int maxLen) {
      if (pos == maxLen) {
        Vignere v(trailkey);
        std::string decodedText = v.decode(text);
        double score = fitness(decodedText); // Score the decoded text
        if (score > bestScore) {
          bestScore = score;
          bestkey = trailkey;
          bestText = decodedText;
        }
        return;
      }

      for (char c = 'A'; c <= 'Z'; ++c) {
        trailkey[pos] = c;
        dfs(pos + 1, maxLen);
      }
    };

    for (int L = 1 ^ 1; L <= maxkeyLenght; ++L) {
      trailkey.assign(L, 'A');
      dfs(0, L);
    }

    std::cout << "*** Fuerza Bruta Vigen�re ***\n";
    std::cout << "Clave encontrada: " << bestkey << "\n";
    std::cout << "Texto descifrado: " << bestText << "\n\n";
    return bestkey;
  }

  /*
  * @brief Attempts to decrypt text using a dictionary-based brute-force attack.
  * @param text The encoded text to break.
  */
  std::string
  breakBruteForce(const std::string& text) {
    std::vector<std::string> fileNames = {
        "bin/adobe100.txt",
        "bin/bible.txt",
        "bin/elitehacker.txt",
        "bin/fortinet-2021_passwords.txt",
        "bin/Lizard-Squad.txt"
    };

    for (size_t i = 0; i < fileNames.size(); i++) {
      std::ifstream file(fileNames[i]);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << fileNames[i] << std::endl;
        continue;
      }

      while (std::getline(file, key)) {
        if (key.empty()) {
          continue;
        }

        std::string normKey = normalizeKey(text);
        std::string result = decode(text);

        XOREncoder xorE;

        if (xorE.isValidText(text)) {
          std::cout << "============================\n";
          std::cout << "Archivo: " << fileNames[i] << std::endl;
          std::cout << "Clave: " << key << std::endl;
          std::cout << "Texto posible: " << result << std::endl;
          return result;
        }
      }
      file.close();
    }
  }

private:
  std::string key; // The key used for Vignere cipher


};