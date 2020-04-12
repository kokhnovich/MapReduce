#include <bits/stdc++.h>

using namespace std;

int main() {
  std::string line;
  while (std::getline(cin, line)) {
    std::istringstream iss(line);
    string Key;
    iss >> Key;
    do {
      string word;
      iss >> word;
      if (word.empty()) break;
      cout << word << "\t1\n";
    } while (iss);
  }
  return 0;
}
