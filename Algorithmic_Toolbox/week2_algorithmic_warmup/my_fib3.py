# python3
import sys
from random import randint
import time
'''
Use the Pisano period to calculate Fn mod m i.e. the remainder of a Fibonacci number divided by m
'''
'''
insert base solution here
'''
def test_solution(n, m):
    if n <= 1:
        return n

    previous = 0
    current  = 1

    for _ in range(n - 1):
        previous, current = current, previous + current

    return current % m


'''
code for comparing the base solution and a new solution
'''
def stress_test():
    while True:
        n, m = generate()

        base_start = time.time()
        base_solve = test_solution(n, m)
        base_end = time.time()

        new_start = time.time()
        new_solve = solution(n, m)
        new_end = time.time()

        print (n, m)
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
    n = randint(1, 100000)
    m = randint(2, 100)
    # input = [randint(0, 1000) for i in range(n)]
    # overwrite input
    # input = [1, 300, 10, 1]
    return n, m


def pisano_period(m):
    for i in range(2, m*m):
        # print (i)
        # print (fib(i)%m )
        # print ( fib(i+1)%m )
        if fib(i)%m == 0 and fib(i+1)%m == 1:
            return i

def fib(n):
    if n <= 1:
        return n

    previous = 0
    current  = 1

    for _ in range(n - 1):
        previous, current = current, previous + current

    return current

'''
new solution to be tested
'''
def solution(n, m):
    pp = pisano_period(m)
    # print (pp)
    remainder = n % pp

    # first, second = 0, 1
    # res = remainder
    #
    # for i in range(remainder):
    #     res = (first + second) % m
    #     first = second
    #     second = res

    return (fib(remainder) % m)


if __name__ == '__main__':

    ''' manual test '''
    # a, b = map(int, sys.stdin.read().split())
    #
    # start = time.time()
    # print (solution(a,b))
    # end = time.time()
    # print (end-start)

    '''stress test'''
    # stress_test()

    ''' submission '''
    # input = int(input())
    a, b = map(int, sys.stdin.read().split())

    # print (pisano_period(b))
    print (solution(a, b))
