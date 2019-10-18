#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
		case 'T': return 4; break;
		case '$': return 0; break;
		default: return 0;
	}
}

vector<int> sortCharacters(const string& text) {
  vector<int> order(text.size());
  int alphabet = 5;
  vector<int> count(alphabet, 0); //size of A C G T $

  for (int i=0; i<text.size(); i++) {
    count[letterToIndex(text[i])] = count[letterToIndex(text[i])]+1;
  }
  // cout << "print count\n";
  // for (int i=0; i<count.size(); i++ ){
  //   cout << count[i] << "\n";
  // }
  for (int j=1; j<alphabet; j++) {
    count[j] = count[j] + count[j-1];
  }
  // cout << "print count\n";
  // for (int i=0; i<count.size(); i++ ){
  //   cout << count[i] << "\n";
  // }
  for (int i=text.size()-1; i>=0; i--) {
    int c = letterToIndex(text[i]);
    count[c] = count[c] - 1;
    order[count[c]] = i;
  }
  return order;
}

vector<int> computeCharClasses(const string& text, vector<int> order) {
  vector<int> classes(text.size());
  classes[order[0]] = 0;

  for (int i=1; i<text.size(); i++) {
    if (text[order[i]] != text[order[i-1]]) {
      classes[order[i]] = classes[order[i-1]] + 1;
    } else {
      classes[order[i]] = classes[order[i-1]];
    }
  }
  return classes;
}

vector<int> sortDoubled(const string& text, int L, vector<int> order, vector<int> classes) {
  vector<int> count(text.size(), 0);
  vector<int> newOrder(text.size());

  for (int i=0; i<text.size(); i++) {
    count[classes[i]] = count[classes[i]]+1;
  }
  // cout << "print count\n";
  // for (int i=0; i<count.size(); i++ ){
  //   cout << count[i] << "\n";
  // }
  for (int j=1; j<text.size(); j++) {
    count[j] = count[j] + count[j-1];
  }
  // cout << "print count\n";
  // for (int i=0; i<count.size(); i++ ){
  //   cout << count[i] << "\n";
  // }
  for (int i=text.size()-1; i>=0; i--) {
    int start = (order[i] - L + text.size()) % text.size();
    int cl = classes[start];
    count[cl] = count[cl] - 1;
    newOrder[count[cl]] = start;
  }
  return newOrder;
}

vector<int> updateClasses(vector<int> newOrder, vector<int> classes, int L) {
  int n = newOrder.size();
  vector<int> newClass(n);

  newClass[newOrder[0]] = 0;
  // cout << "n: " << n <<"\n";
  for (int i=1; i<n; i++) {
    int cur = newOrder[i];
    int prev = newOrder[i-1];
    int mid = cur+L;
    int midPrev = (prev+L)%n;

    if (classes[cur] != classes[prev] || classes[mid] != classes[midPrev]) {
      newClass[cur] = newClass[prev]+1;
    } else {
      newClass[cur] = newClass[prev];
    }
  }
  return newClass;
}

vector<int> BuildSuffixArray(const string& text) {
  vector<int> order;
  vector<int> classes;
  // Implement this function yourself
  order = sortCharacters(text);
  // cout << "print order\n";
  // for (int i=0; i<order.size(); i++ ){
  //   cout << order[i] << "\n";
  // }
  classes = computeCharClasses(text, order);
  int L = 1;
  // cout << "print classes\n";
  // for (int i=0; i<classes.size(); i++ ){
  //   cout << classes[i] << "\n";
  // }

  while (L < text.size()) {
    // cout << "L: " << L << "\n";
    order = sortDoubled(text, L, order, classes);
    // cout << "print order\n";
    // for (int i=0; i<order.size(); i++ ){
    //   cout << order[i] << "\n";
    // }

    classes = updateClasses(order, classes, L);
    // cout << "print classes\n";
    // for (int i=0; i<classes.size(); i++ ){
    //   cout << classes[i] << "\n";
    // }
    L = 2*L;
  }

  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
