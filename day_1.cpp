#include <iostream>
#include <string> 
#include <fstream>
#include <cstdlib>

void part1() {
  std::fstream input("input.txt");
  std::string s;
  int pos = 50;
  int zeros = 0;

  while (std::getline(input, s)) {
    int n = s.length();
    int degree;

    if (n == 2) {
      degree = s[1] - '0'; 
    }
    else {
      degree = (s[n - 2] - '0') * 10 + s[n - 1] - '0';
    } 

    int next_pos = (s[0] == 'R') ? pos + degree : pos - degree;

    if (next_pos > 99) { next_pos -= 100; }
    if (next_pos < 0) { next_pos += 100; }

    pos = next_pos;
    if (pos == 0) { ++zeros; }
    std::cout << "Current position: " << pos << "\n";
  }

  std::cout << "Password: " << zeros << "\n";
}

void part2() {
  std::fstream input("input.txt");
  std::string s;
  int pos = 50;
  int zeros = 0;

  while (std::getline(input, s)) {
    int n = s.length();
    int degree = 0;
    int mut = 1;

    for (int i = n - 1; i > 0; --i) {
      degree += (s[i] - '0') * mut;
      mut *= 10;
    }

    if (std::abs(degree) > 100) {
      int q = degree / 100;
      zeros += q;
      degree %= 100;
    }

    int next_pos = (s[0] == 'R') ? pos + degree : pos - degree;

    if (next_pos > 99) {
      next_pos -= 100;
      if (pos != 0 && next_pos != 0) ++zeros;
    }
    if (next_pos < 0) {
      next_pos += 100;
      if (pos != 0 && next_pos != 0) ++zeros;
    }
    if (next_pos == 0) ++zeros;

    pos = next_pos;
    std::cout << "Current pos: " << pos << "\n";
  }
  std::cout << "Password: " << zeros << "\n";
}

int main() {
  part1();
  part2();
} 