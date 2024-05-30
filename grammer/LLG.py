from grammer.Grammar import GrammarException, Grammar


class LLG(Grammar):

    def __init__(self, f, ends, notends):
        super().__init__(f, ends, notends)
        self.ll1_tab = None

    def removeLR(self):
        """
        消除左递归，包括直接左递归和间接左递归\n
        :警告！ 在有大量非终结符首符时时间复杂度可能过高
        """
        # 产生非终结符首符递推表
        table = {i: set() for i in range(len(self.notends))}
        for k, v in self.f.items():
            for ls in v:
                if not ls:
                    continue
                ef, no = ls[0]

                if not ef:
                    table[k].add(no)

        table = {i: list(v) for i, v in table.items()}

        # print("table:", table)

        def get1ring():
            """获取第一个搜索到的环"""
            # 遍历每个点，从每个点开始dfs
            for point in table:
                if not table[point]:
                    continue
                # 创建路径栈
                paths = [point]
                # 创建遍历栈
                stack = [0]

                while stack:
                    idx = stack[-1]
                    now_point = paths[-1]

                    # print("in find ring:", idx, now_point, table, stack, paths)
                    if not table[now_point]:
                        break

                    next_point = table[now_point][idx]

                    # 判断是否成环
                    if next_point in paths:
                        ci_begin = paths.index(next_point)
                        return paths[ci_begin:]

                    # 判断是否结束本次路径搜索
                    elif not table[next_point]:
                        stack[-1] += 1
                        while len(table[paths[-1]]) < stack[-1] + 1:
                            stack.pop()
                            paths.pop()
                            if stack:
                                stack[-1] += 1
                            else:
                                break
                    # 向下递归
                    else:
                        stack.append(0)
                        paths.append(next_point)

            return []

        # 开始分析直接左递归
        # waits = set()
        # for k, v in self.f.items():
        #     for ls in v:
        #         if not ls:
        #             continue
        #
        #         ef, no = ls[0]
        #         if not ef and no == k:
        #             # 如果第一个为非终结符自身，添加进待处理数组
        #             waits.add(no)

        # 处理待处理数组，对每个非终结符添加新的非终结符
        def removeDirectLeftR(k):
            """
            消除直接左递归\n
            没有错误校验，请确保给出的编号正确已防止语法结构被破坏\n
            :param 直接左递归的非终结符的编号
            """

            # A = Aa1 | Aa2 | b1 | b2
            # =>
            # A = b1A' | b2A'
            # A' = a1A' | a2A' | None
            idx = self._addNT(k, "'")

            a = []
            b = []

            for l in self.f[k]:
                if not l:
                    continue
                ef, no = l[0]
                if not ef and no == k:
                    a.append(l[1:])
                else:
                    b.append(l)

            # print(a, b)
            ol = []
            for bi in b:
                ol.append(bi + [(False, idx)])

            nl = []
            for ai in a:
                nl.append(ai + [(False, idx)])
            nl.append([])

            self.f[k] = ol
            self.f[idx] = nl

        ring = get1ring()
        while ring:
            # print("ring:", ring)
            # 找到传递链
            tl = [None for _ in ring]
            for i, ri in enumerate(ring):
                tl[i] = [l[0] if l else None for l in self.f[ri]] \
                    .index((False, ring[(i + 1) % len(ring)]))

            ots = [i for i, ls in enumerate(self.f[ring[0]]) if
                   not ls[0][0] and ls[0][1] == ring[1 if len(ring) > 1 else 0]]

            # 带入转化为直接左递归
            if len(ring) > 1:
                for i, ii in enumerate(tl[1:]):
                    for j in ots:
                        # print(self, end="\n-------\n")
                        self.f[ring[0]][j] = self.f[ring[i + 1]][ii] + self.f[ring[0]][j][1:]

            # 消除直接左递归
            removeDirectLeftR(ring[0])

            # 在table中删除环的开始边
            table[ring[0]].remove(ring[1] if len(ring) > 1 else ring[0])

            ring = get1ring()

        return self

    def mergePrefix(self):
        """合并相同前缀推导式"""
        # 遍历每个非终结符
        idx = 0
        while idx in self.f:
            v = self.f[idx]
            # 从第一个非终结符开始检查每个或关系的推导式
            sets = {True: {}, False: {}}

            for i, ls in enumerate(v):
                if ls:
                    ef, no = ls[0]
                    if no not in sets[ef]:
                        sets[ef][no] = set()
                    sets[ef][no].add(i)

            # 转化sets为列表
            sets = [list(s) for no, s in sets[True].items()] \
                   + [list(s) for no, s in sets[False].items()]
            # print(sets)

            for s in sets:
                # 如果是前缀唯一的，不计算
                if len(s) <= 1:
                    continue

                # 如果前缀不唯一，那么计算最长公共前缀
                max_long = 1
                for i in range(max([len(v[sii]) for sii in s])):
                    c = v[s[0]][i]
                    for j, n in enumerate(s):
                        if c != v[s[j]][i]:
                            break
                    else:
                        max_long = i + 1
                        continue
                    break

                maxl = v[s[0]][:max_long]
                beforels = [v[sii][max_long:] for sii in s]
                # print(f"{max_long} size maxl: {maxl}")

                # 添加一个非终结符，并修改当前非终结符
                ti = self._addNT(idx, "-")

                ol = [l for i, l in enumerate(self.f[idx]) if i not in s] + [maxl + [(False, ti)]]

                self.f[idx] = ol
                self.f[ti] = beforels

            idx += 1
        return self

    def isLL1(self) -> bool:
        for k, ls in self.f.items():
            for l in ls:
                if l:
                    ef, no = l[0]
                    if not ef and no == k:
                        return False

        for k, ls in self.f.items():
            for i, l1 in enumerate(ls):
                for j, l2 in enumerate(ls):
                    # print(k, i, j, l1, l2)
                    # print(self.first(l1), self.first(l2))
                    if i < j and set.intersection(self.first(l1), self.first(l2)):
                        return False

        for f1, f2 in zip(self.first().values(), self.follow().values()):
            # print(f1, f2)
            if None in f1 and set.intersection(f1, f2):
                return False

        return True

    def table(self):
        if self.ll1_tab is not None:
            return self.ll1_tab

        if not self.isLL1():
            return None

        tab = [[None for _ in self.ends] for _ in self.notends]

        for k, v in self.f.items():
            for ls in v:
                for a in self.first(ls):
                    if a is None:
                        for b in self.follow(k):
                            tab[k][b] = ls
                    else:
                        tab[k][a] = ls

        self.ll1_tab = tab
        return self.ll1_tab

    def _analysis(self, ls):
        if self.table() is None:
            raise GrammarException("Grammar isn't LL(1)!")

        ls = [self.ends[l] for l in ls if l] + [-1]

        stack = [(True, -1), (False, 0)]
        ans = [[(False, 0)]]
        runing_stack = [0]

        idx = 0
        while idx < len(ls):
            a = ls[idx]
            if not stack:
                raise GrammarException("Stack empty!")

            ef, X = stack[-1]
            # print(ef, X, a, idx, stack[-1])
            if ef:
                if X == -1:
                    if X == a:
                        break
                    else:
                        raise GrammarException("Failed analysing: the last word in analysing isn't #")
                elif X == a:
                    stack.pop()
                    runing_stack.pop()
                    idx += 1
                else:
                    raise GrammarException("Failed analysing: unexpected word in analysing: "
                                           + {v: k for k, v in self.ends.items()}[a])
            else:
                if self.ll1_tab[X][a] is not None:
                    stack.pop()
                    aidx = runing_stack.pop()

                    # 在这里在ans中构建分析过程(线性过程)
                    als = ans[-1]
                    als = als[:aidx] + self.ll1_tab[X][a] + als[aidx + 1:]
                    ans.append(als)

                    # 更新栈
                    runing_stack = [i if i < aidx else i + aidx for i in runing_stack] \
                                   + [i + aidx for i in list(range(len(self.ll1_tab[X][a])))][::-1]
                    stack += self.ll1_tab[X][a][::-1]

                    # print(stack, ans, runing_stack)
                else:
                    raise GrammarException("Failed analysing: stap into ERROR path.")

        def ANSNEXT(anself):
            for a in anself.ans:
                yield a

        ans = type('', (object,), {'ans': ans, '__str__': lambda anself: \
            " -> ".join([" ".join([self.i2e[no] if ef else self.i2k[no] for ef, no in ls]) for ls in anself.ans]),
                                   "__getitem__": lambda anself, i: anself.ans, "__iter__": lambda anself: anself,
                                   "__next__": ANSNEXT})()

        return ans
