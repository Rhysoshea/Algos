#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <sys/time.h>

using namespace std;
using std::vector;

/*
count how many inversions there are in an array. An inversion is counted as a pair of numbers b and c, where b > c but comes after c from left to right.
This solution uses the merge sort algorithm.
*/

/*
Merge sort algorithm
*/

// void merge(vector<int> &A, int left, int mid, int right);
//
// void mergeSort(vector<int> &A, int left, int right) {
//
//   if (left < right) {
//
//     int mid = left + (right - left)/2;
//
//     mergeSort(A, left, mid);
//     mergeSort(A, mid+1, right);
//
//     merge(A, left, mid, right);
//   }
// }
//
// void merge(vector<int> &A, int left, int mid, int right) {
//   int m1 = mid - left + 1;
//   int m2 = right - mid;
//   vector<int> B(m1);
//   vector<int> C(m2);
//
//   for (int i=0; i < m1; i++) {
//     B[i] = A[left+i];
//   }
//   for (int j=0; j < m2; j++) {
//     C[j] = A[j+mid+1];
//   }
//   int k = left;
//   int i = 0;
//   int j = 0;
//
//   while (i < m1 && j < m2) {
//     if (B[i] <= C[j]) {
//       A[k] = B[i];
//       i++;
//     }
//     else {
//       A[k] = C[j];
//       j++;
//     }
//     k++;
//   }
//   while (i < m1) {
//     A[k] = B[i];
//     i++;
//     k++;
//   }
//   while (j < m2) {
//     A[k] = C[j];
//     j++;
//     k++;
//   }
// }

/*
Merge invert count algorithm
*/

long long merge(vector<int> &A, int left, int mid, int right);

long long mergeSort(vector<int> &A, int left, int right) {
  long long number_of_inversions = 0;
  if (left < right) {

    int mid = left + (right - left)/2;

    number_of_inversions += mergeSort(A, left, mid);
    number_of_inversions += mergeSort(A, mid+1, right);

    number_of_inversions += merge(A, left, mid, right);
  }
  return number_of_inversions;

}

long long merge(vector<int> &A, int left, int mid, int right) {
  long long inversions = 0;

  int m1 = mid - left + 1;
  int m2 = right - mid;
  vector<int> B(m1);
  vector<int> C(m2);

  for (int i=0; i < m1; i++) {
    B[i] = A[left+i];
  }
  for (int j=0; j < m2; j++) {
    C[j] = A[j+mid+1];
  }
  int k = left;
  int i = 0;
  int j = 0;

  while (i < m1 && j < m2) {
    if (B[i] <= C[j]) {
      A[k] = B[i];
      i++;
    }
    else {
      A[k] = C[j];
      j++;
      inversions += (m1-i);
      // cout << "k:  " << k << " j: " << j << "\n";
      // cout << "A[k]:  " << A[k] << " C[j]: " << C[j] << "\n";
    }
    k++;
  }
  while (i < m1) {
    A[k] = B[i];
    i++;
    k++;
  }
  while (j < m2) {
    A[k] = C[j];
    j++;
    k++;
  }
  return inversions;
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
  int n;
  cin >> n;
  vector<int> A(n);
  for (int i = 0; i < A.size(); i++) {
    cin >> A[i];
  }

  cout << mergeSort(A, 0, A.size()-1) << '\n';

  // for checking the sorted algorithm
  // mergeSort(A, 0, A.size()-1);
  // for (int i=0; i < A.size(); i++) {
  //   cout << A[i] << ' ';
  // }
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
