class DFA:
    def __init__(self, f, begin, end):
        # 不是唯一起点，报错
        if len(begin) != 1:
            raise Exception(f"Unforeseeable starting points number: {len(begin)}")

        # 起点不是0， 将起点置换为0
        begin = begin.pop()
        if begin != 0:
            for i, (a, b, t) in enumerate(f):
                if a == 0 or a == begin or b == 0 or b == begin:
                    f[i] = (begin if a == 0 else 0 if a == begin else a,
                            begin if b == 0 else 0 if b == begin else b, t)
            if 0 in end:
                end = {i if i != 0 else begin for i in end}

        chars = {c: i for i, c in enumerate({t for _, _, t in f})}
        # states = set.union({a for a, _, _ in f}, {b for _, b, _ in f})

        f = [(a, b, chars[t]) for a, b, t in f]

        maxA = max([a for a, b, t in f] + [b for a, b, t in f]) + 1
        maxT = max([t for a, b, t in f]) + 1

        # print(maxA, maxT)

        maps = [[-1] * (maxT + 1) for _ in range(maxA)]
        for a, b, t in f:
            maps[a][t] = b

        if isinstance(end, list):
            for n, e in enumerate(end):
                print(n, e)
                for s in e:
                    maps[s] = [-n - 2 if i == -1 else i for i in maps[s]]

        self._chars = chars
        self._map = maps
        self._x = maxA + 1
        self._y = maxT + 1
        self.end = end
        self.tips = range(len(end) if isinstance(end, list) else 1)

    def __getitem__(self, item):
        t, c = item
        return self._map[t][self._chars[c]]

    def chars(self) -> set:
        return set(self._chars.keys())

    def __iter__(self):
        f = []
        bc = {v: k for k, v in self._chars.items()}
        for a, tl in enumerate(self._map):
            for tv, b in enumerate(tl):
                if tv != -1 and b >= 0 and (a, b, bc[tv]) not in f:
                    f.append((a, b, bc[tv]))

        for i in range(3):
            yield (f, {0}, self.end)[i]

    def __str__(self):
        return str(tuple(self))

    def inChars(self, c):
        return c in self._chars

    def state2Cpp(self, name="states"):
        ans = f"int {name}[{self._x}][{self._y + 1}] = "
        ans += "{ \n"
        for m in self._map:
            ans += "{"
            for i in m:
                ans += f"{i}, "
            ans += "},\n"

        ans += "};"

        return ans

    def chars2Cpp(self, name="chars"):
        ans = f"std::map<char, int> {name} = "
        ans += "{ \n"
        for k, v in self._chars.items():
            if k == '\\':
                k = '\\\\'
            ans += "{ \'%s\', %d }, \n" % (k, v)
        ans += "};"

        return ans

