#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
int k=0;

int main() {
  for (int i=0; i<10; i++) {
    k += 1 << i;
    cout << "i: " << i << " ";
    cout << "(1<<1): " << (1<<i) << " ";
    cout << "k: " << k << " ";
    cout << "(k ^ (1<<i)): " << (k ^ (1<<i)) << endl;
  }
  return 0;
}
