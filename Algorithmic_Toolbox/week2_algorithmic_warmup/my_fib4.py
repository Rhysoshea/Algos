# python3

import sys
from random import randint
import time
'''
Find the last digit of a sum of Fibonacci numbers
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
        sum += current

    return sum % 10


'''
code for comparing the base solution and a new solution
'''
def stress_test():
    while True:
        input = generate()

        base_start = time.time()
        base_solve = test_solution(input)
        base_end = time.time()

        new_start = time.time()
        new_solve = solution(input)
        new_end = time.time()

        print (input)
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
    n = randint(2, 100)
    # input = [randint(0, 1000) for i in range(n)]
    # overwrite input
    # input = [1, 300, 10, 1]
    return n


'''
new solution to be tested
'''

def fib(n):
    if n <= 1:
        return n

    previous = 0
    current  = 1

    for _ in range(n - 1):
        previous, current = current, previous + current
    return (current)

def solution(n):

    # pisano period of 10 is 60
    pp = 60
    remainder = n % pp
    sum = fib(remainder+2)-1

    return (sum%10 )


if __name__ == '__main__':

    ''' manual test '''
    # input = generate()
    # print (input)
    # input = int(input())
    # start = time.time()
    # print (solution(input))
    # end = time.time()
    # print (end-start)

    '''stress test'''
    # stress_test()

    ''' submission '''
    input = int(input())
    print (solution(input))
