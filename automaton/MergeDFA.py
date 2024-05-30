from automaton.DFA import DFA


def mergeDFA(fs: list):
    fs = [DFA(*e) for e in fs]

    chars = set()
    for a in fs:
        chars |= a.chars()

    f = []
    states = []
    stack = []
    nowState = [0] * len(fs)

    states.append(nowState)
    stack.append(nowState)

    while stack:
        nowState = stack.pop()
        for t in chars:
            bl = [-1] * len(fs)
            for i, am in enumerate(fs):
                if am.inChars(t) and nowState[i] >= 0:
                    bl[i] = am[nowState[i], t]
            if max(bl) >= 0:
                if bl not in states:
                    states.append(bl)
                    stack.append(bl)

                f.append((states.index(nowState), states.index(bl), t))
                print(f[-1])

    ends = []
    for i, a in enumerate(fs):
        s = set()
        for j, l in enumerate(states):
            if l[i] in a.end:
                s.add(j)
        ends.append(s)

    mergeTree = DFA(f, {0}, ends)

    return mergeTree
