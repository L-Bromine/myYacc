def getI(f, now: set):
    que = [i for i in now]
    I = now
    while que:
        st = que.pop(0)
        for a, b, t in f:
            if a == st and t is None and b not in I:
                que.append(b)
                I.add(b)
    return I


def getNext(f, now: set, c):
    out = set()
    for a, b, t in f:
        if a in now and t == c and b not in out:
            out.add(b)
    return getI(f, out)


def nfa2dfa(f, begin, end):
    chars = {t for _, _, t in f if t is not None}
    # print(chars)
    _b = [i for i in begin]
    begin = getI(f, begin)
    states = [begin]
    tranforms = []

    que = [begin]

    while que:
        st = que.pop(0)
        for c in chars:
            n = getNext(f, st, c)
            if n:
                # print(st, n, c)
                if n not in states:
                    que.append(n)
                    states.append(n)
                tranforms.append((states.index(st), states.index(n), c))

    return tranforms, \
           {i for i, s in enumerate(states) if set.intersection(s, _b)}, \
           {i for i, s in enumerate(states) if set.intersection(s, end)}


if __name__ == "__main__":

    f0 = [
        ("X", 1, None),
        (1, 1, "b"),
        (1, 1, "a"),
        (1, 2, None),
        (2, 3, "a"),
        (2, 4, "b"),
        (3, 5, "a"),
        (4, 5, "b"),
        (5, 6, None),
        (6, 6, "a"),
        (6, 6, "b"),
        (6, "Y", None)
    ]

    f1 = [
        (0, 1, 1),
        (1, 1, 0),
        (1, 1, 1),
        (1, 2, 1),
        (2, 3, 0),
        (3, 4, 1)
    ]

    f2 = [
        (0, 1, 1),
        (1, 2, 1),
        (2, 3, 0),
        (3, 4, 1),
        (4, 4, 0),
        (4, 5, None),
        (5, 1, None),
        (1, 6, 1),
        (6, 7, 0),
        (7, 8, 1),
        (8, 9, 0),
        (9, 6, None),
        (9, 10, 1),
        (10, 5, None),
        (5, 11, 0)
    ]

    f3 = [
        (0, 1, None),
        (1, 1, 0),
        (1, 2, 1),
        (2, 2, 0),
        (2, 3, 1),
        (3, 3, 0),
        (3, 4, 1),
        (4, 4, 0),
        (4, 5, None)
    ]

    f4 = [
        (0, 1, None),
        (1, 2, 0),
        (1, 3, 1),
        (2, 4, 0),
        (3, 4, 1),
        (4, 1, None),
        (4, 5, None),
        (5, 6, None),
        (6, 7, 1), (6, 8, 0),
        (7, 9, 0),
        (8, 9, 1),
        (9, 10, None),
        (10, 11, 0),
        (10, 12, 1),
        (11, 13, 0),
        (12, 13, 1),
        (13, 14, None),
        (13, 10, None),
        (14, 15, 1),
        (14, 16, 0),
        (15, 17, 0),
        (16, 17, 1),
        (17, 18, None),
        (18, 19, 1),
        (18, 20, 0),
        (19, 21, 1),
        (20, 21, 0),
        (21, 22, None),
        (22, 5, None),
        (22, "Y", None)
    ]

    f5 = [
        (0, 1, None),
        (1, 1, 1),
        (1, 1, 0),
        (1, 2, 0),
        (2, 3, 1),
        (3, 4, 0),
        (4, 4, 1),
        (4, 4, 0),
    ]

    f6 = [
        (0, 0, "a"),
        (0, 1, "a"),
        (0, 1, "b"),
        (1, 0, "a")
    ]

    begin = {0}
    end = {}

    t, s, e = nfa2dfa(f6, begin, {1})
    print(t, s, e)

    for a in t:
        print("%d %d %s" % a)
