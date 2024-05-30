from grammer.LRG import LRG

class LALR(LRG):
    def  __init__(self, f, ends, notends):
        super().__init__(f, ends, notends)

    # def table(self):
        