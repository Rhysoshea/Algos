#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <csignal>


using namespace std;
using std::vector;

/*
given x, find the minimum number of operations to get to n with only x*2, x*3 and x=1 as possible operations
*/

/*
Base solution, naive but works
*/
int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
}


/*
New, fast solution to test
*/

int test_weight(int W, int n, const vector<int> &w) {
  //write your code here
  vector< vector<int> > D(n+1, vector<int>(W+1));
  // initialize all values
  // cout << "n " << n << "\n";
  // cout << "W " << W << "\n";

  D[0][0] = 0;
  for (int i=1; i<=n; i++) {
    D[i][0] = 0;
    // cout << str1[i] << "\n";
  }
  for (int j=1; j<=W; j++) {
    D[0][j] = 0;
    // cout << str2[j] << "\n";
  }

  // for (int i=0; i<=n; i++) {
  //   for (int j=0; j<=W; j++) {
  //     cout << "i: " << i << " j: " << j << " D: " << D[i][j] << "\n";
  //   }
  // }

  for (int i=1; i <=n; i++) {
    for (int v=1; v <= W; v++) {
      D[i][v] = D[i-1][v];
      // cout << "w[i]: " << w[i-1] << "\n";
      if (w[i-1] <= v) {
        int val = D[i-1][v-w[i-1]] + w[i-1];
        if (D[i][v] < val) {
          D[i][v] = val;
        }
      }
    }
  }
  // for (int i=0; i<=n; i++) {
  //   for (int j=0; j<=W; j++) {
  //     cout << "i: " << i << " j: " << j << " D: " << D[i][j] << "\n";
  //   }
  // }
  return D[n][W];
  // return 0;
}



/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
   // cout << str1 << " " << str2;

   // cleanup and close up stuff here
   // terminate program

   exit(signum);
}


/*
submission function
*/

int main() {
  int n, W;
  cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  cout << test_weight(W, n, w) << '\n';
}
/*
test functions
*/
// int main() {
//
//   int n = generate(100000);
//   vector<int> a(n);
//   for (size_t i = 0; i < a.size(); ++i) {
//     a[i] = generate(1000000000);
//   }
//
//   struct timespec start, end;
//
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   test_solution(a, 0, a.size());
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
//   // calculate and print time
//   double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
//   time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//   cout << "n: " << n << "\n";
//   cout << "Time taken: " << fixed << time_taken;
//   cout << "sec" << endl;
// }


/*
stress testing
*/
// int main() {
//   struct timespec start, end;
//
//   signal(SIGINT, signalHandler);
//   while (true) {
//     int n = generate(1000000);
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     vector <int> sequence_base = optimal_sequence(n);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     vector <int> sequence_test = test_sequence(n);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     if (sequence_base.size()-1 != sequence_test.size()-1) {
//       cout << "Input: " << n << "\n";
//       cout << "Base: " << sequence_base.size()-1 << " Test: " << sequence_test.size()-1 << "\n";
//       // break;
//     }
//     cout << "Input: " << n << "\n";
//     cout << "Base: " << sequence_base.size()-1 << " Test: " << sequence_test.size()-1 << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
