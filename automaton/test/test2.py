from automaton import *

with open("test3.lex") as file:
    f1 = reg2NFA(file.readline()[:-1])
    print(f1)
    f1 = nfa2dfa(*f1)
    f1 = simplifyDFA(*f1)
    print(f1)

    # f2 = reg2NFA(file.readline()[:-1])
    # print(f2)
    # f2 = nfa2dfa(*f2)
    # f2 = simplifyDFA(*f2)
    # print(f2)
    #
    # f = mergeDFA([f1, f2])
    # print(f)

    a = f1[0]
    for i1, i2, c in a:
        print(f"{i1} {i2} {c}")

    # print('------------------------')
    # a = tuple(f)[0]
    # for i1, i2, c in a:
    #     print(f"{i1} {i2} {c}")
