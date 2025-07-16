# Criptoanalisis
This project is a c++ toolkit for encrypting and decrypting sensitive information using various classical and custom ciphers. The project is modular and includes support for:
- Caesar Cipher
- XOR Cipher (with brute-force & dictionary attacks)
- Binary Conversion Utilities
- DES Encryption (64-bit block cipher logic)
- Custom: Starmise Cipher (XOR + WFC-style permutation)

It has a custom encryption method called **Starmise Cipher**, combining a classic **XOR cipher** with a **Wave Function Collapse-inspired permutation**. It's integrated into a larger system capable of handling multiple encryption techniques (including DES, XOR, Caesar, etc.) on plaintext files.

---

## Features

- Encrypts/decrypts plain text files line-by-line
- Supports multi-line input and special characters
- Outputs encrypted text as hexadecimal (for safe storage)
- Implements brute-force, frequency and dictionary attacks (XOR, Caesar)
- Starmise Custom Cipher Abomination:
    - XOR-based encryption
    - Wave Function Collapse-like character permutation
    - Combined as a dual-layer cipher (XOR + permutation)
    - Handles multi-line documents
    - Hexadecimal output encoding for safe storage
    - Full encryption and decryption support

---

## How to use
1. Create a file .txt format with the sensitive information you want to encrypt.
2. Add your .txt file to the bin folder
3. Inside main.cpp, on line 10, replace the file name with the name of your own file.
4. Run program.
5. That's it! You will have your file encrypted by 6 different methods: Caesar, XOR, DES, Binary, Vignere and Starmise (custom).

## How Starmise Cipher Works

### 1. XOR Cipher

Each character of the input is XOR-ed with a repeating key.

### 2. Wave Function Collapse very, very, very simplificated shuffle

A seeded `std::shuffle` creates a consistent but non-reversible permutation unless the same seed is reused.

---

## Usage Instructions

### Prerequisites

- C++17 or higher
- Standard C++ STL libraries (fstream, vector, string, iostream, etc.)

### Example Code (main.cpp)

```cpp
SensitiveInfoCypher sic;
sic.encodeByStarmise("input.txt", "encrypted_output.txt", "key", 123);
sic.decodeByStarmise("encrypted_output.txt", "decrypted_output.txt", "key", 123);
```

- `input.txt`: Plaintext file with any content
- `encrypted_output.txt`: Hexadecimal encoded encrypted output
- `decrypted_output.txt`: Reconstructed plaintext
- `key`: A string key used for XOR
- `123`: A fixed seed for reproducible shuffle order

---

## Encryption Format

Each encrypted block is output as hexadecimal values

---

## Take in account

- The seed **must be the same** for both encryption and decryption.
- Shuffling is position-based; tampering with data will cause loss of decryption integrity.
- Currently designed for **entire document encryption**.
