#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sys/time.h>
#include <csignal>
#include <stack>


using namespace std;
using std::vector;

/*
find errors in the correct order of brackets in an input string
*/

/*
Base solution, naive but works
*/


/*
New, fast solution to test
*/

// similar to init in python when you are initializing the constructor for a class
struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']') {
          return true;
        }
        if (type == '{' && c == '}') {
          return true;
        }
        if (type == '(' && c == ')') {
          return true;
        }
        return false;
    }

    char type;
    int position;
};



/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}

// void signalHandler( int signum ) {
//    cout << "Interrupt signal (" << signum << ") received.\n";
//    // cout << str1 << " " << str2;
//
//    // cleanup and close up stuff here
//    // terminate program
//
//    exit(signum);
// }
/*
submission function
*/

int main() {
    string text;
    getline(cin, text);

    // cout << text ;
    std::stack<Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            // push to stack
            opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            // if stack empty return false
            // top = pop from stack
            // if (top != char) return False

            if (opening_brackets_stack.empty()) {
              cout << position + 1;
              return 0;
            }
            Bracket top = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            // cout << "type: " << top.type << " position: " << top.position << "\n";
            // if (!opening_brackets_stack.Matchc(next)) {
            if (!top.Matchc(next)) {
              cout << position+1;
              return 0;
            }
        }
    }
    // Printing answer, write your code here
    if (opening_brackets_stack.empty()) {
      cout << "Success";
      return 0;
    } else {
      cout << opening_brackets_stack.top().position+1;
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
