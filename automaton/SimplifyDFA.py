def make_map_DAF(f: list) -> dict:
    maps = {a: [] for a, b, t in f}
    chars = {t for _, _, t in f}
    for a, b, t in f:
        maps[a].append((t, b))
        if b not in maps:
            maps[b] = []

    maps = {a: {t: None for t in chars} for a, m in maps.items()}
    for a, b, t in f:
        maps[a][t] = b
    return maps


def simplifyDFA(f: list, begin: set, end: set):
    chars = {t for _, _, t in f}
    states = set.union({t for t, _, _ in f}, {t for _, t, _ in f})
    que = [{i for i in states if i not in end}, end]
    sets = [{i for i in states if i not in end}, end]
    maps = make_map_DAF(f)

    # print(maps)
    # print(que)

    while que:
        s = que.pop(0)
        for c in chars:
            touch_sets = []
            key2sets = {}

            for a in s:
                b = maps[a][c]

                def addIn2set(k, a):
                    if k not in touch_sets:
                        touch_sets.append(k)
                    idx = touch_sets.index(k)
                    if idx not in key2sets:
                        key2sets[idx] = []
                    key2sets[idx].append(a)

                if b is None:
                    addIn2set(None, a)
                else:
                    for ts in sets:
                        if b in ts:
                            addIn2set(ts, a)

            # print(s, touch_sets, c, key2sets)
            # print(que, sets)

            # print("sets:", sets, "update from set", s, " by char:", c)

            if len(touch_sets) > 1:
                if s in sets: sets.remove(s)
                for l in key2sets.values():
                    que.append(set(l))
                    sets.append(set(l))
                break

    set2map = {}
    for i, s in enumerate(sets):
        for sta in s:
            set2map[sta] = i

    nf = {}
    for a, b, t in f:
        nf[(set2map[a], t)] = set2map[b]

    nf = [(a, b, t) for (a, t), b in nf.items()]

    # 获取结束位置
    nend = set()
    for i in end:
        for s in sets:
            if i in s and s not in nend:
                nend.add(sets.index(s))

    return nf, {i for i, s in enumerate(sets) if set.intersection(s, begin)}, nend


if __name__ == "__main__":
    a1 = [(0, 1, 0), (0, 2, 1), (1, 1, 0), (1, 3, 1), (2, 1, 0), (2, 2, 1), (3, 4, 0), (3, 2, 1), (4, 4, 0), (4, 5, 1),
          (5, 4, 0), (5, 6, 1), (6, 4, 0), (6, 6, 1)], {0}, {0, 1}

    a2 = [
             (0, 2, "b"),
             (0, 1, "a"),
             (1, 1, "a"),
             (1, 4, "b"),
             (2, 3, "b"),
             (2, 1, "a"),
             (3, 2, "b"),
             (3, 3, "a"),
             (4, 5, "b"),
             (4, 0, "a"),
             (5, 4, "b"),
             (5, 5, "a")
         ], \
        {0}, {1, 0}

    print(simplifyDFA(*a2))
