#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using namespace std;

const int INPUT = 400;

// #define DEBUG
#define LOOP(i, m) for(int i = 0; i < m; i++)
#define RLOOP(i, m) for(int i = m; i > 0; i--) // reverse loop
// #define SLOOP(i, m) for(set<int>::iterator i = m.begin(); i!=m.end(); i++) // loop for sets

bool isOptimized(int k, vector<string> &reads) {
    set<string> kmers;
    for (string read : reads) {
      LOOP (i, read.size()-k+1){
        kmers.insert(read.substr(i,i+k));
      }
    }
    set<string> prefixes;
    set<string> suffixes;

    #ifdef DEBUG
      cout << "kmers: " << endl;
      for (std::set<string>::iterator it = kmers.begin(); it!=kmers.end(); it++) {
        cout << *it << endl;
      }
    #endif

    for (string kmer : kmers) {
      prefixes.insert(kmer.substr(0,kmer.size()-1));
      suffixes.insert(kmer.substr(1,kmer.size()));
    }

    #ifdef DEBUG
      cout << "prefixes: " << endl;
      for (std::set<string>::iterator it = prefixes.begin(); it!=prefixes.end(); it++) {
        cout << *it << endl;
      }
      cout << "suffixes: " << endl;
      for (std::set<string>::iterator it = suffixes.begin(); it!=suffixes.end(); it++) {
        cout << *it << endl;
      }
    #endif

    return prefixes == suffixes;
}

int main() {
  vector<string> reads(INPUT);
  LOOP (i,INPUT) {
    cin >> reads[i];
  }

#ifdef DEBUG
  cout << "reads: " << endl;
  LOOP (i, reads.size()) {
    cout << reads[i] << endl;
  }
#endif

  RLOOP(k, reads[0].size()) {
    if (isOptimized(k, reads)){
      cout << k << endl;
      break;
    }
  }

  return 0;
}
