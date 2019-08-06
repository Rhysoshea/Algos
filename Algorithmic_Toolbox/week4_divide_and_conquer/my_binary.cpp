#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <sys/time.h>

using namespace std;
using std::vector;

/*
create a binary search algorithm which takes in an ascending array of integers and an array of search criteria, outputting the indices of the search values or -1 if they do not exist
*/

/*
Base solution, naive but works
*/
// linear search
int base_solution(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}


/*
New, fast solution to test
*/
// binary search
static int test_solution(const vector<int> &a,  int x) {

  int first = 0, last = (int)a.size();

  while (last > first) {
    int middle = floor((first+last)/2);
    // cout << "Middle " << a[middle] << "\n";
    if (x == a[middle]) {
      return middle;
    }
    else if (x < a[middle]) {
      last = middle;
    }
    else if (x > a[middle]){
      first = middle+1;
    }
  }
  return -1;
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
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  int m;
  cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }


  // cout << "Base: \n";
  // for (int i = 0; i < m; ++i) {
  //   //replace with the call to binary_search when implemented
  //   cout << base_solution(a, b[i]) << ' ';
  // }

  // cout << "Test: \n";
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    cout << test_solution(a, b[i]) << ' ';
  }
}

/*
test functions
*/
// int main() {
//
//   int m;
//   int coins = 0;
//   struct timespec start, end;
//
//   cin >> m;
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   test_solution(m, coins);
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
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
//     int n = generate();
//     vector<int> a(n);
//     for (size_t i = 0; i < a.size(); i++) {
//       a[i] = generate();
//     }
//     int m = generate();
//     vector<int> b(m);
//     for (int i = 0; i < m; ++i) {
//       b[i] = generate();
//     }
//
//     int first = 0, last = (int)a.size();
//
//     vector<int> ansB(m);
//     vector<int> ansT(m);
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     for (int i = 0; i < m; ++i) {
//       ansB[i] = base_solution(a, b[i]);
//     }
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     for (int i = 0; i < m; ++i) {
//       ansT[i] = test_solution(a, first, last, b[i]);
//     }
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     for (int j = 0; j < m; j++) {
//       if (ansB[j] != ansT[j]) {
//         cout << "Input 1: ";
//         for (int i = 0; i < m; i++) {
//           cout << a[i] << " ";
//         }
//         cout << "Input 2: ";
//         for (int i = 0; i < m; i++) {
//           cout << b[i] << " ";
//         }
//         cout << "\nBase: " << ansB[j] << "  Test: " << ansT[j] << "\n";
//         break;
//       }
//     }
//
//
//     // cout << "Input: " << m << "  "<< n << "\n";
//     cout << "Base: " << fixed << time_takenB << "  Test: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
