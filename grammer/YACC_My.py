from automaton import strs2cpp
from grammer.LRG import LRG


def files2cpp(filename, encoding="utf-8"):
    reg = []
    res = []
    ends = []
    with open(filename, encoding=encoding) as file:

        flg = False

        for l in file:
            if l == "\n":
                flg = True
                continue

            if not flg:
                l = l[:-1]
                ls = l.split(' ')
                ends.append(ls[0])
                reg.append(' '.join(ls[1:]))

            else:
                res.append(l)


    print(reg)
    print(res)
    print(ends)

    lrg = LRG.lines2grammar(res, ends)
    lrg.table()
    print("LRG分析表构建完毕")
    lrg.printTable()

    other_ends: list = list(lrg.ends.keys())[len(ends):]
    if other_ends:
        for end in other_ends:
            reg.append(end)

    print(reg)
    # 生成lexer的cpp文件
    # strs2cpp(reg, "Lexer")
    print("lexer生成完毕")
    # 生成paser的cpp文件
    lrg.toCpp("Parser")

    return lrg



