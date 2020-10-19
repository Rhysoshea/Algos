#include <iostream>
#include <cassert>
#include <random>
/*
create a function that calculates the Fibonacci number
*/

/*
Base solution, naive but works
*/
int base_solution(int n) {
    if (n <= 1)
        return n;

    return base_solution(n - 1) + base_solution(n - 2);
}

/*
New, fast solution to test
*/
int test_solution(int n) {
    // write your code here

    return 0;
}

/*
Generator function for stress testing
*/
void generate(){
  int input = rand() % 10 + 1;
  return input
}


// void stress_test() {
//   while True {
//     n = generate()
//
//   }
//     assert(fibonacci_fast(3) == 2);
//     assert(fibonacci_fast(10) == 55);
//     for (int n = 0; n < 20; ++n)
//         assert(fibonacci_fast(n) == fibonacci_naive(n));
// }


/*
call functions
*/
int main() {
    // int n = 0;
    // std::cin >> n;
    while(True){
      std::cout << generate();

    }
    // std::cout << fibonacci_naive(n) << '\n';
    // // test_solution();
    // //std::cout << fibonacci_fast(n) << '\n';
    // return 0;
}
