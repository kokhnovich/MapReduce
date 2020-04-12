#include <bits/stdc++.h>

using namespace std;

int main() {
  map<string, int> m;
  std::string line;
  while (std::getline(cin, line)) {
    std::istringstream iss(line);
    string key;
    iss >> key;
    if (key.empty()) break;
    int cnt;
    iss >> cnt;
    ++m[key];
  }
  for (const auto&[key, value] : m) {
    cout << key << "\t" << value << "\n";
  }
  return 0;
}
