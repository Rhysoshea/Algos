#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
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


/*
New, fast solution to test
*/


int edit_distance(const string &str1, const string &str2) {
  //write your code here
  int n = str1.length();
  int m = str2.length();
  // cout << "n " << n << " m " << m << "\n";
  int insert, del, match, mis;
  vector< vector<int> > D(n+1, vector<int>(m+1));
  // int D[n][m];
  D[0][0] = 0;
  for (int i=1; i<=n; i++) {
    D[i][0] = i;
    // cout << str1[i] << "\n";
  }
  for (int j=1; j<=m; j++) {
    D[0][j] = j;
    // cout << str2[j] << "\n";
  }
  // for (int j=0; j<=m; j++) {
  //   for (int i=0; i<=n; i++) {
  //     cout << "i: " << i << " j: " << 0 << " D: " << D[i][0] << "\n";
  //   }
  // }
  for (int j=1; j<m+1; j++) {
    for (int i=1; i<n+1; i++) {
      insert = (D[i][j-1]) +1;
      del = (D[i-1][j]) +1;
      match = D[i-1][j-1];
      mis = (D[i-1][j-1]) +1;
      // cout << "insert: " << insert << "\n";
      // cout << "del: " << del << "\n";
      // cout << "match: " << match << "\n";
      // cout << "mis: " << mis << "\n";
      // cout << "i " << j << " j " << j << "\n";
      // cout << "str1: " << str1[i-1] << " str2: " << str2[j-1] << "\n";
      if (str1[i-1] == str2[j-1]) {
        D[i][j] = min(min(insert, del), match);
      } else {
        D[i][j] = min(min(insert, del), mis);
      }
    }
  }
  // for (int j=0; j<=m; j++) {
  //   for (int i=0; i<=n; i++) {
  //     cout << "i: " << i << " j: " << j << " D: " << D[i][j] << "\n";
  //   }
  // }
  // cout << "\n";
  return D[n][m];
  // return 0;
}



/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}

// void signalHandler( int signum ) {
//    cout << "Interrupt signal (" << signum << ") received.\n";
//    // cout << str1 << " " << str2;
//
//    // cleanup and close up stuff here
//    // terminate program
//
//    exit(signum);
// }
/*
submission function
*/

int main() {
  string str1;
  string str2;
  cin >> str1 >> str2;
  // signal(SIGINT, signalHandler);
  cout << edit_distance(str1, str2) << endl;
  return 0;
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
//   while (true) {
//     int n = generate(100000);
//     vector<int> a(n);
//     for (size_t i = 0; i < a.size(); ++i) {
//       a[i] = generate(1000000000);
//     }
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int solution_base = base_solution(a, 0, a.size());
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int solution_test = test_solution(a, 0, a.size());
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     if (solution_base != solution_test) {
//       cout << "Input: " << n << "\n";
//       cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//       // break;
//     }
//     cout << "Input: " << n << "\n";
//     cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
