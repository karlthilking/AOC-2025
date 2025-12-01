#include <iostream>
#include <string> 
#include <fstream>

int main() {
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
    if (next_pos < 0) { next_pos = 100 + next_pos; }

    pos = next_pos;
    if (pos == 0) { ++zeros; }
    std::cout << "Current position: " << pos << "\n";
  }

  std::cout << "Password: " << zeros << "\n";
} 