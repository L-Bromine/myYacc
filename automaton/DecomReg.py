def decomReg(reg_str):
    # 在正则表达式中填补连接运算符，并识别转义字符
    reg = []
    stack = []

    lastc = None
    for c in reg_str:
        if lastc != '\\' and c in ('[', ']', '&'):
            stack.append(c+"no")

        elif lastc == '\\' and c in ('[', ']', '&'):
            stack.pop()
            stack.append(c)
        else:
            stack.append(c)
        lastc = c

    print(stack)


if __name__ == "__main__":
    print(decomReg(r"a\&[b\cd\]]"))
