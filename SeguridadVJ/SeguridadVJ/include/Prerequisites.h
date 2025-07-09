#pragma once

#include <iostream> 
#include <string> 
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <functional>
#include <random>
#include <mutex>
#include <array>

#include <fstream> //Para leer los txt
#include <sstream> //Para leer los txt

/*
* @brief Struct to store one line of sensitive data.
*/
struct
SensitiveData {
  std::string user;
  std::string password;
  std::string others;
};