# python3
import sys
from random import randint
import time
'''
Find the last digit of the sum of square of Fibonacci Numbers
'''
'''
insert base solution here
'''
def test_solution(n):
    if n <= 1:
        return n

    previous = 0
    current  = 1
    sum      = 1

    for _ in range(n - 1):
        previous, current = current, previous + current
        sum += current * current

    return sum %10


'''
code for comparing the base solution and a new solution
'''
def stress_test():
    while True:
        n = generate()

        base_start = time.time()
        base_solve = test_solution(n)
        base_end = time.time()

        new_start = time.time()
        new_solve = solution(n)
        new_end = time.time()

        print (n)
        print ('Base: ', base_solve, 'New: ', new_solve)
        print ('Base: ', base_end-base_start, 'New: ', new_end-new_start)
        if base_solve != new_solve:
            break
        else:
            print ('Pass')

'''
generator for input to both solutions
'''
def generate():
    n = randint(2, 1000)
    # input = [randint(0, 1000) for i in range(n)]
    # overwrite input
    # input = [1, 300, 10, 1]
    return n


def fib(n):
    if n <= 1:
        return n

    previous = 0
    current  = 1

    for _ in range(n - 1):
        previous, current = current, previous + current
    return (current)

'''
new solution to be tested
'''
def solution(n):
    # F0^2+F1^2+.....+Fn^2 = Fn * F(n+1)
    pp = 60
    fib1 = fib(n%pp)
    fib2 = fib((n+1)%pp)

    return (fib1*fib2) % 10


# def solution(n):
#     pp = 60
#
#     sum_m = fib((m%pp)+1)-1
#     sum_n = fib((n%pp)+2)-1
#
#     return (sum_n - sum_m)%10


if __name__ == '__main__':

    ''' manual test '''
    # input = generate()
    # # print (input)
    # input = int(input())
    # start = time.time()
    # print (solution(input))
    # end = time.time()
    # print (end-start)

    '''stress test'''
    # stress_test()

    ''' submission '''
    # a, b = map(int, sys.stdin.read().split())
    a = int(input())
    print (solution(a))
