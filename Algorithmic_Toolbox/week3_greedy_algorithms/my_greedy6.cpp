#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
using std::vector;
/*
Find the maximum amount of numbers that can sum to n, with each number being greater than the last
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
struct Segment {
  int start, end;
};

vector<int> test_solution(int n) {
  vector<int> summands;
  int remainder = n - 1;
  int ii = 1;
  if (n < 3) {
    summands.push_back(n);
    return summands;
  }
  summands.push_back(1);
  // if (n = 3) {
  //   summands.push_back(2)
  // }

  while (remainder > 0) {
    // cout << "remainder: " << remainder << " last: " << summands.back() << "\n";
    if (remainder <= summands.back()) {

      summands.back() += remainder;
      remainder = 0;
    }
    else {
      summands.push_back(summands.back() + 1);
      remainder -= summands.back();
      ii++;
    }
  }
  return summands;
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
  cin >> n;

  vector<int> summands = test_solution(n);

  cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    cout << summands[i] << ' ';
  }
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
