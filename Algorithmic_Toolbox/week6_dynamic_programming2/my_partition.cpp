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
Output 1, if it possible to partition 𝑣1, 𝑣2, . . . , 𝑣𝑛 into three subsets with equal sums, and 0 otherwise.
*/


/*
New, fast solution to test
*/
bool subSum (vector<int> X, int n, int a, int b, int c) {
  // cout << "a: " << a << " b: " << b << " c: " << c <<"\n";
  // cout << "n: " << n << "\n";
  if (a==0 && b==0 && c==0) {
    return true;
  }
  if (n < 0){
    return false;
  }

  // add to a
  bool A = false;
  if (a - X[n] >= 0) {
    A = subSum(X, n-1, a-X[n], b, c);
    // cout << "A: " << A << "\n";
  }
  // add to b
  bool B = false;
  if (b - X[n] >= 0) {
    B = subSum(X, n-1, a, b-X[n], c);
    // cout << "B: " << B << "\n";

  }
  // add to c
  bool C = false;
  if (c - X[n] >= 0) {
    C = subSum(X, n-1, a, b, c-X[n]);
    // cout << "C: " << C << "\n";

  }

  // if solution found return true
  // cout << "A: " << A << "\n";
  // cout << "B: " << B << "\n";
  // cout << "C: " << C << "\n";

  return A || B || C;
}

int partition3(vector<int> &A) {
  //write your code here
  if (A.size() < 3) {
    return 0;
  }
  int total=0;
  for (int i=0; i<A.size(); i++){
    total += A[i];
  }
  // cout << "total: " << total << "\n";
  if (total%3 != 0) {
    // cout << "not divisible by 3\n";
    return 0;
  }

  int third = total/3;
  // cout << "third: " << third << "\n";
  bool ans = subSum(A, A.size()-1, third, third, third);
  // cout << "ans: " << ans << "\n";
  if (ans) {
    return 1;
  }
  else {
    return 0;
  }
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
  int n;
  cin >> n;
  vector<int> A(n);
  // vector<int> A({1,2,3,4,5,5,7,7,8,10,12,19,25});
  for (size_t i = 0; i < A.size(); ++i) {
    cin >> A[i];
  }
  cout << partition3(A) << '\n';
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
