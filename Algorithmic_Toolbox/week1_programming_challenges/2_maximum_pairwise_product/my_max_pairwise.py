# python3
import sys
from random import randint
import time
'''
return maximum product
'''

'''
insert base solution here
'''
def test_solution(input):
    n = len(input)
    max_product = 0
    for first in range(n):
        for second in range(first + 1, n):
            max_product = max(max_product,
                              input[first] * input[second])
    return max_product

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
    n = randint(2, 9)
    input = [randint(0, 1000) for i in range(n)]
    # overwrite input
    # input = [1, 300, 10, 1]
    return input


'''
new solution to be tested
'''
def solution(input):

    first = max(input)
    del input[input.index(first)]
    second = max(input)

    return (first * second)


if __name__ == '__main__':

    ''' manual test '''
    # input = generate()
    # start = time.time()
    # print (solution(input_numbers))
    # end = time.time()
    # print (end-start)

    '''stress test'''
    # stress_test()

    ''' submission '''
    input_n = int(input())
    input_numbers = [int(x) for x in input().split()]
    # a, b = map(int, sys.stdin.read().split())
    # input_numbers = [a, b]
    print (solution(input_numbers))
