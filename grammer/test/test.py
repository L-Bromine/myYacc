from grammer.LLG import LLG
from grammer.LRG import LRG

if __name__ == "__main__":
    # ends = ["a", "b", "c"]
    # notends = ["A", "B", "C"]

    # f = [
    #     ("A", ["a", "B", "C", "A"]),
    #     ("A", ["C", "A"]),
    #     ("B", ["a", "C", "B"]),
    #     ("B", ["c"]),
    #     ("B", ["C", "b", "B"]),
    #     ("C", []),
    #     ("C", ["c", "C"]),
    #     ("C", ["c", "A", "c", "C"])
    # ]

    # ends = ["+", "i", "(", ")", "*"]
    # notends = ["E", "E'", "T", "T'", "F"]
    #
    # f = [
    #     ("E", ["T", "E'"]),
    #     ("E'", ["+", "T", "E'"]),
    #     ("E'", []),
    #     ("T", ["F", "T'"]),
    #     ("T'", ["*", "F", "T'"]),
    #     ("T'", []),
    #     ("F", ["(", "E", ")"]),
    #     ("F", ["i"]),
    #
    # ]

    # ends = ["a", "b"]
    # notends = ["S", "A", "B"]
    #
    # f = [
    #     ("S", ["A", "b", "c"]),
    #     ("A", ["a"]),
    #     ("A", []),
    #     ("B", ["b"]),
    #     ("B", [])
    # ]

    # f = [
    #     ("S", ["A", "b"]),
    #     ("A", ["a"]),
    #     ("A", ["B"]),
    #     ("A", []),
    #     ("B", ["b"]),
    #     ("B", []),
    # ]

    # a = LLG.getGrammar(f, ends, notends)
    # print(a)
    # f = [
    #     ("S", ["A", "b", "c"]),
    #     ("A", ["A", "a"]),
    #     ("A", ["A", "b"]),
    #     ("A", ["c"]),
    #     ("A", ["d"]),
    #     ("A", ["B"])
    # ]

    # ends = ["a", "b", "c", "d"]
    # notends = ["S", "A", "B", "C", "D", "E"]
    # f = [
    #     ("S", ["A", "b", "c"]),
    #     ("A", ["a", "b", "B"]),
    #     ("A", ["a", "b", "c"]),
    #     ("A", ["b", "c"]),
    #     ("A", ["B", "b"]),
    #     ("B", ["B", "a"]),
    #     ("B", ["C", "a"]),
    #     ("C", ["D"]),
    #     ("D", ["E"]),
    #     # ("E", ["A"]),
    # ]

    # llg = LLG.read("grammar1.gra")
    # print("源输入：", llg)
    # print("去除直接左递归与间接左递归后：", llg.removeLR())
    # print("合并同类前缀后：", llg.mergePrefix())
    # # print(llg.first())
    # # print(llg.follow())
    # print("是否为LL(1)文法", llg.isLL1())
    # # print(llg.table())
    # anastr = input("请输入待分析终结符序列，以空格分割\n").split(" ")
    # # print(llg.analysis(["a", "b", "c", "b", "c"]))
    # print(llg.analysis(anastr))

    lrg = LRG.read("grammar5.gra")
    # print("源输入：", lrg)
    lrg.printProgramGroup()
    lrg.printTable()
    # lrg.analysis("i = i * i".split(" "))
    # lrg.toCpp('Paser', 'Automaton')


    # print("去除直接左递归与间接左递归后：", llg.removeLR())
    # print("合并同类前缀后：", llg.mergePrefix())
    # # print(llg.first())
    # # print(llg.follow())
    # print("是否为LL(1)文法", llg.isLL1())
    # # print(llg.table())
    # anastr = input("请输入待分析终结符序列，以空格分割\n").split(" ")
    # # print(llg.analysis(["a", "b", "c", "b", "c"]))
    # print(llg.analysis(anastr))


