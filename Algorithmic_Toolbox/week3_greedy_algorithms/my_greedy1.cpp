#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>

using namespace std;
/*
find the minimum number of coins needed to change the input value into coins with denominations 1, 5 and 10
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
void test_solution(int m, int coins) {

    int remainder = m;

    if (remainder >= 10) {
      remainder -= 10;
      coins += 1;
      test_solution(remainder, coins);
    }
    else if (remainder >= 5) {
      remainder -= 5;
      coins += 1;
      test_solution(remainder, coins);
    }
    else if (remainder > 0) {
      remainder -= 1;
      coins += 1;
      test_solution(remainder, coins);
    }
    else {
      cout << coins << "\n";
      // return coins;
    }
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

  int m;
  int coins = 0;
  cin >> m;
  // function call
  test_solution(m, coins);
  // cout << test_solution(m, coins) << '\n';
  // cout << answer;
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
//     int m = generate();
//     int n = generate();
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
