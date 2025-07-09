#pragma once
#include "Prerequisites.h"

class
  SensitiveInfoCypher {
public:
  /*
  * @brief Default constructor and destructor.
  */
  SensitiveInfoCypher() = default;
  ~SensitiveInfoCypher() = default;

  /*
  * @brief
  * @param
  * @param
  */
  bool
    LoadFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
      std::cerr << "No se pudo abrir el archivo: " << filePath << "\n";
      return false;
    }

    data.clear();

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty()) {
        continue; // Se salta si la línea está vacía a la siguiente
      }

      std::istringstream iss(line);
      std::string user;
      std::string pass;
      std::string other;
      if (std::getline(iss, user, ':') &&
          std::getline(iss, pass, ':') &&
          std::getline(iss, other)) {
        data.push_back({ user, pass, other });
      }
      else {
        std::cerr << "Not readable line: " << line << std::endl;
      }
    }
    file.close();
    return true;
  }

  const std::vector<SensitiveData>& getData() const {
    return data;
  }

  void 
    printData(const std::vector<SensitiveData>& data) {
    for (size_t i = 0; i < data.size(); i++) {
      std::cout << "Register" << i + 1 << ":\n";
      std::cout << "User" << data[i].user << ":\n";
      std::cout << "Pass" << data[i].password << ":\n";
      std::cout << "Other Data:" << data[i].others << ":\n";
    }
  }

private:
  std::vector<SensitiveData> data;
};