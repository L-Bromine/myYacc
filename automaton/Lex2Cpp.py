import os
from automaton import *


def lex2cpp(path, name=None):
    if name is None:
        name = os.path.split(path)[1]
        name = os.path.splitext(name)[0]

    with open(path, "r") as lexfile:
        fs = []

        line = lexfile.readline()
        while line:
            if line[-1] == '\n':
                line = line[:-1]

            f = reg2NFA(line)
            f = nfa2dfa(*f)
            f = simplifyDFA(*f)

            fs.append(f)

            line = lexfile.readline()

        ans = mergeDFA(fs)
        h, cpp = DFA2Cpp(ans, name)

        with open(name + ".h", "w") as hfile:
            hfile.write(h)

        with open(name + ".cpp", "w") as cppfile:
            cppfile.write(cpp)


def strs2cpp(strs, name):
    fs = []
    for s in strs:
        f = reg2NFA(s)
        f = nfa2dfa(*f)
        f = simplifyDFA(*f)

        fs.append(f)

    ans = mergeDFA(fs)
    h, cpp = DFA2Cpp(ans, name)

    with open(name + ".h", "w") as hfile:
        hfile.write(h)

    with open(name + ".cpp", "w") as cppfile:
        cppfile.write(cpp)
