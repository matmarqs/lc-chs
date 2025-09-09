from collections import namedtuple

Casino = namedtuple('Casino', ['l', 'r', 'real'])

def bsort(casinos):
    sorted_casinos = dict()
    for c in casinos:
        if c.real not in sorted_casinos:
            sorted_casinos[c.real] = c
        else:
            sorted_casinos[c.real] = min(sorted_casinos[c.real], c, key=lambda x: (x.real, x.l))
    return sorted_casinos

def acessível(m, c):
    return c.l <= m < c.real

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    casinos = (Casino(*map(int, input().split())) for _ in range(n))
    casinos = filter(lambda c: c.l != c.real, casinos)
    casinos = bsort(casinos)

    for _, c in sorted(casinos.items()):
        if acessível(k, c):
            k = c.real
            continue
    print(k)
