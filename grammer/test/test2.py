from grammer.YACC_My import files2cpp

if __name__ == '__main__':
    lrg = files2cpp("gra2.yac")
    lrg.analysis("INTTK IDENFR COMMA IDENFR COMMA IDENFR SEMICN "
                 "INTTK MAINTK LPARENT RPARENT LBRACE IDENFR ASSIGN IDENFR PLUS IDENFR SEMICN RBRACE"
                 .split(" "))
