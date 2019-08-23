#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sys/time.h>
#include <csignal>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using namespace std;

/*
Your task is to implement this first step and convert a given array of integers into a heap. You will do that by applying a certain number of swaps to the array. Swap is an operation which exchanges elements 𝑎𝑖 and 𝑎𝑗 of the array 𝑎 for some 𝑖 and 𝑗. You will need to convert the array into a heap using only 𝑂(𝑛) swaps, as was described in the lectures. Note that you will need to use a min-heap instead of a max-heap in this problem.
*/

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  // void GenerateSwaps() {
  //   swaps_.clear();
  //   // The following naive implementation just sorts
  //   // the given sequence using selection sort algorithm
  //   // and saves the resulting sequence of swaps.
  //   // This turns the given array into a heap,
  //   // but in the worst case gives a quadratic number of swaps.
  //   //
  //   // TODO: replace by a more efficient implementation
  //   for (int i = 0; i < data_.size(); ++i)
  //     for (int j = i + 1; j < data_.size(); ++j) {
  //       if (data_[i] > data_[j]) {
  //         swap(data_[i], data_[j]);
  //         swaps_.push_back(make_pair(i, j));
  //       }
  //     }
  // }

  void siftDown(int i, int size) {
    // cout << "i: " << i << "\n";
    int minIndex = i;
    int l = 2*i+1;
    if (l < size && data_[l] < data_[minIndex]) {
      minIndex = l;
    }
    int r = 2*i+2;
    if (r < size && data_[r] < data_[minIndex]) {
      minIndex = r;
    }
    // cout << "minindex: " << minIndex << "\n";

    if (i != minIndex) {
      swap(data_[i], data_[minIndex]);
      swaps_.push_back(make_pair(i, minIndex));
      siftDown(minIndex, size);
    }
  }


  void GenerateSwaps() {
    swaps_.clear();
    // TODO: replace by a more efficient implementation
    int size = data_.size();
    for (int i = size/2; i >= 0; --i) {
      siftDown(i, size);
    }

  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}

/*
Test function
*/








/*
submission function
*/

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
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
