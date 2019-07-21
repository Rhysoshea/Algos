# python3
import sys
from random import randint
import time
'''
Return the greatest common divisor for two integers
'''

'''
insert base solution here
'''
def test_solution(a, b):
        current_gcd = 1
        for d in range(2, min(a, b) + 1):
            if a % d == 0 and b % d == 0:
                if d > current_gcd:
                    current_gcd = d

        return current_gcd


'''
code for comparing the base solution and a new solution
'''
def stress_test():
    while True:
        input = generate()
        a = input[0]
        b = input[1]

        base_start = time.time()
        base_solve = test_solution(a, b)
        base_end = time.time()

        new_start = time.time()
        new_solve = solution(a, b)
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
    # n = randint(2)
    n = 2
    input = [randint(1, 100) for i in range(n)]

    return input


'''
new solution to be tested
'''
def solution(a, b):
    if b == 0:
        return a
    a_prime = a % b
    # current_gcd = 1
    # for d in range(2, min(a, b) + 1):
    #     if a % d == 0 and b % d == 0:
    #         if d > current_gcd:
    #             current_gcd = d

    return solution(b, a_prime)


if __name__ == '__main__':

    ''' manual test '''
    # input = generate()
    # print (input)
    # a = input[0]
    # b = input[1]
    # # input = int(input())
    # start = time.time()
    # print (solution(a, b))
    # end = time.time()
    # print (end-start)

    '''stress test'''
    # stress_test()

    ''' submission '''
    # input = int(input())
    # input= [int(x) for x in input().split()]
    a, b = map(int, sys.stdin.read().split())
    print (solution(a, b))
