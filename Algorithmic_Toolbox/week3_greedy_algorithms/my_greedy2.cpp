#include <iostream>
#include <cassert>
#include <random>
#include <sys/time.h>
#include <algorithm>
#include <vector>

using namespace std;
// using std::vector;
/*
find the most valuable combination of items assuming that any fraction of loot item can be put into the bag
*/

int check_max(double array[][3], int num) {
  double max = 0.0;
  int index = 0;
  for (int ii=0; ii < num; ii++) {
    if (array[ii][2] > max){
      max = array[ii][2];
      index = ii;
    }
  }
  return index;
}

// void sort(double array[][3], int index) {
//   int  i,j;
//   // int index = 0;
//   double temp;
//   sorted = false;
//
//   while (!sorted) {
//
//     for(i = 0; i < index - 1; i++) {
//
//       if(array[i][2] < array[i+1][2]){
//
//         for (j=0; j < 3; j++) {
//
//     	    temp = array[i][j];
//     	    array[i][j] = array[i+1][j];
//     	    array[i+1][j] = temp;
//   	     }
//   	  // cout  << array << endl;
//       }
//     }
//   }
// }

/*
Base solution, naive but works
*/

double base_solution(double capacity, vector<double> weights, vector<double> values) {
  double value = 0.0;
  double bag = 0.0;
  double array[weights.size()][3];
  for (int i=0; i<weights.size(); i++) {
    array[i][0] = values[i];
    array[i][1] = weights[i];
    array[i][2] =  values[i]/weights[i];
    // cout << array[i][0] << " " << array[i][1] << " " << array[i][2] << "\n";
  }


  while (bag < capacity) {
    // check max ratio
    int index = check_max(array, weights.size());
    // add the value to the value
    value += array[index][2];
    // remove 1 from weight and add 1 to bag
    array[index][1] -= 1;
    bag += 1;
    // if run out of object then delete row
    if (array[index][1] == 0) {
      array[index][2] = 0;
    }
  }
  return value;
}


/*
New, fast solution to test
*/
double test_solution(double capacity, vector<double> weights, vector<double> values) {
  double value = 0.0;
  double bag = 0.0;
  double array[weights.size()][3];
  for (int i=0; i<weights.size(); i++) {
    array[i][0] = values[i];
    array[i][1] = weights[i];
    array[i][2] =  values[i]/weights[i];
    // cout << array[i][0] << " " << array[i][1] << " " << array[i][2] << "\n";
  }
  // sort(array, weights.size());
  //
  // for (int i=0; i<weights.size(); i++) {
  //   cout << array[i][0] << " " << array[i][1] << " " << array[i][2] << "\n";
  //   // cout << array[i] << "\n";
  // }

  int index = check_max(array, weights.size());

  while (bag < capacity) {
    // check max ratio
    // int index = check_max(array, weights.size());
    // add the value to the value
    value += array[index][2];
    // remove 1 from weight and add 1 to bag
    array[index][1] -= 1;
    bag += 1;
    // if run out of object then delete row
    if (array[index][1] == 0) {
      array[index][2] = 0;
      index = check_max(array, weights.size());
    }
  }
  return value;
}

/*
Generator function for stress testing
*/
int generate(int max){
  int input = rand() % max + 1;
  return input;
}


/*
submission function
*/
int main() {

  int m;
  double capacity;
  cin >> m >> capacity;
  vector<double> values(m);
  vector<double> weights(m);

  for (int i = 0; i < m; i++) {
    cin >> values[i] >> weights [i];
  }
  // function call
  double value = test_solution(capacity, weights, values);

  cout.precision(12);
  cout << value << "\n";

}

/*
test functions
*/
// int main() {
//
//   int m;
//   double capacity;
//   cin >> m >> capacity;
//   vector<double> values(m);
//   vector<double> weights(m);
//
//   struct timespec start, end;
//
//
//   for (int i = 0; i < m; i++) {
//     values[i] = generate();
//     weights [i] = generate();
//   }
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   double value = base_solution(capacity, weights, values);
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
//
//   cout.precision(12);
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
//     double capacity;
//     m = generate(1000);
//     capacity = generate(2000000);
//     vector<double> values(m);
//     vector<double> weights(m);
//
//     for (int i = 0; i < m; i++) {
//       values[i] = generate(2000000);
//       weights[i] = generate(2000000);
//     }
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     double base_value = base_solution(capacity, weights, values);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     double test_value = test_solution(capacity, weights, values);
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     if (base_value != test_value) {
//       cout << "m: " << m << "  " << "Capacity: "<< capacity << "\n";
//       cout << "Base value: " << base_value << "  Test value: " << test_value << "\n";
//       break;
//     }
//
//     cout << "m: " << m << "  " << "Capacity: "<< capacity << "\n";
//     cout << "Base value: " << base_value << "  Test value: " << test_value << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
