# python2
import sys
from random import randint
import time
'''
Return the least common multiple of two integers
'''

'''
insert base solution here
'''
def test_solution(a, b):
    for l in range(1, a*b + 1):
        if l % a == 0 and l % b == 0:
            return l

    return a*b



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
# def solution(a, b):
#     minimum = min(a,b)
#     maximum = max(a,b)
#     for l in range(1, int((a*b)/2)):
#         print (l * maximum)
#         if (l*maximum) % minimum == 0:
#             return l*maximum
#
#     return a*b

def solution(a, b):
    divisor = gcd(a, b)

    return (a*b)/divisor


def gcd(a, b):
    if b == 0:
        return a
    a_prime = a % b

    return gcd(b, a_prime)

if __name__ == '__main__':

    ''' manual test '''
    # a, b = map(int, sys.stdin.read().split())
    #
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
    print (int(solution(a, b)))
