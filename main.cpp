#include "header.hpp"

const std::string path_to_towns("/home/dan_kokin/CLionProjects/countries/towns.txt");
const std::string path_to_counties("/home/dan_kokin/CLionProjects/countries/countries.txt");

std::vector<town_info> extract_towns(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    return std::vector<town_info>{};
  }
  std::vector<town_info> res;
  town_info tmp;
  while (getline(file, tmp.town)) {
    getline(file, tmp.country);
    std::string str;
    getline(file, str);
    tmp.amount = stoi(str);
    res.push_back(tmp);
    getline(file, str);
  }
  file.close();
  return res;
}

std::vector<country_info> extract_countries(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    return std::vector<country_info>{};
  }
  std::vector<country_info> res;
  country_info tmp;

  while (getline(file, tmp.country)) {
    getline(file, tmp.capital);
    getline(file, tmp.continent);
    res.push_back(tmp);
    std::string skip;
    getline(file, skip);
  }
  file.close();
  return res;
}

template <class T, class Compare = std::less<>>
void Sort(std::vector<T>& info, Compare cmp=Compare{}) {
  if (info.size() > 1) {
    for (size_t i = 0; i < info.size() - 1; ++i) {
      size_t index = i;
      for (size_t j = i + 1; j < info.size(); ++j) {
        if (cmp(info[j], info[i])) {
          index = j;
        }
      }

      if (index != i) {
        std::swap(info[i], info[index]);
      }
    }
  }
}

std::string GetCountryInfo(const std::vector<country_info>& countries,
    const std::string& countryName) {
  std::string answer("Информация о стране, в которой находится город:\n");

  for (const auto& it : countries) {
    if (it.country == countryName) {
      return answer += "Название страны:    " + it.country +
                       "\nНазвание столицы: " + it.capital +
                       "\nКонтинент:        " + it.continent + "\n";

    }
  }
  return answer += "Нет информации\n";
}

std::string GetTownsInfoFromCountry(const std::vector<town_info>& towns,
    const std::string& countryName) {
  std::string answer("Информация о городах, находящихся в стране:");
  bool isHaveInfo = false;

  for (const auto& town : towns) {
    if (town.country == countryName) {
      isHaveInfo = true;
      answer += "\nНазвание:           " + town.town +
                "\nКоличество жителей: " + std::to_string(town.amount) + "\n";
    }
  }
  if (!isHaveInfo) {
    answer += "\nНет информации\n";
  }
  return answer;
}

void Menu() {
  auto towns = extract_towns(path_to_towns);
  auto countries = extract_countries(path_to_counties);

  size_t townNameCounter = 0, townCountryCounter = 0, townAmountCounter = 0,
  countryNameCounter = 0, countryCapitalCounter = 0, countryContinentCounter = 0;
  std::cout << "Добро пожаловать в программу сортировки информации!" << std::endl;
  while (true) {
    std::cout << "По какому полю хотите сортировать?" << std::endl;

    std::cout << "Для сортировки городов по их названию нажмите 1" << std::endl;
    std::cout << "Для сортировки городов по названию их стран нажмите 2" << std::endl;
    std::cout << "Для сортировки городов по численности их населения нажмите 3" << std::endl;

    std::cout << "Для сортировки стран по их названию нажмите 4" << std::endl;
    std::cout << "Для сортировки стран по названиям столиц нажмите 5" << std::endl;
    std::cout << "Для сортировки стран по названию их континента нажмите 6" << std::endl;

    std::cout << "Для выхода из программы нажмите <esc>" << std::endl;

    char field;
    std::cin >> field;
    if (field == 27) {
      break;
    }

    if (field < '1' || field > '6') {
      std::cout << "Неправильно введены данные!" << std::endl;
      continue;
    }

    std::cout << "Для сортировки по убыванию нажмите 1" << std::endl;
    std::cout << "Для сортировки по возрастанию нажмите 2" << std::endl;
    std::cout << "Для возврата назад, нажмите <esc>" << std::endl;

    char lambda;
    std::cin >> lambda;
    if (lambda == 27) {
      continue;
    }

    if (lambda != '1' && lambda != '2') {
      std::cout << "Неправильно введены данные!" << std::endl;
      continue;
    }


    if (field == '1') {
      ++townNameCounter;
      std::ofstream out ("SortByTownName" + std::to_string(countryNameCounter) + ".txt");
      out << "Сортировка по названию города" << std::endl;
      // Сортировка по названию
      if (lambda == '1') {
        Sort(towns, [](const town_info& t1, const town_info& t2) {
          return t1.town < t2.town;
        });
      } else {
        Sort(towns, [](const town_info& t1, const town_info& t2) {
          return t1.town > t2.town;
        });
      }
      for (const auto& it : towns) {
        std::cout << it.town << " ";
      }
      std::for_each(towns.begin(), towns.end(), [&](const town_info& info) {
        out << "Название города: " << info.town << std::endl;
        out << "Страна:          " << info.country << std::endl;
        out << "Население:       " << info.amount << std::endl;
        out << GetCountryInfo(countries, info.country);
        out << std::endl;
      });

      out.close();

    } else if (field == '2') {
      ++townCountryCounter;
      std::ofstream out ("SortByTownCountry" + std::to_string(countryNameCounter) + ".txt" + std::to_string(townCountryCounter));
      out << "Сортировка по названию страны" << std::endl;
      // Сортировка по стране
      if (lambda == '1') {
        Sort(towns, [](const town_info& t1, const town_info& t2) {
          return t1.country < t2.country;
        });
      } else {
        Sort(towns, [](const town_info& t1, const town_info& t2) {
          return t1.country > t2.country;
        });
      }

      std::for_each(towns.begin(), towns.end(), [&](const town_info& info) {
        out << "Страна:          " << info.country << std::endl;
        out << "Название города: " << info.town << std::endl;
        out << "Население:       " << info.amount << std::endl;
        out << GetCountryInfo(countries, info.country);
        out << std::endl;
      });

      out.close();

    } else if (field == '3') {
      ++townAmountCounter;
      std::ofstream out ("SortByTownAmount" + std::to_string(countryNameCounter) + ".txt" + std::to_string(townAmountCounter));
      out << "Сортировка по численности населения города" << std::endl;
      // Сортировка по численности
      if (lambda == '1') {
        Sort(towns, [](const town_info& t1, const town_info& t2) {
          return t1.amount < t2.amount;
        });
      } else {
        Sort(towns, [](const town_info& t1, const town_info& t2) {
          return t1.amount > t2.amount;
        });
      }
      std::for_each(towns.begin(), towns.end(), [&](const town_info& info) {
        out << "Население        " << info.amount << std::endl;
        out << "Название города: " << info.town << std::endl;
        out << "Страна:          " << info.country << std::endl;
        out << GetCountryInfo(countries, info.country);
        out << std::endl;
      });

      out.close();

    } else if (field == '4') {
      ++countryNameCounter;
      std::ofstream out ("SortByCountryName" + std::to_string(countryNameCounter) + ".txt" + std::to_string(countryNameCounter));
      // Сортировка по названию
      if (lambda == '1') {
        Sort(countries, [](const country_info& t1, const country_info& t2) {
          return t1.country < t2.country;
        });
      } else {
        Sort(countries, [](country_info& t1, country_info& t2) {
          return t1.country > t2.country;
        });
      }
      std::for_each(countries.begin(), countries.end(), [&](const country_info& info) {
        std::cout << info.country << " ";
        out << "Страна:    " << info.country << std::endl;
        out << "Континент: " << info.continent << std::endl;
        out << "Столица    " << info.capital << std::endl;
        out << GetTownsInfoFromCountry(towns, info.country);
        out << std::endl;
      });

      out.close();

    } else if (field == '5') {
      ++countryCapitalCounter;
      std::ofstream out ("SortByCountryCapital" + std::to_string(countryNameCounter) + ".txt" + std::to_string(countryCapitalCounter));
      // Сортировка по названию столицы
      if (lambda == '1') {
        Sort(countries, [](const country_info& t1, const country_info& t2) {
          return t1.capital < t2.capital;
        });
      } else {
        Sort(countries, [](country_info& t1, country_info& t2) {
          return t1.capital > t2.capital;
        });
      }

      std::for_each(countries.begin(), countries.end(), [&](const country_info& info) {
        out << "Столица:   " << info.capital << std::endl;
        out << "Страна:    " << info.country << std::endl;
        out << "Континент: " << info.continent << std::endl;
        out << GetTownsInfoFromCountry(towns, info.country);
        out << std::endl;
      });

      out.close();

    } else if (field == '6') {
      ++countryContinentCounter;
      std::ofstream out ("SortByCountryContinent" + std::to_string(countryNameCounter) + ".txt" + std::to_string(countryContinentCounter));
      // Сортировка по названию континента
      if (lambda == '1') {
        Sort(countries, [](const country_info& t1, const country_info& t2) {
          return t1.continent < t2.continent;
        });
      } else {
        Sort(countries, [](country_info& t1, country_info& t2) {
          return t1.continent > t2.continent;
        });
      }
      std::for_each(countries.begin(), countries.end(), [&](const country_info& info) {
        out << "Континент: " << info.continent << std::endl;
        out << "Страна:    " << info.country << std::endl;
        out << "Столица:   " << info.capital << std::endl;
        out << GetTownsInfoFromCountry(towns, info.country);
        out << std::endl;
      });

      out.close();
    }
  }
}

int main() {
  Menu();
}