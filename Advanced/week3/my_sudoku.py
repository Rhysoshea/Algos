# python3
import itertools
import os
#
# puzzle=[
#     "5***1***4",
#     "***2*6***",
#     "**8*9*6**",
#     "*4*****1*",
#     "7*1*8*4*6",
#     "*5*****3*",
#     "**6*4*1**",
#     "***5*2***",
#     "2***6***8"
# ]
#
# clauses = []
#
# digits = range(1,10)
#
# def varnum(i, j, k):
#     assert(i in digits and j in digits and k in digits)
#     return 100*i + 10*j +k
#
# def exactly_one_of(literals):
#     clauses.append([l for l in literals])
#     for pair in itertools.combinations(literals,2):
#         clauses.append([-l for l in pair])
#
# # cell [i,j] contains exactly one digit
# for (i,j) in itertools.product(digits, repeat=2):
#     exactly_one_of([varnum(i,j,k) for k in digits])
#
# # k appears exactly once in row i
# for (i,k) in itertools.product(digits, repeat=2):
#     exactly_one_of([varnum(i,j,k) for i in digits])
#
# # k appears exactly once in column j
# for (j,k) in itertools.product(digits, repeat=2):
#     exactly_one_of([varnum(i,j,k) for i in digits])
#
# # k appears exactly once in a 3x3 block
# for (i,j) in itertools.product([1,4,7], repeat=2):
#     for k in digits:
#         exactly_one_of([varnum(i + deltai, j + deltaj, k) for (deltai, deltaj) in itertools.product(range(3), repeat=2)])
#
# for (i,j) in itertools.product(digits, repeat=2):
#     if puzzle[i-1][j-1] != "*":
#         k = int(puzzle[i-1][j-1])
#         assert(k in digits)
#         clauses.append([varnum(i,j,k)])
#
#
#
# # This solution prints a simple satisfiable formula
# # and passes about half of the tests.
# # Change this function to solve the problem.
# def printEquisatisfiableSatFormula():
#     for c in clauses:
#         c.append(0)
#         print (" ".join(map(str, c))+"\n")
#
# printEquisatisfiableSatFormula()

l = 9

# map() can listify the list of strings individually
l.append(0)
test = ''.join(map(str, l))
print(test)
