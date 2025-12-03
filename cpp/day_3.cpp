#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using ll = long long;

ll part1(std::vector<std::vector<int>>& lines) {
  ll voltage = 0;
  for (const auto& line: lines) {
    auto lhs = std::max_element(line.begin(), line.end() - 1);
    auto rhs = std::max_element(lhs + 1, line.end());
    voltage += *lhs * 10 + *rhs;
  }
  return voltage;
}

ll part2(std::vector<std::vector<int>>& lines) {
  std::vector<ll> powers;
  for (int i = 0; i <= 11; ++i) {
    powers.push_back(std::pow(10, i));
  }

  ll voltage = 0;
  for (const auto& line: lines) {
    auto left = line.begin(); auto right = line.end() - 11;
    for (int digit = 11; digit >= 0; --digit) {
      auto current = std::max_element(left, right);
      voltage += *current * powers[digit];
      left = current + 1; right += 1;
    }
  }
  return voltage;
}

int main() {
  std::fstream input("../data/input3.txt");
  std::string s;
  std::vector<std::vector<int>> lines;
  
  while (std::getline(input, s)) {
    std::vector<int> line(s.length(), 0);
    for (size_t i = 0; i < s.length(); ++i) {
      line[i] = s[i] - '0';
    }
    lines.push_back(line);
  }

  std::cout << "Part 1: " << part1(lines) << "\n";
  std::cout << "Part 2: " << part2(lines) << "\n";

  return 0;
}
