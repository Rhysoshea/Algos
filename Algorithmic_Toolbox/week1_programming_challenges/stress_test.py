# python3

def base_solution(input):
    n = len(input)
    max_product = 0
    for first in range(n):
        for second in range(first + 1, n):
            max_product = max(max_product,
                              input[first] * input[second])
    return max_product

def new_solution(input):
    

    return ans

def generate():
    input = randint(1, 9)
    return input

def main():
    while True:
        input = generate()
        base_solve = base_solution(input)
        new_solve = new_solution(input)

        print (input)
        print ('Base: ', base_solve, 'New: ', new_solve)
        if base_solve != new_solve:
            break
        else:
            print 'Pass'



if __name__ == '__main__':
    main()
