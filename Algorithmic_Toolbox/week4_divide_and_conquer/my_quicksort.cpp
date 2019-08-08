#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <sys/time.h>

using namespace std;
using std::vector;

/*
optimise the quicksort algorithm to make it faster, using a 3 way partition function instead of a 2 way partition
*/

/*
Base solution, naive but works
*/
int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  cout << "x: " << x << "\n";
  int j = l;
  cout << "j: " << j << "\n";

  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
      for (size_t i = 0; i < r+1; ++i) {
        cout << a[i] << ' ';
      }
      cout << "\n";
    }
    cout << "j: " << j << "\n";
  }
  swap(a[l], a[j]);
  for (size_t i = 0; i < r+1; ++i) {
    cout << a[i] << ' ';
  }
  cout << "\n";
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  cout << "k: " << k << "\n";
  cout << "l: " << l << "\n";

  swap(a[l], a[k]);

  for (size_t i = 0; i < r+1; ++i) {
    cout << a[i] << ' ';
  }
  cout << "\n";

  int m = partition2(a, l, r);

  for (size_t i = 0; i < r+1; ++i) {
    cout << a[i] << ' ';
  }
  cout << "\n";

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}



/*
New, fast solution to test
*/

void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
  int x = a[l];
  m1 = l;
  m2 = r;

  if (r - l <= 1) {
    if (a[r] < a[l]) {
      swap(a[r], a[l]);
    }
    m1 = l;
    m2 = r;
    return;
  }
  while (l <= r)  {

    if (a[l] < x) {
      swap(a[l], a[m1]);
      m1++;
      l++;
    }
    else if (a[l] == x) {
      l++;
    }
    else if (a[l] > x) {
      swap(a[l], a[m2]);
      m2--;
      r--;
    }
  }
  return;
}

void quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int m1, m2;
  partition3(a, l, r, m1, m2);


  quick_sort(a, l, m1-1);
  quick_sort(a, m2+1, r);

}

// void quick_sort(vector<int> &a, int l, int r) {
//   while (l < r) {
//
//     int k = l + rand() % (r - l + 1);
//     cout << "k: " << k << "\n";
//     cout << "l: " << l << "\n";
//
//     swap(a[l], a[k]);
//
//     // for (size_t i = 0; i < r+1; ++i) {
//     //   cout << a[i] << ' ';
//     // }
//     // cout << "\n";
//
//     // struct pivots {
//     //   int m1, m2;
//     // }
//     m = partition3(a, l, r);
//
//     // for (size_t i = 0; i < r+1; ++i) {
//     //   cout << a[i] << ' ';
//     // }
//     // cout << "\n";
//
//     if ((m - l) < (r-m)) {
//       quick_sort(a, l, m-1);
//       l = m + 1;
//     }
//     else {
//       quick_sort(a, m2, r);
//       r = m - 1;
//     }
//   }
// }


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
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << ' ';
  }
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
//       break;
//     }
//     cout << "Input: " << n << "\n";
//     cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
