class opt:
    link = 0
    clos = 1
    per = 2
    lb = 3
    rb = 4

    oplist = range(5)

    @staticmethod
    def c2o(c):
        return {'.': 0, '*': 1, '|': 2, '(': 3, ')': 4}[c]

    @staticmethod
    def o2c(o):
        return ['.', '*', '|', '(', ')'][o]


class aNodes:
    index = 0

    def __init__(self, k=None):
        self.next = []
        self.keys = []
        if k is None:
            self.begin = self
            self.end = self
            self.no = aNodes.index
            aNodes.index += 1
        else:
            self.begin = aNodes()
            self.end = aNodes()
            self.begin.next.append((self.end, k))
            self.next.append((self.begin, None))
            self.no = -1

    def append(self, n):
        self.end.next.append((n.begin, None))

    def __add__(self, n):
        self.append(n)
        self.end = n.end

        return self

    def __or__(self, n):
        nb = aNodes()

        for i in self.begin.next:
            nb.next.append(i)

        self.begin.next = [(nb, None), (n.begin, None)]

        ne = aNodes()
        self.append(ne)
        n.append(ne)

        self.end = ne

        return self

    def clos(self):
        self.append(self)
        self.begin.next.append((self.end, None))

        return self


beload = set()


def output_aNodes(n: aNodes, f, end, beg=True):
    global beload
    if beg:
        beload = set()

    beload.add(n.no)

    if not n.next:
        end.add(n.no)
    for tn, k in n.next:
        # print(f"from {n.no} to {tn.no} by {k}")
        f.append((n.no, tn.no, k))
        if tn.no not in beload:
            output_aNodes(tn, f, end, False)


def reg2NFA(reg_str):
    # 在正则表达式中填补连接运算符，并识别转义字符
    print(reg_str)
    reg = []
    tran_flg = False
    lastc = None
    for c in reg_str:
        if not tran_flg and c == '\\':
            tran_flg = True
            continue
        else:
            if not tran_flg and c in ('*', '|', '(', ')'):
                sig = opt.c2o(c)
            elif tran_flg and c == 'n':
                sig = '\\n'
            else:
                sig = c

            if lastc not in (None, opt.lb, opt.per) and sig not in (opt.clos, opt.rb, opt.per):
                reg.append(opt.link)
            reg.append(sig)

            lastc = sig
            tran_flg = False

    # print(reg)

    oper_hige = {opt.clos: 0, opt.per: 2, opt.link: 1, opt.rb: 10, opt.lb: 10}

    Astack = []
    Ostack = []

    for c in reg:
        # print([(i.begin.no, i.end.no) for i in Astack], [opt.o2c(tc) for tc in Ostack])

        if c not in opt.oplist:
            Astack.append(aNodes(c))
        else:
            # 处理opt栈
            while Ostack:
                if c == opt.lb:
                    break

                lc = Ostack[-1]
                if oper_hige[lc] < oper_hige[c] or c == opt.rb and lc != opt.lb:
                    # 处理运算
                    tc = Ostack.pop()

                    if tc == opt.clos:
                        Astack[-1].clos()

                    elif tc == opt.link:
                        n = Astack.pop()
                        Astack[-1] += n

                    elif tc == opt.per:
                        n = Astack.pop()
                        Astack[-1] |= n

                elif c == opt.rb and lc == opt.lb:
                    # 如果是括号出栈流程， 将左括号出栈后再停止出栈
                    Ostack.pop()
                    break
                elif oper_hige[lc] >= oper_hige[c]:
                    # 如果优先级不高于当前， 停止出栈
                    break

            if c != opt.rb:
                Ostack.append(c)

    while Ostack:
        # print([(i.begin.no, i.end.no) for i in Astack], [opt.o2c(tc) for tc in Ostack])
        tc = Ostack.pop()

        if tc == opt.clos:
            Astack[-1].clos()

        elif tc == opt.link:
            n = Astack.pop()
            Astack[-1] += n

        elif tc == opt.per:
            n = Astack.pop()
            Astack[-1] |= n

    Astack[0].append(aNodes())
    f = []
    end = set()
    output_aNodes(Astack[0], f, end)
    return f, {-1}, end


if __name__ == "__main__":
    a = reg2NFA("0*10*\\*1(1|2)*01|1")
    print(a)
