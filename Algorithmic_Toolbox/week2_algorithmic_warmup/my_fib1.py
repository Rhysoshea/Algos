# python3
import sys
from random import randint
import time
'''
Quickly calculate the a Fibonnaci sequence
'''
'''
insert base solution here
'''
def test_solution(n):
        if (n <= 1):
            return n

        return test_solution(n - 1) + test_solution(n - 2)


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
    n = randint(2, 15)

    return n


'''
new solution to be tested
'''
def solution(input):
    if input <= 1:
        return input
    cache = [0 for _ in range(input)]
    cache[0] = 1
    for i in range(1,len(cache)):
        cache[i] = cache[i-1] + cache[i-2]


    return cache[-1]


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
