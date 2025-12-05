#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

using ll = long long;

ll part1(std::vector<std::vector<ll>>& ranges, std::vector<ll>& ingredients) {
  ll num_spoiled = 0;

  for (const ll& ing: ingredients) {
    bool spoiled = true;
    for (const auto& range: ranges) {
      if (ing >= range[0] && ing <= range[1]) {
        spoiled = false;
        break;
      }
    }
    if (spoiled) num_spoiled++;
  }
  return ingredients.size() - num_spoiled;
}

ll part2(std::vector<std::vector<ll>>& ranges) {
  size_t n = ranges.size();
  std::vector<std::vector<ll>> merged_ranges;
  std::sort(ranges.begin(), ranges.end(), [&](std::vector<ll>& lhs, std::vector<ll>& rhs){
    return lhs[0] < rhs[0];
  });

  size_t i = 0; size_t j = 1;
  while (i < ranges.size() - 1) {
    std::vector<ll> temp(std::move(ranges[i]));
    if (temp[1] < ranges[j][0] - 1) {
      merged_ranges.push_back(std::move(temp));
      i++; j++; continue;
    }
    else {
      while (j < ranges.size() && temp[1] >= ranges[j][0] - 1) {
        temp[1] = std::max(temp[1], ranges[j][1]);
        j++;
      }
      i = j; j = i + 1;
      merged_ranges.push_back(std::move(temp));
    }
  }
  if (ranges[n - 1][1] > merged_ranges[merged_ranges.size() - 1][1]) {
    merged_ranges.push_back(std::move(ranges[n - 1]));
  }

  ll fresh_ingredients = 0;
  for (const auto& range: merged_ranges) {
    fresh_ingredients += (range[1] - range[0]) + 1;
  }
  return fresh_ingredients;
}

int main() {
  std::fstream input("data/day5input.txt");
  std::string s;
  std::vector<std::vector<ll>> ranges;
  std::vector<ll> ingredients;
  
  while (std::getline(input, s)) {
    if (s.empty()) {
      break;
    }
    else {
      ptrdiff_t lhs_start = 0; ptrdiff_t lhs_end = 0;
      ptrdiff_t rhs_start = 0; ptrdiff_t rhs_end = s.end() - s.begin();
      for (auto it = s.begin(); it != s.end(); ++it) {
        if (*it == '-') {
          lhs_end = std::distance(s.begin(), it);
          rhs_start = std::distance(s.begin(), it + 1);
          break;
        }
      }
      ll lhs = std::stoll(s.substr(lhs_start, lhs_end));
      ll rhs = std::stoll(s.substr(rhs_start, rhs_end));
      std::vector<ll> range{lhs, rhs};
      ranges.push_back(range);
    }
  }
  while (std::getline(input, s)) {
    if (s.empty()) continue;
    else {
      ingredients.push_back(std::stoll(s));
    }
  }
  std::cout << "Part 1: " << part1(ranges, ingredients) << "\n";
  std::cout << "Part 2: " << part2(ranges) << "\n"; 
}
