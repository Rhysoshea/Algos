#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <sys/time.h>

using namespace std;
using std::vector;

/*
given a sequence of elements, check whether it contains an element that appears more than n/2 times (more than 50% of the elements), if yes output 1 else 0
implement technique in O(nlogn) time
*/

/*
Base solution, naive but works
*/
int base_solution(vector<int> &a, int left, int right) {
  for (int i = 0; i < right; i++) {
    int current = a[i];
    int count = 0;
    for (int j = 0; j < right; j++) {
      if (a[j] == current) {
        count += 1;
      }
    }
    if (count > right/2) {
      return 0;
    }
  }
  return -1;
}

/*
New, fast solution to test
*/
int get_majority_element(vector<int> &a, int left, int right) {
  if (left + 1 == right) {
      return a[left];
    }
  if (left + 2 == right) {
    if (a[left] == a[right-1]) {
      return a[left];
    }
    return -1;
  }

  vector<int> temp;

  for (int i = 0; i < right; i++) {
    if (a[i] == a[i+1]) {
      temp.push_back(a[i]);
    }
  }
  if (temp.empty()) {
    return -1;
  }
  return get_majority_element (temp, 0, temp.size());
}

// int test_solution (vector<int> &a, int left, int right) {
//   vector<int> temp;
//   // int m = get_majority_element(a, left, right);
//   for (int i = 0; i < right; i++) {
//     int count = 0;
//     if (a[i] == a[i+1]) {
//       for (int j = 0; j < right; j++) {
//         if (a[j] == a[i]) {
//           count += 1;
//           if (count > (right/2)) {
//             return a[i];
//           }
//         }
//       }
//     }
//   }
//   return -1;
// }

// int test_solution (vector<int> &a, int left, int right) {
//   vector<int> temp;
//   // int m = get_majority_element(a, left, right);
//   for (int i = 0; i < right; i++) {
//     if (a[i] == a[i+1]) {
//       // if (std::find(temp.begin(), temp.end(),a[i])==temp.end()) {
//         temp.push_back(a[i]);
//       // }
//     }
//   }
//   for (int k = 0; k<temp.size(); k++) {
//     int count = 0;
//     for (int j = 0; j < right; j++) {
//       if (a[j] == temp[k]) {
//         count += 1;
//         if (count > (right/2)) {
//           return temp[k];
//         }
//       }
//     }
//   }
//   return -1;
// }

// int test_solution(vector<int> &a, int left, int right) {
//   if (left == right) return -1;
//   if (left + 1 == right) return a[left];
//   //write your code here
//   int middle = floor((left+right)/2);
//
//   int first = test_solution (a, left, middle);
//   int second = test_solution (a, middle+1, right);
//   int count_first = 0;
//   int count_second = 0;
//   if ((first != -1) || (second != -1)) {
//     for (int j = 0; j < right; j++) {
//       if (a[j] == first) {
//         count_first += 1;
//         if (count_first > right/2) {
//           return first;
//         }
//       }
//       else if (a[j] == second) {
//         count_second += 1;
//         if (count_second > right/2) {
//           return second;
//         }
//       }
//     }
//   }
//   return -1;
// }

int test_solution(vector<int> &arr, int left, int right) {
    int count = 0, i, majorityElement;
    // read through the array and find the element with the highest count
    for (i = 0; i < right; i++) {
        if (count == 0)
            majorityElement = arr[i];
        if (arr[i] == majorityElement)
            count++;
        else
            count--;
    }
    // read through the array a second time checking whether that element exceeds 50% of the elements
    count = 0;
    for (i = 0; i < right; i++)
        if (arr[i] == majorityElement)
            count++;
    if (count > right/2)
        return majorityElement;
    return -1;
}

//   for (int i = 0; i < (right/2)+1; i++) {
//     int current = a[i];
//     int count = 0;
//     for (int j = 0; j < right; j++) {
//       if (a[j] == current) {
//         count += 1;
//       }
//     }
//     if (count > right/2) {
//       return 0;
//     }
//   }
//   return -1;
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
  cout << (test_solution(a, 0, a.size()) != -1) << '\n';
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
