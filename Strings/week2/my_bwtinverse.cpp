#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		case '$': return 4; break;
		default: return -1;
	}
}

string InverseBWT(const string& bwt) {
  string text = "";

  // write your code here
  vector <char> last;
  for (int i=0; i<bwt.length(); i++) {
    last.push_back(bwt[i]);
  }
  // create an array where it row is index based for letters ACGT and the column index is the i'th appearance of the letter in the first/last column

  vector <char> first = last;
  sort(first.begin(), first.end());
  // cout << "first\n";
  // for (int i=0; i<first.size(); i++) {
  //   cout << first[i] << "\n";
  // }

	vector<vector <int>> last_array(5);
	for (int i=0; i<last.size(); i++) {
		int j = letterToIndex(last[i]);
		last_array[j].push_back(i);
	}
	vector<vector <int>> first_array(5);
	for (int i=0; i<first.size(); i++) {
		int j = letterToIndex(first[i]);
		first_array[j].push_back(i);
	}

	// cout << "first array\n";
	// for (int i=0; i<first_array.size(); i++){
	// 	for (int j=0; j<first_array[i].size(); j++){
	// 		cout << first_array[i][j] << "\n";
	// 	}
	// }

	int next = 0;
	int i = 0;
	int index = 0;
	while (text.length() < bwt.length()) {
		text.push_back(first[i]);
		next = first_array[letterToIndex(first[i])][index];
		// cout << "next: " << next << "\n";
		// first_array[letterToIndex(first[i])].pop();

		vector<int>::iterator it = find (last_array[letterToIndex(last[next])].begin(), last_array[letterToIndex(last[next])].end(), next);
		index = distance(last_array[letterToIndex(last[next])].begin(), it);
		// cout << "index: " << index << "\n";

		i = first_array[letterToIndex(last[next])][index];
		// cout << "i: " << i << "\n";
	}

	reverse(text.begin(), text.end());
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
