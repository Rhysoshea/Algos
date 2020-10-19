# python3

import itertools

n, m = map(int, input().split())
edges = [ list(map(int, input().split())) for i in range(m) ]
# print (edges)
clauses = []
positions = range(1, n+1)
adj = [[] for _ in range(n)]
for i, j in edges:
    adj[i-1].append(j-1)
    adj[j-1].append(i-1)

# print (adj)


def var_number(i, j):
    return n*i + j

def exactly_One_Of(literals):
    clauses.append([l for l in literals])
    for pair in itertools.combinations(literals, 2):
        clauses.append([-l for l in pair])

for i in range(n):
    exactly_One_Of([var_number(i, j) for j in positions])

for j in positions:
    exactly_One_Of([var_number(i, j) for i in range(n)])

for j in positions[:-1]:
    # print (j)
    for i, nodes in enumerate(adj):
        # print (i, nodes)
        # print (-var_number(i, j))
        # print ([var_number(n, j+1) for n in nodes])
        # print ([-var_number(i, j)] + [var_number(n, j+1) for n in nodes])
        clauses.append([-var_number(i, j)] + [var_number(n, j+1) for n in nodes])

print(len(clauses), n*n)
for c in clauses:
    c.append(0)
    print(' '.join(map(str, c)))
