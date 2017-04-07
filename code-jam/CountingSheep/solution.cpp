#!/usr/bin/env cppsh
#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
  string calculate_sleep_number(int n) {
    if (!n) return "INSOMNIA";
    int sleep_number = n;
    vector<bool> seen(10, false);
    int seen_count = count(sleep_number, seen);
    while (seen_count != 10) {
      sleep_number += n;
      seen_count += count(sleep_number, seen);
    }
    return itos(sleep_number);
  }

private:
  int count(int n, vector<bool>& seen) {
    int new_digits = 0;
    while (n) {
      if (!seen[n % 10]) {
        seen[n % 10] = true;
        ++new_digits;
      }
      n /= 10;
    }
    return new_digits;
  }

  string itos(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
  }
};

int main(int argc, char *argv[])
{
  Solution soln;
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    int starting_number;
    cin >> starting_number;
    printf("Case #%d: %s\n", i, soln.calculate_sleep_number(starting_number).c_str());
  }

  return 0;
}
