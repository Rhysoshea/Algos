#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;
using std::vector;
using std::string;
/*
Compose the largest number out of a set of integers.
*/

/*
Base solution, naive but works
*/
int base_solution(int m) {

  return m;
}


/*
New, fast solution to test
*/

// bool isGreaterOrEqual(int a, int b) {
//   cout << "a: " << a << " b: " << b << "\n";
//   if (a >= 100 && b > 0) {
//     return false;
//   }
//   if (a > 0 && b >= 100) {
//     return true;
//   }
//   if (a >= 10 && b >= 10) {
//     return isGreaterOrEqual(a/10, b/10);
//     // return a >= b;
//   }
//   if (a < 10 && b >= 10) {
//     if (a == b/10) {
//       return isGreaterOrEqual(a, b%10);
//     }
//     return a >= b/10;
//   }
//   if (a >= 10 && b < 10) {
//     if (a/10 == b) {
//       return isGreaterOrEqual(a%10, b);
//     }
//     return a/10 >= b;
//   }
//   if (a < 10 && b < 10) {
//     // cout << "here\n";
//     return a >= b;
//   }
//   return false;
// }

// bool isGreaterOrEqual(int a, int b) {
//   int a_1;
//   int a_2;
//   int a_3;
//   int b_1;
//   int b_2;
//   int b_3;
//
//   a_1 = a/100;
//   b_1 = b/100;
//   a_2 = (a/10)%10;
//   b_2 = (b/10)%10;
//   a_3 = a%10;
//   b_3 = b%10;
//
//   cout << "a_1: " << a_1 << " a_2: " << a_2 << " a_3: " << a_3 << "\n";
//   cout << "b_1: " << b_1 << " b_2: " << b_2 << " b_3: " << b_3 << "\n";
//
//   if (a_1 == b_1) {
//
//   }
//
//   return true;
// }

bool isGreaterOrEqual(int a, int b) {

  stringstream c;
  stringstream d;

  c << a << b;

  d << b << a;

  int one;
  int two ;

  c >> int one;
  d >> int two;

  // cout << "one: " << one << "\n";
  // cout << "two: " << two << "\n";

  if (one >= two) {
    return true;
  }
  else {
    return false;
  }
}


string test_solution(vector<int> a) {

  stringstream ret;

  while (!a.empty()) {
    int maxDigit = -10000;
    int index = 0;
    for (size_t i = 0; i < a.size(); i++) {
      // cout << "a[i]" << a[i] << "\n";
      if (isGreaterOrEqual(a[i], maxDigit)) {
      // if (a[i] >= maxDigit) {
        // cout << "True\n";
        maxDigit = a[i];
        index = i;
      }
    }
    a.erase(a.begin() + index);

    ret << maxDigit;

  }
  string result;
  ret >> result;

  return result;
}


/*
Generator function for stress testing
*/
int generate(){
  int input = rand() % 10 + 1;
  return input;
}


/*
submission function
*/

int main() {
  int n;
  // int b;
  cin >> n;
  // cin >> b;
  vector<int> a(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> a[i];
    // cout << a[i] << "\n";
  }
  // cout << isGreaterOrEqual(n, b);
  cout << test_solution(a);
}

/*
test functions
*/
// int main() {
//
//   int m;
//   int capacity;
//   cin >> m >> capacity;
//   vector<double> values(m);
//   vector<double> weights(m);
//
//   struct timespec start, end;
//
//
//   for (int i = 0; i < m; i++) {
//     cin >> values[i] >> weights [i];
//   }
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   double value = test_solution(capacity, weights, values);
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
//
//   cout.precision(8);
//   cout << "Value: " << value << "\n";
//   // calculate and print time
//   double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
//   time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//   cout << "Time taken: " << fixed << time_taken;
//   cout << "sec" << endl;
// }


/*
stress testing
*/
// int main() {
//   struct timespec start, end;
//
//   while (true) {
//     int m;
//     int capacity;
//     m = generate();
//     vector<int> values(m);
//     vector<int> weights(m);
//
//     for (int i = 0; i < m; i++) {
//       values[i] = generate();
//       weights[i] = generate();
//     }
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int baseOut = base_solution(m, n);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int testOut = test_solution(m, n);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     if (baseOut != testOut) {
//       cout << "Input: " << m << "  " << n << "\n";
//       cout << "Base: " << baseOut << "  Test: " << testOut << "\n";
//       break;
//     }
//
//     cout << "Input: " << m << "  "<< n << "\n";
//     cout << "Base: " << fixed << time_takenB << "  Test: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
