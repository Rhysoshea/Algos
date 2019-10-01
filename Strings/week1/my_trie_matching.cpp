#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>


using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;
using namespace std;


trie build_trie(const vector<string> & patterns) {

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

int find_edge(char symbol, int v, trie t) {
		bool match = false;
		int index = 0;
		int count = 0;
		int node = 0;
		for (auto& j: t[v]) {
			if (symbol == j.first) {
				match = true;
				index = count;
				break;
			}
			count ++;
		}
		if (match) {
			node = t[v].find(symbol)->second;
		}
		// edges f;
		// f.insert(std::pair<char,int>(t[node].first, node));

		return node;
}

bool trie_matching (const string& text, int n, trie t)
{
	// vector <int> result;
	// write your code here
	int i = 0;
	char symbol = text[i];
	// cout << "symbol: " << symbol << "\n";
	int v=0;
	bool forever = true;
	while (forever) {
		// edges f = find_edge();
		int next_node = find_edge(symbol, v, t);
		// cout << "here\n";
		if (t[v].empty()) {
			// cout << "yes\n";
			return true;
		} else if ( next_node != 0) {
			i++;
			symbol = text[i];
			v = next_node;
		} else {
			return false;
		}
	}
	return false;
}

vector <int> solve (string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	trie t = build_trie(patterns);
	// write your code here
	int index = 0;

	while (!text.empty()) {
		// cout << "text: " << text << "\n";
		if (trie_matching(text, n, t)) {
			result.push_back(index);
		};
		text.erase(0,1);
		index ++;
	}

	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++) {
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++) {
		cout << ans[i];
		if (i + 1 < (int) ans.size ()) {
			cout << " ";
		} else {
			cout << endl;
		}
	}

	return 0;
}
