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

int indexToLetter (char letter) {
	switch (letter) {
		case 0: return 'A'; break;
		case 1: return 'C'; break;
		case 2: return 'G'; break;
		case 3: return 'T'; break;
		case 4: return '$'; break;
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
	vector<int> first_appear(4, -1);
	vector<int> record(4, 0);
	vector<int> count(4, 0);
	// int i=0;
	for (int i=0; i<bwt.length(); i++){
		char letter = last[i];
		int index = letterToIndex(letter);
		record[index] += 1;
		if (first_appear[index] == -1) {
			first_appear[index] = i;
		}
	}
	// for (int i =0; i<first_appear.size(); i++) {
	// 	cout << first_appear[i] << " ";
	// }
	// cout << "\n";
	// for (int i =0; i<record.size(); i++) {
	// 	cout << record[i] << " ";
	// }
	// cout << "\n";
	vector <char> first;
	first.push_back('$');
	for (int i=0; i<record.size(); i++) {
		for (int j=0; j<record[i]; j++) {
			first.push_back(indexToLetter(i));
		}
	}

	vector<int> last_to_first;
	for (int i=0; i<bwt.length(); i++){
		if (bwt[i] == 'A') {
			// cout << "count A: " << count[0] << "\n";
			last_to_first.push_back(1 + count[0]);
			count[0] += 1;
		}
		if (bwt[i] == 'C') {
			last_to_first.push_back(1 + record[0] + count[1]);
			count[1] += 1;
		}
		if (bwt[i] == 'G') {
			last_to_first.push_back(1 + record[0] + record[1] + count[2]);
			count[2] += 1;
		}
		if (bwt[i] == 'T') {
			last_to_first.push_back(1 + record[0] + record[1] + record [2] + count[3]);
			count[3] += 1;
		}
		if (bwt[i] == '$') {
			last_to_first.push_back(0);
		}
	}

	// text.push_back('$');
	int i = 0;
	while (text.length() < bwt.length()) {
		text.push_back(first[i]);
		i = last_to_first[i];
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
