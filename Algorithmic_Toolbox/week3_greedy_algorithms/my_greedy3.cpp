#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>
#include <algorithm>
#include <vector>

using namespace std;
using std::vector;
/*
You are going to travel to another city that is located 𝑑 miles away from your home city. You can can travel at most 𝑚 miles on a full tank and you start with a full tank. Along your way, there are gas stations at distances stop1, stop2, . . . , stop𝑛 from your home city. What is the minimum number of refills needed?
*/

/*
Base solution, naive but works
*/


/*
New, fast solution to test
*/
int compute_min_refills(int d, int m, vector<int> & stops) {
    // write your code here
    int numRefills = 0;
    int currentRefill = 0;

    stops.insert(stops.begin(), 0);
    stops.push_back(d);
    int n = stops.size();
    // for (int i=0; i < stops.size(); i++) {
    //   cout << stops[i] << " ";
    // }

    while (currentRefill < n) {
      // cout << "numRefills: " << numRefills << "\n";

      int lastRefill = currentRefill;
      // cout << "currentRefill: " << currentRefill << "\n";
      while (currentRefill < n && ((stops[currentRefill+1] - stops[lastRefill]) <= m)) {
        // if (currentRefill+1 > n) {
          // break;
        // }
        currentRefill += 1;
        // cout << "currentRefill: " << currentRefill << "\n";

      }
      // cout << "currentRefill: " << currentRefill << "\n";
      // cout << "lastRefill: " << lastRefill << "\n";

      if (currentRefill == lastRefill) {
        return -1;
      }

      if (currentRefill < n-1) {
        numRefills += 1;
      }
    }
    if (d - stops[currentRefill-1] <= m) {
      return numRefills;
    }
    else {
      return -1;
    }
}

// int compute_min_refills(int d, int n, int m, vector<int> & stops) {
//     // write your code here
//     int numRefills = 0;
//     int currentRefill = 0;
//
//
//     while (currentRefill < n) {
//       cout << "numRefills: " << numRefills << "\n";
//
//       int lastRefill = currentRefill;
//       cout << "currentRefill: " << currentRefill << "\n";
//       while (currentRefill < n && ((stops[currentRefill+1] - stops[lastRefill]) <= m)) {
//         // if (currentRefill+1 > n) {
//           // break;
//         // }
//         currentRefill += 1;
//         cout << "currentRefill: " << currentRefill << "\n";
//
//       }
//       cout << "currentRefill: " << currentRefill << "\n";
//       cout << "lastRefill: " << lastRefill << "\n";
//
//       if (currentRefill == lastRefill) {
//         return -1;
//       }
//
//       if (currentRefill <= n) {
//         numRefills += 1;
//       }
//     }
//     if (d - stops[currentRefill] <= m) {
//       return numRefills;
//     }
//     else {
//       return -1;
//     }
// }

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
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops[i];

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
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
