#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;
using std::cout;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.

vector<int> computePrefixFunction(string& bigS) {
  vector<int> smalls;
  smalls.push_back(0);
  int border = 0;

  for (int i=1; i<bigS.size(); i++) {
    while (border > 0 && bigS[i] != bigS[border]) {
      border = smalls[border-1];
    }
    if (bigS[i] == bigS[border]) {
      border = border + 1;
    } else {
      border = 0;
    }
    smalls.push_back(border);
  }

  return smalls;
}

vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  string bigS = pattern + '$' + text;

  vector<int> smalls;
  smalls = computePrefixFunction(bigS);

  for (int i=pattern.size()+1; i<bigS.size(); i++) {
    if (smalls[i] == pattern.size()) {
      result.push_back(i-2*pattern.size());
    }
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
