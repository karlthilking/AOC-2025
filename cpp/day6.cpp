#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <utility>

using ll = long long;

ll part1(std::vector<std::string>& lines, std::vector<char>& ops) {
  std::vector<std::vector<ll>> nums;

  for (const auto& line: lines) {
    std::vector<ll> temp;

    auto l = line.begin(); auto r = line.begin();
    while (*r == ' ') ++r;
    l = r; r = std::next(l);

    while (l < line.end() && r < line.end()) {
      while (*r != ' ') ++r;
      auto start = std::distance(line.begin(), l);
      auto count = std::distance(l, r);
      temp.push_back(std::stoll(line.substr(start, count)));
      while (*r == ' ') ++r;
      l = r; r = std::next(l);
    }
    nums.push_back(std::move(temp));
  }

  ll total = 0; 
  for (size_t c = 0; c < nums[0].size(); ++c) {
    ll x; std::function<ll(ll, ll)> op;
    if (ops[c] == '+') { x = 0; op = std::plus<>(); }
    else { x = 1; op = std::multiplies<>(); }

    for (size_t r = 0; r < nums.size(); ++r) {
      x = op(x, nums[r][c]);
    }
    total += x;
  }

  return total;

}

int main() {
  std::fstream input("data/day6.txt");
  std::vector<std::string> lines;
  std::vector<char> ops;
  std::string s;

  while (std::getline(input, s)) {
    if (s[0] == '+' || s[0] == '*') {
      for (char c: s) {
        if (c == ' ') continue;
        ops.push_back(c);
      }
    }
    else {
      lines.push_back(s);
    }
  }
  
  std::cout << "Part 1: " << part1(lines, ops);
  return 0;
}
