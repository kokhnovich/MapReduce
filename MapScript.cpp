#include <iostream>
#include <sstream>

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string Key;
    iss >> Key;
    do {
      std::string word;
      iss >> word;
      if (word.empty()) break;
      std::cout << word << "\t1\n";
    } while (iss);
  }
  return 0;
}
