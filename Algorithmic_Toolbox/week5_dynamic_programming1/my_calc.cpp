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
vector<int> optimal_sequence(int n) {
  vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

/*
New, fast solution to test
*/


vector<int> test_sequence(int n) {
  vector <int> temp_sequence(n,n);
  temp_sequence[0] = 0;
  if (n == 1) {
    temp_sequence[0] = 1;
    return temp_sequence;
  }
  vector <int> sequence(n+1,n);
  sequence[0] = 0;
  sequence[1] = 0;
  // sequence[n] = 0;

  // create array
  for (int i=1; i < n; i++) {
    int m = i * 3;
    // cout << "i*3: "<< sequence[m] << "\n";
    if (m<=n && sequence[i]+1 < sequence[m]) {
      sequence[m] = sequence[i]+1;
    }
    m = i * 2;
    // cout << "i*2: "<< sequence[m] << "\n";
    if (m<=n && sequence[i]+1 < sequence[m]) {
      sequence[m] = sequence[i]+1;
    }
    m = i + 1;
    // cout << "i+1: "<< sequence[m] << "\n";
    if (m<=n && sequence[i]+1 < sequence[m]) {
      sequence[m] = sequence[i]+1;
    }
  }
  // resize vector to include the shortest path
  int q = n;
  int r = n;
  int s = n;

  vector <int> new_sequence;
  while (n >= 1) {
    new_sequence.push_back(n);
    if (n % 3 == 0) {
      q = sequence[n/3];
    }
    if (n % 2 == 0) {
      r = sequence[n/2];
    }
    if (n - 1 != 0) {
      s = sequence[n-1];
    }
    if (q<=r && q<=s) {
          n /= 3;
    } else if (r<s && r<q){
        n /= 2;
    } else {
        n = n-1;
    }
  }

  reverse(new_sequence.begin(), new_sequence.end());
  return new_sequence;
  // return sequence;
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
  int n;
  cin >> n;
  vector<int> sequence = test_sequence(n);
  cout << sequence.size() - 1 << endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << " ";
  }
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
