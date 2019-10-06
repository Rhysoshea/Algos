#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>


using std::vector;
using std::string;

using namespace std;


int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}

	bool isLeaf () const {
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

typedef vector<Node> trie;


int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: return -1;
	}
}


trie build_trie(const vector<string> & patterns) {

  trie t;
	Node e;
	t.push_back(e);

  for (int z=0; z < patterns.size(); z++) {
    int currentNode = 0;
    for (int i=0; i < patterns[z].length(); i++){

      char currentSymbol = patterns[z][i];

			// there is an edge with a matching letter so current node becomes node at end of edge
      if (t[currentNode].next[letterToIndex(currentSymbol)] != -1) {

        currentNode = t[currentNode].next[letterToIndex(currentSymbol)];
				if (i == patterns[z].length()-1) {
					t[currentNode].patternEnd = true;
				}
      }
			// there is not an edge with that letter so create one and put a node at the end of it
      else {
        Node f;
        t.push_back(f);
				t[currentNode].next[letterToIndex(currentSymbol)] = t.size()-1;
        currentNode = t.size()-1;
				if (i == patterns[z].length()-1) {
					// cout << "currentSymbol " << currentSymbol << "\n";
					// cout << "patternEnd\n";
					t[currentNode].patternEnd = true;
				}
      }
    }
  }
  return t;
}

bool trie_matching (string& text, int n, trie& t)
{
	vector <int> result;

	// write your code here
	int i = 0;
	char symbol = text[0];
	// cout << "symbol: " << symbol << "\n";

	Node v = t[0];
	bool forever = true;
	while (forever) {
		// cout << "symbol: " << symbol << "\n";
		if (v.patternEnd == true) {
			// cout << "end\n";
			return true;
		}
		if (v.isLeaf()) {
			// cout << "leaf\n";
			return true;
		}

		if ( v.next[letterToIndex(symbol)] != -1) {
			// if (v.patternEnd == true) {
	 		// 	cout << "end\n";
	 		// 	return true;
			// }
			i++;
			v = t[v.next[letterToIndex(symbol)]];
			// cout << "yes\n";
			if (!text[i]) {
				if (v.isLeaf()) {
					// cout << "A\n";
					return true;
				} else if (v.patternEnd == true) {
		 			// cout << "B\n";
		 			return true;
				} else {
				return false;
				}
			}
			symbol = text[i];
			// cout << "symbol: " << symbol << "\n";
		} else {
			return false;
		}
	}
	return false;
}



vector <int> solve (string& text, int n, const vector <string>& patterns)
{
	// struct timespec start, end;
	vector <int> result;
	// clock_gettime(CLOCK_MONOTONIC, &start);
	trie t = build_trie(patterns);
	// clock_gettime(CLOCK_MONOTONIC, &end);
	// double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	// time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	// cout << "Time taken: " << fixed << time_taken;
	// cout << "sec" << endl;
	// write your code here
	int index=0;
	// clock_gettime(CLOCK_MONOTONIC, &start);

	while (!text.empty()) {
		if (trie_matching(text, n, t)) {
			result.push_back(index);
		};
		text.erase(0,1);
		index ++;
	}

	// clock_gettime(CLOCK_MONOTONIC, &end);
	// double time_taken2 = (end.tv_sec - start.tv_sec) * 1e9;
	// time_taken2 = (time_taken2 + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	// cout << "Time taken: " << fixed << time_taken2;
	// cout << "sec" << endl;

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
