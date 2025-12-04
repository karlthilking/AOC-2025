#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::vector<int>> adj = {
    {0,1},{1,0},{0,-1},{-1,0},{-1,-1},{-1,1},{1,-1},{1,1}
};

int part1(std::vector<std::vector<char>>& lines) {
  int rolls = 0;
  for (size_t i = 0; i < lines.size(); ++i) {
    for (size_t j = 0; j < lines[i].size(); ++j) {
      if (lines[i][j] == '.') continue;
      int adj_rolls = 0;
      for (const auto& pos: adj) {
        int r = pos[0] + i; int c = pos[1] + j;
        if (r < 0 || c < 0 || r >= lines.size() || c >= lines[i].size()) {
          continue;
        }
        if (lines[r][c] == '@') ++adj_rolls;
      }
      if (adj_rolls < 4) {
        ++rolls;
      }
    }
  }
  return rolls;
}

int part2(std::vector<std::vector<char>>& lines) {
  std::vector<std::vector<size_t>> remove;
  int rolls = 0;
  for (size_t i = 0; i < lines.size(); ++i) {
    for (size_t j = 0; j < lines[i].size(); ++j) {
      if (lines[i][j] == '.' || lines[i][j] == 'x') {
        continue;
      }
      int adj_rolls = 0;

      for (const auto& pos: adj) {
        int r = pos[0] + i; int c = pos[1] + j;
        if (r < 0 || c < 0 || r >= lines.size() || c >= lines[i].size()) {
          continue;
        }
        if (lines[r][c] == '@') ++adj_rolls;
      }
      if (adj_rolls < 4) {
        ++rolls;
        remove.push_back({i, j});
      }
    }
  }
  for (const auto& pos: remove) {
    lines[pos[0]][pos[1]] = 'x';
  }
  return rolls;
}

int main() {
  std::vector<std::vector<char>> lines;
  std::fstream input("data/day4input.txt");
  std::string s;

  while (std::getline(input, s)) {
    std::vector<char> line(s.length(), 0);
    for (size_t i = 0; i < s.length(); ++i) {
      line[i] = s[i];
    }
    lines.push_back(line);
  }

  std::cout << "Part 1: " << part1(lines) << "\n";

  int part2_total = 0;
  while (true) {
    int removed = part2(lines);
    if (removed == 0) break;
    else part2_total += removed;
  }
  std::cout << "Part 2: " << part2_total << "\n";
  return 0;
}
