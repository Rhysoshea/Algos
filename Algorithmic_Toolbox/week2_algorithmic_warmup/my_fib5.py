# python3
import sys
from random import randint
import time
'''
Find the last digit of a partial sum of Fibonacci numbers
'''
'''
insert base solution here
'''
def test_solution(n, m):
    sum = 0

    current = 0
    next  = 1

    for i in range(m + 1):
        if i >= n:
            sum += current

        current, next = next, current + next

    return sum%10


'''
code for comparing the base solution and a new solution
'''
def stress_test():
    while True:
        m = generate()
        n = generate(i=m)


        base_start = time.time()
        base_solve = test_solution(m,n)
        base_end = time.time()

        new_start = time.time()
        new_solve = solution(m,n)
        new_end = time.time()

        print (m, n)
        print ('Base: ', base_solve, 'New: ', new_solve)
        print ('Base: ', base_end-base_start, 'New: ', new_end-new_start)
        if base_solve != new_solve:
            break
        else:
            print ('Pass')

'''
generator for input to both solutions
'''
def generate(i=0):
    n = randint(i, 100)
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
def solution(m, n):
    pp = 60

    sum_m = fib((m%pp)+1)-1
    sum_n = fib((n%pp)+2)-1

    return (sum_n - sum_m)%10


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
    a, b = map(int, sys.stdin.read().split())
    print (solution(a, b))
