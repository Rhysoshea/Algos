# python3
import sys
from random import randint

def sum_digits(first, second):
    return first + second

def generate():
    return randint(1, 9)

if __name__ == '__main__':
    # a, b = map(int, sys.stdin.read().split())
    while True:
        print(sum_digits(generate(), generate()))
