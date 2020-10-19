#include <iostream>
#include <string>
#include <vector>

using std::string;
using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<long long>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        cout << output[i] << " ";
    cout << "\n";
}

size_t polyHash(const string& s, int prime, int x) {
    // static const size_t multiplier = 263;
    // static const size_t prime = 1000000007;
    int hash = 0;
    for (int i = s.size()-1; i >=0 ; --i){
      hash = ((hash * x + s[i]) % prime + prime) % prime;
    }
    return  hash; //((hash % prime) + prime) % prime;
}

vector<long long> precomputeHashes(const string& T, long long size_P, int prime, int x) {
  vector<long long> H(T.size()-size_P+1);
  string S = &T[T.size()-size_P];
  // string S = T.substr(T.size()-size_P, T.size()-1);
  // cout << "S: " << S << "\n";
  H[T.size()-size_P] = polyHash(S, prime, x);
  // cout << T.size()-size_P << "\n";
  // cout << "H: " << H[T.size()-size_P] << "\n";
  long long y = 1;

  // for (int i=1; i <= size_P; i++){
  //   y = (((y*x) % prime) + prime) % prime;
  // }
  y = y % prime;

  for (int i=T.size()-size_P-1; i>=0; i--) {
    // cout << "T[i]: " << T[i] << "\n";
    // cout << "H[i+1]: " << H[i+1] << "\n";

    H[i] = (((x*H[i+1] + T[i] - y*T[i+size_P]) % prime) + prime) % prime;
  }
  return H;
}

int generate(int a){

  int input = rand() % a - 1;
  return input;
}

bool areEqual(string s1, string s2){
  // cout << s1 << " " << s2 << "\n";
  unsigned sz = s2.size();
  s1.resize(sz);
  // cout << s1 << "\n";
  if (s1 != s2) {
    return false;
  }
  // for (int i=0; i < s2.size() -1; ++i) {
  //   if (s1[i] != s2[i]) {
  //     return false;
  //   }
  // }
  return true;
}

vector<long long> get_occurrences(const Data& input) {
    const string& P = input.pattern, T = input.text;
    static const size_t prime = 1000000007; //(P.size()*T.size()*100)+7;
    const unsigned int x = 1; //generate(prime);
    // cout << "p: " << prime << "\n";
    vector<long long> result;
    size_t pHash = polyHash(P, prime, x);
    // cout << "pHash: " << pHash << "\n";
    vector<long long> H = precomputeHashes(T, P.size(), prime, x);
    // cout << "here\n";

    for (int i = 0; i <= T.size() - P.size(); ++i) {
      // cout << "i: " << i << "\n";
      // cout << "pHash: " << pHash << " H[i]: " << H[i] << "\n";
      // cout << "sub: " << T.substr(i, P.size()) << " P: " << P << "\n";
      // cout << &T[i] << "\n";

      if (pHash != H[i]) {
        continue;
      }

      // if (!strncmp(T.substr(i, P.size()), P)) {
      //   result.push_back(i);
      // }
      // cout << &T[i] << "\n";
      // string S = T.substr(T.size()-size_P, T.size()-1);

      if (areEqual(&T[i], P)) {
      // if (areEqual(T.substr(i, P.size()), P)) {

        // result.push_back(i);
        cout << i << " ";
      }
    }
    // cout << "result length: " << result.size() << "\n";
    cout << "\n";
    return result;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    get_occurrences(read_input());
    // print_occurrences(get_occurrences(read_input()));

    return 0;
}
