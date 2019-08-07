#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <climits>


using std::vector;
using std::string;
using std::pair;
using std::min;
using namespace std;

/*
given a set of points find the smallest distance between a pair
*/



struct Point {
  int x, y;
};

float stripMin(vector<Point> &strip, int n, float d)
{
    float min = d;  // Initialize the minimum distance as d

    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) -> bool {
      return a.y < b.y;
    });
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n && (strip[j].y - strip[i].y) < min; ++j) {
          float check = sqrt(pow((strip[j].x - strip[i].x),2) + pow((strip[j].y - strip[i].y),2));
          if (check < min) {
            min = check;
          }
        }
    return min;
}

float quickMin(vector<Point> &points, int n) {
  float min = 100000;
  for (int j=0; j < n; j++) {
    for (int i=j+1; i < n; i++) {
      float check = sqrt(pow((points[j].x - points[i].x),2) + pow((points[j].y - points[i].y),2));
      // cout << "check: " << check << "\n";
      if (check < min) {
        min = check;
      }
    }
  }
  return min;
}

float getMin(vector<Point> &points, int l, int r) {
  float min = 100000;
  for (int j=l; j < r; j++) {
    for (int i=j+1; i < r; i++) {
      float check = sqrt(pow((points[j].x - points[i].x),2) + pow((points[j].y - points[i].y),2));
      // cout << "check: " << check << "\n";
      if (check < min) {
        min = check;
      }
    }
  }
  return min;
}

/*
New, fast solution to test
*/
double minimal_distance(vector<int> x, vector<int> y) {
  // write your code here
  // create sorted list from x
  vector<Point> points(x.size());
  for (int i=0; i<x.size(); i++) {
    points[i].x = x[i];
    points[i].y = y[i];
  }
  sort(points.begin(), points.end(), [](const Point &a, const Point &b) -> bool {
    return a.x < b.x;
  });

  if (x.size() < 4) {
    return quickMin(points, x.size());
  }
  // split midway through x
  int n = x.size();
  int mid = x.size()/2;
  Point midPoint = points[mid];

  // recursively call points on each side of the split to find minimum distance
  float min_left = getMin(points, 0, mid);
  float min_right = getMin(points, mid, x.size());

  // find the minimum of the two = d
  float d = min(min_left, min_right);
  // focus on the points within d of the midway split
  vector<Point> strip;
  for (int i = 0; i < points.size(); i++) {
    if (abs(points[i].x - midPoint.x) <= d) {
      strip.push_back(points[i]);
    }
  }
  // find the minimum distance between these points in the strip = d_prime
  // float min_strip = getMin(strip, 0, strip.size());

  // compare d and d_prime
  // float ans = min(d, min_strip);

  // return ans;
  return min(d, stripMin(strip, strip.size(), d));
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
  size_t n;
  cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  cout << fixed;
  cout << setprecision(9) << minimal_distance(x, y) << "\n";
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
