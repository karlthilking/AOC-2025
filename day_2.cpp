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

int main() {
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
  
  ll invalid_ids = 0;
  for (size_t i = 0; i < ranges.size() - 1; i += 2) {
    ll lower = ranges[i]; ll upper = ranges[i + 1];
    ll cur = lower;

    while (cur <= upper) {
      int num_digits = count_digits(cur);
      if (!(num_digits % 2) && compare(cur, num_digits)) {
        invalid_ids += cur;
      }
      cur = get_next(cur, num_digits);
    }
  }
  std::cout << "Invalid IDs: " << invalid_ids;
}
