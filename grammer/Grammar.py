class GrammarException(Exception):
    def __init__(self, msg: str):
        self.args = (msg,)

    def __str__(self):
        return self.args[0]


class Grammar:

    def __init__(self, f, ends, notends):
        self.f, self.ends, self.notends = Grammar.getGrammar(f, ends, notends)
        self.fwn = None

        self._fir = None
        self._fol = None
        self.ll1_tab = None
        self.i2k = {v: k for k, v in self.notends.items()}
        self.i2e = {v: k for k, v in self.ends.items()}

    @staticmethod
    def getGrammar(f: list, ends: list, notends: list):
        # 终结符与非终结符有交集，报错
        if set.intersection(set(ends), set(notends)):
            raise Exception("Same word in Terminals and Non-terminals!")

        ends = {k: i for i, k in enumerate(ends)}
        notends = {k: i for i, k in enumerate(notends)}

        nf = {k: [] for k in notends.values()}

        for k, v in f:
            idx = notends[k]

            nft = []
            for s in v:
                # 如果为终结符
                if s in ends:
                    nft.append((True, ends[s]))

                # 如果为非终结符
                if s in notends:
                    nft.append((False, notends[s]))

            nf[idx].append(nft)

        return nf, ends, notends

    def _addNT(self, k, pix="'"):
        """根据源非终结符与后缀添加非终结符"""
        s = self.i2k[k] + pix
        self.notends[s] = len(self.notends)
        self.i2k[self.notends[s]] = s
        return self.notends[s]

    def _passNone(self):
        """传递空字"""
        done = set()  # 处理完的非终结符

        nfWithNone = {k: [l for l in v] for k, v in self.f.items()}
        for k, v in self.f.items():
            # 如果某非终结符能够直接推出空字,并且没有处理过
            if [] in v and k not in done:
                done.add(k)
                # 扫描所有推导式，如果出现该终结符，添加一个删掉了所有该终结符的推导式
                for k2, v2 in nfWithNone.items():
                    for ls in v2:
                        if (False, k) in ls:
                            l = [i for i in ls]
                            l.remove((False, k))
                            if l not in v2:
                                v2.append(l)
        self.fwn = nfWithNone
        return self.fwn

    def first(self, arg=None):
        """求每个终结符的first集合"""
        # 求解某个list的first
        if isinstance(arg, list):
            if not arg:
                return {None}
            ef, no = arg[0]
            if ef:
                return {no}
            else:
                return self.first()[no]

        # 求某个符号的first（二元组形式）
        elif isinstance(arg, tuple) and len(arg) == 2 \
                and isinstance(arg[0], bool) and isinstance(arg[1], int):
            ef, no = arg
            if ef:
                return {no}
            else:
                return self.first()[no]

        elif arg is None:
            # 求解所有非终结符的first
            # 之前求过了，直接返回
            if self._fir is not None:
                return self._fir
            self._passNone()

            fir = {k: set() for k in self.notends.values()}
            flg = True
            while flg:
                flg = False

                for k, v in self.fwn.items():
                    for ls in v:
                        # 如果是空字
                        if not ls:
                            if None not in fir[k]:
                                fir[k].add(None)
                                flg = True
                            continue

                        ef, idx = ls[0]
                        # print(ef, idx)
                        # 如果是终结符
                        if ef:
                            if idx not in fir[k]:
                                fir[k].add(idx)
                                flg = True

                        # 如果是非终结符
                        else:
                            for s in fir[idx]:
                                if s not in fir[k] and s is not None:
                                    fir[k].add(s)
                                    flg = True

                # print(fir)

            self._fir = fir
            return self._fir

    def follow(self, arg=None):
        """求每个非终结符的follow集合"""
        if isinstance(arg, int):
            if self._fol is None:
                self.follow()
            return self._fol[arg]

        elif arg is None:
            # 之前求过了，直接返回
            if self._fol is not None:
                return self._fol

            # 查询first，没有->求
            if self._fir is None:
                self.first()
            fir = self._fir
            fol = {k: set() for k in self.notends.values()}
            fol[0].add(-1)

            flg = True
            while flg:
                flg = False
                for k, v in self.fwn.items():
                    for ls in v:
                        for i, (ef, no) in enumerate(ls):
                            if not ef:
                                if i + 1 < len(ls):
                                    nef, nno = ls[i + 1]
                                    # 如果后继是终结符，直接加入
                                    if nef:
                                        if nno not in fol[no]:
                                            fol[no].add(nno)
                                            flg = True
                                            # print(f"{no}后继是终结符，直接加入{nno}到follow集合{fol[no]}")
                                    # 如果后继是非终结符，将后继的first集合并入follow集合
                                    else:
                                        if not fir[nno].issubset(fol[no]):
                                            fol[no] |= fir[nno]
                                            flg = True
                                            # print(f"{no}后继是非终结符，将后继 {nno} 的first集合 {fir[nno]} 并入follow集合{fol[no]}")
                                else:
                                    # 如果非终结符是最后一个，那么与推导式左端的非终结符合并follow集
                                    if no != k and not fol[k].issubset(fol[no]):
                                        fol[no] |= fol[k]
                                        # fol[k] |= fol[no]
                                        flg = True
                                        # print(f"{no}非终结符是最后一个，那么与推导式左端的非终结符{k}合并follow集{fol[k]}, {fol[no]}")
                # print(fol)

            for i in fol.values():
                if None in i:
                    i.remove(None)

            self._fol = fol
            return self._fol

    def __str__(self):
        ans = ""
        for k, v in self.f.items():
            ans += self.i2k[k] + " -> "
            flg1 = False
            for ls in v:
                if flg1:
                    ans += " | "
                flg1 = True
                ans += " ".join([self.i2e[no] if ef else self.i2k[no] for ef, no in ls]) if ls else "ε"
            ans += "\n"

        return ans

    def analysis(self, ls):
        try:
            ans = self._analysis(ls)
        except GrammarException as e:
            print(e)
            return str(e)
        else:
            return ans

    def key(self, t):
        ef, no = t
        if ef:
            return self.i2e[no]
        else:
            return self.i2k[no]

    def _analysis(self, ls):
        raise NotImplementedError('Please define a analysis method')

    @classmethod
    def read(cls, filename, ends: list = None, encoding="utf-8"):
        with open(filename, encoding=encoding) as file:
            return cls.lines2grammar(file, ends)

    @classmethod
    def lines2grammar(cls, lines, ends=None):
        noends = []
        allci = set()

        allrecs = []
        lastbegin = None
        for l in lines:
            if l[-1] == "\n":
                l = l[:-1]
            l = l.split(" ")

            if l[0] == "|":
                begin = lastbegin
            else:
                begin = l[0]
                lastbegin = begin

            recursions: list
            if l[1] == "->":
                recursions = l[2:]
            else:
                recursions = l[1:]

            # 以单一“|”为分割线分割递推式并且以空格分割推导式符号
            recursions = " ".join(recursions).split("|")
            recursions = [recursion.split(" ") for recursion in recursions]
            for recursion in recursions:
                while "" in recursion:
                    recursion.remove("")

            # print(recursions)
            # 删除全空递推式以防止干扰空字
            while [] in recursions:
                recursions.remove([])

            # 检测空字
            for i, re in enumerate(recursions):
                if re == ['ε'] or re == ['[]']:
                    recursions[i] = []

            # 将所有在推导式左端出现的符号作为非终结符
            if begin not in noends:
                noends.append(begin)
            allci.add(begin)
            for recursion in recursions:
                for s in recursion:
                    allci.add(s)

            # 添加到递推式数组中
            for re in recursions:
                allrecs.append((begin, re))

        if ends is None:
            ends = allci - set(noends)
        elif allci - set.union(set(ends), set(noends)):
            other_set = allci - set.union(set(ends), set(noends))
            ends += list(other_set)
            # raise GrammarException("Some unknowing terminator in recursions! Unknowing Signals: " +
            #                        ",".join(allci - set.union(set(ends), set(noends))))

        return cls(allrecs, ends, noends)
