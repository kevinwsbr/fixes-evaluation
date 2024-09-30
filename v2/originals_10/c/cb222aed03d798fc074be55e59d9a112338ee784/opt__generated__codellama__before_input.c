
[PYTHON]
import sys
from collections import defaultdict

def solve(inp):
    adj = defaultdict(list)
    for i in range(len(inp)):
        for j in range(i+1, len(inp)):
            if inp[j][0] - inp[i][0] <= 3:
                adj[i].append(j)
    return len(adj)

if __name__ == "__main__":
    input = sys.stdin.read()
    n, m = map(int, input.split())
    inp = []
    for i in range(m):
        *line, = map(str, input().split())
        inp.append([float(i) for i in line])
    print(solve(inp))
[/PYTHON]
