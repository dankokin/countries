#ifndef COUNTRIES_HEADER_HPP
#define COUNTRIES_HEADER_HPP
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <dirent.h>
#include <iostream>
// обьявление внешней структуры с членами
struct town_info {
  std::string town, country;
  size_t amount;
};

// обьявление внешней структуры с членами
struct country_info {
  std::string country, capital, continent;
};

#endif //COUNTRIES_HEADER_HPP
