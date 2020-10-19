#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;
using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;


trie build_trie(vector<string> & patterns) {

  trie t;

  for (int z=0; z < patterns.size(); z++) {
    int currentNode = 0;
    for (int i=0; i < patterns[z].length(); i++){

      if (t.empty()) {
        edges e;
        e.insert(std::pair<char,int>(patterns[z][i], t.size()+1) );
        t.push_back(e);
        currentNode += 1;
        edges f;
        t.push_back(f);
        continue;
      }
      char currentSymbol = patterns[z][i];
      bool match = false;
      int index = 0;
      int count = 0;
      for (auto& j: t[currentNode]) {
        if (currentSymbol == j.first) {
          match = true;
          index = count;
          break;
        }
        count ++;
      }
      if (match) {
        currentNode = t[currentNode].find(currentSymbol)->second;
      }
      else {
        edges f;
        t.push_back(f);
        t[currentNode].insert(std::pair<char,int>(currentSymbol, t.size()-1) );
        currentNode = t.size()-1;
      }

    }
  }

  return t;
}

int main() {
  size_t n;
  cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    cin >> s;
    patterns.push_back(s);
  }
  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
