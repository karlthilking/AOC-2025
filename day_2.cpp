#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>

using ll = long long;

int count_digits(ll x) {
  int digits = 0;
  while (x > 0) {
    x /= 10;
    ++digits;
  }
  return digits;
}

ll get_next(ll x, int num_digits) {
  if (num_digits % 2) {
    ll res = std::pow(10, num_digits);
    res += std::pow(10, num_digits / 2);
    return res;
  }
  else {
    ll lhs = x / std::pow(10, num_digits / 2);
    ll res = (lhs * std::pow(10, num_digits / 2)) + lhs;
    
    if (res > x) {
      return res;
    }
    else {
      ll temp = lhs;
      while (temp > 0) {
        if (temp % 10 < 9) {
          break;
        }
        else {
          temp /= 10;
        }
      }
      temp += 1;
      while (temp < lhs) {
        temp *= 10;
      }
      if (count_digits(temp) > num_digits / 2) {
        num_digits += 2;
      }
      res = (temp * std::pow(10, num_digits / 2)) + temp;
      return res;
    }
  }
}

bool compare(ll x, int num_digits) {
  ll lhs = x / std::pow(10, num_digits / 2);
  ll denom = lhs * std::pow(10, num_digits / 2);
  ll rhs = x % denom;
  return lhs == rhs;
}

void part1() {
  std::fstream input("input2.txt");
  std::string s;
  std::getline(input, s);
  std::vector<ll> ranges;
  
  std::string c{};
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == '-' || *it == ',') {
      ranges.push_back(std::stoll(c));
      c = "";
    }
    else if (it == s.end() - 1) {
      c += *it;
      ranges.push_back(std::stoll(c));
    }
    else {
      c += *it;
    }
  }
  
  ll invalid_ids = 0; int iterations = 0;
  for (size_t i = 0; i < ranges.size() - 1; i += 2) {
    ll lower = ranges[i]; ll upper = ranges[i + 1];
    ll cur = lower;

    while (cur <= upper) {
      int num_digits = count_digits(cur);
      if (!(num_digits % 2) && compare(cur, num_digits)) {
        invalid_ids += cur;
      }
      cur = get_next(cur, num_digits);
      ++iterations;
    }
  }
  std::cout << "Invalid IDs: " << invalid_ids;
  std::cout << "\nTotal Iterations: " << iterations;
}

bool compare_all(ll x, int num_digits) { 
  for (int length = 1; length <= num_digits / 2; ++length) {
    if (num_digits % length) { continue; }

    std::vector<ll> seqs;
    ll temp = x;
    ll denom = std::pow(10, num_digits - length);

    while (denom > 0) {
      seqs.push_back(temp / denom);
      temp %= denom;
      denom /= std::pow(10, length);
    }

    if (std::all_of(seqs.begin(), seqs.end(), [&](ll cur){
      return cur == seqs[0];
    })) {
      return true;
    }
  }
  return false;
}

ll find_next2(ll x, int num_digits) {
  std::vector<ll> next;
  for (int length = 1; length <= num_digits / 2; ++length) {
    if (num_digits % length) { continue; }

    ll mult1 = std::pow(10, num_digits - length);
    ll temp1 = x / mult1;
    ll temp2 = (x / mult1) + 1;
    ll test1 = 0; ll test2 = 0;
    int length2 = length + (count_digits(temp2) - count_digits(temp1));
    ll mult2 = std::pow(10, num_digits - length2); 

    while (mult1 > 0) {
      test1 += temp1 * mult1;
      mult1 /= std::pow(10, length);
    }
    while (mult2 > 0) {
      test2 += temp2 * mult2;
      mult2 /= std::pow(10, length2);
    }

    if (test1 > x) { next.push_back(test1); } 
    if (test2 > x) { next.push_back(test2); }
  }
  if (!next.empty()) {
    return *std::min_element(next.begin(), next.end());
  }
  
  ll temp = 1;
  while (temp < x) {
    temp *= 10;
  }
  return find_next2(temp, num_digits + 1);
}

void part2() {
  std::fstream input("input2.txt");
  std::string s;
  std::getline(input, s);
  std::vector<ll> ranges;

  std::string c{};
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == '-' || *it ==  ',') {
      ranges.push_back(std::stoll(c));
      c = "";
    }
    else if (it == s.end() - 1) {
      c += *it;
      ranges.push_back(std::stoll(c));
    }
    else {
      c += *it;
    }
  }

  ll invalid_ids = 0;
  for (size_t i = 0; i < ranges.size() - 1; i += 2) {
    ll lower = ranges[i]; ll upper = ranges[i + 1];
    ll cur = lower;
    
    while (cur <= upper) {
      int num_digits = count_digits(cur);
      if (compare_all(cur, num_digits)) {
        invalid_ids += cur;
      }
      cur = find_next2(cur, num_digits);
    }
  }
  std::cout << "Invalid IDs: " << invalid_ids << "\n";
}

int main() {
  part1();
  part2();
  return 0;
}
