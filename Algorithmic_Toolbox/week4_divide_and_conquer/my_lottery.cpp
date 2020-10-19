#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <sys/time.h>

using namespace std;
using std::vector;

/*
given a set of points and a set of segments, return the number of segments each point exists in.
*/

/*
Base solution, naive but works
*/
vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}


/*
New, fast solution to test
*/
// void merge(int *a, int left, int mid, int right);

void partition3(vector< vector<int> > &a, int l, int r, int &m1, int &m2) {
  int x = a[l][0];
  m1 = l;
  m2 = r;

  if (r - l <= 1) {
    if (a[r][0] < a[l][0]) {
      swap(a[r][0], a[l][0]);
      swap(a[r][1], a[l][1]);
    }
    m1 = l;
    m2 = r;
    return;
  }
  while (l <= r)  {

    if (a[l][0] < x) {
      swap(a[l][0], a[m1][0]);
      swap(a[l][1], a[m1][1]);
      m1++;
      l++;
    }
    else if (a[l][0] == x) {
      l++;
    }
    else if (a[l][0] > x) {
      swap(a[l][0], a[m2][0]);
      swap(a[l][1], a[m2][1]);
      m2--;
      r--;
    }
  }
  return;
}

void quick_sort(vector< vector<int> > &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int m1, m2;
  partition3(a, l, r, m1, m2);


  quick_sort(a, l, m1-1);
  quick_sort(a, m2+1, r);

}

vector<int> find_index(vector<int> array, int number) {
  int index = 0;
  vector<int> indices;
  for (index=0; index < array.size(); index++){
    if (array[index] == number) {
      indices.push_back(index);
    }
  }
  return indices;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());


  // allocate left(0), right(1) and point(2) pairs
  // int arr[points.size()+starts.size()+ends.size()][2];
  // use merge sort, on the merge step allocate a code depending on its origin
  // sort everything in ascending order
  int rows = points.size()+starts.size()+ends.size();
  vector< vector<int> > arr(rows, vector<int>(2));

  // int size = sizeof(arr)/sizeof(*arr);
  for (int i=0; i < arr.size(); i++) {
    for (int j=0; j < starts.size(); j++) {
      arr[i][0] = starts[j];
      arr[i][1] = 0;
      i++;
    }
    for (int j=0; j < points.size(); j++) {
      arr[i][0] = points[j];
      arr[i][1] = 1;
      i++;
    }
    for (int j=0; j < ends.size(); j++) {
      arr[i][0] = ends[j];
      arr[i][1] = 2;
      i++;
    }

  }

  // cout << "Array: \n";
  // for (int i=0; i < arr.size(); i++) {
  //   cout << arr[i][0] << " " << arr[i][1] << "\n";
  // }

  // vector < vector<int> > new_starts(starts,1);
  // use quicksort to initially sort arrays
  quick_sort(arr, 0, arr.size() - 1);

  // cout << "Array: \n";
  // for (int i=0; i < arr.size(); i++) {
  //   cout << arr[i][0] << " " << arr[i][1] << "\n";
  // }

  for (int i=0; i < arr.size()-1; i++) {
    if (arr[i+1][0] == arr[i][0]) {
      if (arr[i+1][1] < arr[i][1]) {
        swap(arr[i][0], arr[i+1][0]);
        swap(arr[i][1], arr[i+1][1]);
      }
    }
  }

  // cout << "Array: \n";
  // for (int i=0; i < arr.size(); i++) {
  //   cout << arr[i][0] << " " << arr[i][1] << "\n";
  // }


  // int j = 0;
  int count = 0;
  // cout << "point: " << points[j] << "\n";

  for (int i=0; i < arr.size(); i++) {
    if (arr[i][1] == 1) {
      vector<int> indices = find_index(points, arr[i][0]);
      for (int index=0; index < indices.size(); index++){
          cnt[indices[index]] = count;
      }

      // cout << "count: " << count << "\n";
    }
    else if (arr[i][1] == 0) {
      count ++;
    }
    else if (arr[i][1] == 2) {
      count --;
    }
  }

  return cnt;
}



/*
Generator function for stress testing
*/
int generate(int a, int b){

  int input = rand() % a + b;
  return input;
}


/*
submission function
*/

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    cout << cnt[i] << ' ';
  }
  // cout << "\n";
  // vector<int> base_cnt = naive_count_segments(starts, ends, points);
  // for (size_t i = 0; i < base_cnt.size(); i++) {
  //   cout << base_cnt[i] << ' ';
  // }
}

/*
test functions
*/
// int main() {
//   // int n, m;
//   // cin >> n >> m;
//   int n = 13;
//   int m = 19;
//   int points_ints[] = {-56 -32 -10 -76 -4 -70 -97 -78 -34 -51 -76 -99 -47 -23 -92 -72 -67 -2 -19};
//   int starts_ints[] = {-22, -65, -74, -33, -67, -51, -79, -28, -64, -55, -9, -43, -47};
//   int ends_ints[] = {-6, 32, -62, -23, 12, 28, -12, 65, 21, -27, 85, -42, -39};
//
//   vector<int> starts( starts_ints, starts_ints + sizeof(starts_ints)/sizeof(int));
//   vector<int> ends( ends_ints, ends_ints + sizeof(ends_ints)/sizeof(int));
//   // for (size_t i = 0; i < starts.size(); i++) {
//   //   cin >> starts[i] >> ends[i];
//   // }
//   vector<int> points( points_ints, points_ints + sizeof(points_ints)/sizeof(int));
//   for (size_t i = 0; i < points.size(); i++) {
//     cout << points[i] << " ";
//   }
//
//
//
//   //use fast_count_segments
//   vector<int> cnt = fast_count_segments(starts, ends, points);
//   for (size_t i = 0; i < cnt.size(); i++) {
//     cout << cnt[i] << ' ';
//   }
//   cout << "\n";
//   vector<int> base_cnt = naive_count_segments(starts, ends, points);
//   for (size_t i = 0; i < base_cnt.size(); i++) {
//     cout << base_cnt[i] << ' ';
//   }
// }


/*
stress testing
*/
// int main() {
//   struct timespec start, end;
//   bool progress = true;
//   while (progress == true) {
//     int n = generate(20, 0);
//     int m = generate(20, 0);
//     vector<int> starts(n), ends(n);
//     for (size_t i = 0; i < starts.size(); ++i) {
//       starts[i] = generate(100, -100);
//       ends[i] = generate(100, starts[i]);
//     }
//     vector<int> points(m);
//     for (size_t i = 0; i < points.size(); i++) {
//       points[i] = generate(100, -100);
//     }
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     vector<int> base_cnt = naive_count_segments(starts, ends, points);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     vector<int> test_cnt = fast_count_segments(starts, ends, points);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // for (int j = 0; j < test_cnt.size(); j++) {
//     //   if (base_cnt[j] != test_cnt[j]) {
//     //     cout << "Input: " << points[j] << "\n";
//     //     cout << "Base: " << base_cnt[j] << " Test: " << test_cnt[j] << "\n";
//     //     progress = false;
//     //     for (int j = 0; j < starts.size(); j++) {
//     //       cout << starts[j] << " " << ends[j] << "\n";
//     //     }
//     //     cout << "Points: ";
//     //     for (int j = 0; j < points.size(); j++) {
//     //       cout << points[j] << " ";
//     //     }
//     //     cout << "\n";
//     //   }
//     // }
//
//     cout << "\n";
//       for (size_t i = 0; i < base_cnt.size(); i++) {
//         cout << base_cnt[i] << ' ';
//       }
//     cout << "\n";
//       for (size_t i = 0; i < test_cnt.size(); i++) {
//         cout << test_cnt[i] << ' ';
//       }
//     if ((std::equal(base_cnt.begin(), base_cnt.end(), test_cnt.begin()))==false) {
//       progress = false;
//     }
//     for (int j = 0; j < starts.size(); j++) {
//       cout << starts[j] << " " << ends[j] << "\n";
//     }
//     cout << "Points: ";
//     for (int j = 0; j < points.size(); j++) {
//       cout << points[j] << " ";
//     }
//     cout << "\n";
//     // cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
//
// }
