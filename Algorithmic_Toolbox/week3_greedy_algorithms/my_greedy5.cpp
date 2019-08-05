#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
using std::vector;
/*
minimum number of cross over points between line segments
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
struct Segment {
  int start, end;
};

vector<int> test_solution(vector<Segment> &segments) {
  vector<int> points;
  //write your code here

  sort(segments.begin(), segments.end(), [](const Segment &a, const Segment &b) -> bool {
    return a.end < b.end;
  });

  int point = segments[0].end;
  // cout << "point: " << point;
  points.push_back(point);

  for (size_t i = 0; i < segments.size(); ++i) {
    if (point < segments[i].start || point > segments[i].end) {
      point = segments[i].end;
      points.push_back(point);
    }
    // points.push_back(segments[i].start);
    // points.push_back(segments[i].end);
  }
  // int max =  *max_element(points.begin(), points.end());
  // vector<int> counts(max, 0);

  // cout << "size: " << counts.size();
  // for (int i = 0; i < counts.size(); ++i) {
  //   for (int j = 0; j < points.size(); j+=2) {
  //     if (i+1 >= points[j] && i+1 <= points[j+1] ) {
  //       counts[i] += 1;
  //     }
  //   }
  // }

  return points;
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
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = test_solution(segments);
  cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    cout << points[i] << " ";
  }
}

/*
test functions
*/
// int main() {
//
//   int m;
//   int capacity;
//   cin >> m >> capacity;
//   vector<double> values(m);
//   vector<double> weights(m);
//
//   struct timespec start, end;
//
//
//   for (int i = 0; i < m; i++) {
//     cin >> values[i] >> weights [i];
//   }
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   double value = test_solution(capacity, weights, values);
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
//
//   cout.precision(8);
//   cout << "Value: " << value << "\n";
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
//     int m;
//     int capacity;
//     m = generate();
//     vector<int> values(m);
//     vector<int> weights(m);
//
//     for (int i = 0; i < m; i++) {
//       values[i] = generate();
//       weights[i] = generate();
//     }
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
