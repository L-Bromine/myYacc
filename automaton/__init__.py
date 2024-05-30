from automaton.NFA2DFA import nfa2dfa
from automaton.SimplifyDFA import simplifyDFA
from automaton.Regular2NFA import reg2NFA
from automaton.MergeDFA import mergeDFA
from automaton.DFA2Cpp import DFA2Cpp
from automaton.Lex2Cpp import lex2cpp, strs2cpp

__all__ = ["nfa2dfa", "simplifyDFA", "reg2NFA", "mergeDFA", "DFA2Cpp", "lex2cpp", "strs2cpp"]

if __name__ == "__main__":

    # f0 = reg2NFA("(a|b)*(aa|bb)(a|b)*")
    f0 = reg2NFA("(1|2|3|4|5|6|7|8|9|0)*")

    # f0 = ([
    #           ("X", 1, None),
    #           (1, 1, "b"),
    #           (1, 1, "a"),
    #           (1, 2, None),
    #           (2, 3, "a"),
    #           (2, 4, "b"),
    #           (3, 5, "a"),
    #           (4, 5, "b"),
    #           (5, 6, None),
    #           (6, 6, "a"),
    #           (6, 6, "b"),
    #           (6, "Y", None)
    #       ],
    #       {"X"},
    #       {"Y"}
    # )

    print(f0)
    f0 = nfa2dfa(*f0)
    print(f0)
    # for a, b, t in f0[0]:
    #     print(a, b, t)

    f0 = simplifyDFA(*f0)
    print(f0)



    # f1 = reg2NFA("(a|b)(aa|bb)*(a|c)")
    f1 = reg2NFA("abe")

    print(f1)
    f1 = nfa2dfa(*f1)
    print(f1)
    f1 = simplifyDFA(*f1)
    print(f1)

    t = mergeDFA([f0, f1])
    print(t)

    t = DFA2Cpp(t)
    print(t[0], t[1])

