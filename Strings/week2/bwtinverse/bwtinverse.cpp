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

string InverseBWT(const string& bwt) {
  string text = "";

  // write your code here
  vector <char> last(bwt.length());
  for (int i=0; i<bwt.length(); i++) {
    last.push_back(text[i]);

  }
  for (int i=0; i<last.size(); i++) {
    cout << last[i] << "\n";

  }

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
