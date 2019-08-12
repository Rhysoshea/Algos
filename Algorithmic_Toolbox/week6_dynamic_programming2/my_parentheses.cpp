#include <iostream>
#include <cassert>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <csignal>
#include <cstdlib>

using namespace std;
using std::vector;
using std::string;
using std::max;
using std::min;

/*
given an arithmetic expression of integers and mathematical operators, determine the maximum output and optimal placement of parentheses
*/

/*
Base solution, naive but works
*/
// int optimal_weight(int W, const vector<int> &w) {
//   //write your code here
//   int current_weight = 0;
//   for (size_t i = 0; i < w.size(); ++i) {
//     if (current_weight + w[i] <= W) {
//       current_weight += w[i];
//     }
//   }
//   return current_weight;
// }


/*
New, fast solution to test
*/
long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

long long * minmax(int i, int j, vector< vector<long long> > &m, vector< vector<long long> > &M, char *operators) {
  static long long result[2];
  result[0] = 100000;
  result[1] = -100000;
  // cout << "i: " << i << "\n";
  // cout << "j: " << j << "\n";
  for (int k=i; k < j; k++) {
    char op = operators[k];
    // cout << "op: " << op << "\n";
    // cout << "M[i][k]: " << M[i][k] << " M[k+1][j]: " << M[k+1][j] << "\n";
    long long a = eval(M[i][k], M[k+1][j], op);
    long long b = eval(M[i][k], m[k+1][j], op);
    long long c = eval(m[i][k], M[k+1][j], op);
    long long d = eval(m[i][k], m[k+1][j], op);
    // cout << "a: " << a << "\n";
    // cout << "b: " << b << "\n";
    // cout << "c: " << c << "\n";
    // cout << "d: " << d << "\n";
    result[0] = min(result[0], min(a, min(b, min(c, d))));
    result[1] = max(result[1], max(a, max(b, max(c, d))));
    // cout << "0: " << result[0] << "\n";
    // cout << "1: " << result[1] << "\n";
  }
  return result;
}

long long get_maximum_value(const string &exp) {
  //write your code here


  float n = exp.size();
  int l = ceil(n/2);
  // cout << "l: " << l << "\n";
  vector< vector<long long> > m(l, vector<long long>(l));
  vector< vector<long long> > M(l, vector<long long>(l));

  char operators[l-1];
  int j=0;
  for (int i=1; i < n; i+=2) {
    operators[j] = exp[i];
    j++;
  }
  // for (int x=0; x < l-1; x++) {
  //   cout << operators[x] << " ";
  // }

  for (int i=0; i < l; i++) {
    m[i][i] = exp[2*i] - '0';
    // cout << m[i][i] << " ";
    M[i][i] = exp[2*i] - '0';
  }
  // for (int i=0; i < l; i++) {
  //   cout << m[i][i] << " ";
  // }
  // for (int i=0; i < l; i++) {
  //   cout << M[i][i] << " ";
  // }

  for (int s=1; s < l; s++) {
    for (int i=0; i < l-s; i++) {
      // cout << "l: " << l << "\n";
      // cout << "s: " << s << "\n";
      int j = i+s;
      long long *array;
      array = minmax(i, j, m, M, operators);
      // cout << "min: " << array[0] << "\n";
      // cout << "max: " << array[1] << "\n";

      m[i][j] = array[0];
      M[i][j] = array[1];
    }
  }
  return M[0][l-1];
  // return 0;
}



/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}


/*
submission function
*/

int main() {
  string s;
  cin >> s;
  cout << get_maximum_value(s) << '\n';
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
