#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>
#include <algorithm>
#include <vector>

using namespace std;
using std::vector;
/*
output the maximum dot product of two sequences of integers
*/

/*
Base solution, naive but works
*/
int base_solution(int m) {

  return m;
}


int check_max(long long array[][3], int num) {
  int max = 0;
  int index = 0;
  for (int ii=0; ii < num; ii++) {
    if (array[ii][2] > max){
      max = array[ii][2];
      index = ii;
    }
  }
  return index;
}

// void vector_sort(vector<int> input) {
//   return sort(input.begin(), input.end());
// }

/*
New, fast solution to test
*/
long long test_solution(vector<long long> a, vector<long long> b) {
  long long result = 0;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  for (size_t i = 0; i < a.size(); i++) {
    result += ((double) a[i]) * b[i];
  }
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
  size_t n;
  cin >> n;
  vector<long long> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    cin >> b[i];
  }
  cout << test_solution(a, b) << endl;
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
