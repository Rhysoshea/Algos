#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

string BWT(string& text) {
  string result = "";

  // write your code here
  vector<string> grid(text.length());

  for (int i=0; i<text.length(); i++) {
    grid[i] = text;
    // cout << grid[i] << "\n";
    text.push_back(text[0]);
    text.erase(0,1);
  }
  sort(grid.begin(), grid.end());
  for (int i=0; i<text.length(); i++) {
    // cout << grid[i] << "\n";
    result.push_back(grid[i].back());
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
