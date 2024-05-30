from grammer.Grammar import GrammarException, Grammar

const_sign = {
    # _
    '+': 'add',
    '-': 'sub',
    '*': 'star',
    '/': 'slash',
    '.': 'dot',
    '|': 'or',
    '&': 'and',
    '^': 'caret',
    '#': 'hash',
    '@': 'at',
    '%': 'per',
    '$': 'dol',
    '\\': 'back_slash',
    '(': 'l_open',
    ')': 'r_open',
    '[': 'l_close',
    ']': 'r_close',
    '{': 'l_curly',
    '}': 'r_curly',
    '<': 'less',
    '>': 'great',
    '=': 'equal',
    '!': 'bang',
    '~': 'til',
    '?': 'que',
    ';': 'sem',
    ':': 'colon',
    ',': 'comma',
    '\'': 'single_quo',
    '"': 'double_quo',
}


class LRG(Grammar):

    def __init__(self, f, ends, notends):
        super().__init__(f, ends, notends)
        self.prods = None
        self.lps = None
        self.programs = None
        self.go = None

        self.action = None
        self.goto = None

        self.notends["S'"] = -1
        self.i2k[-1] = "S'"
        self.f[-1] = [[(False, 0)]]

        self.ends["#"] = -1
        self.i2e[-1] = "#"

    def _GetProgram(self) -> list:
        """获取项目规范族"""
        if self.programs is not None:
            return self.programs

        self.programs = []

        def closure(parm):
            """获取闭包"""
            stack = []
            c: list

            if isinstance(parm, tuple):
                pno, v, i = parm
                c = [parm]
                if i != -1 and not v[i][0]:
                    stack.append(v[i][1])

            elif isinstance(parm, list):
                c = parm
                for pa in parm:
                    pno, v, i = pa
                    if i != -1 and not v[i][0]:
                        stack.append(v[i][1])

            nset = set()

            while stack:
                n = stack.pop()
                nset.add(n)

                for ls in self.f[n]:
                    c.append((n, ls, 0))
                    ef, no = ls[0]
                    if not ef and no not in nset:
                        stack.append(no)

            return c

        def go(I, x):
            J = []
            for ls in I:
                k, v, i = ls
                if v[i] == x and i != -1:
                    J.append((k, v, i + 1 if i + 1 < len(v) else -1))

            return closure(J)

        self.go = []

        v = self.f[-1][0]
        self.programs.append(closure([(-1, v, 0)]))
        all_chars = [(False, i) for i in self.notends.values()] + [(True, i) for i in self.ends.values()]
        pidx = 0

        print(all_chars)

        while pidx < len(self.programs):
            for i, I in enumerate(self.programs):
                for x in all_chars:
                    J = go(I, x)
                    if J:
                        if J not in self.programs:
                            self.programs.append(J)
                        idx = self.programs.index(J)
                        self.go.append((i, idx, x))
                print(f"已经过{pidx}次循环，当前programs总长度{len(self.programs)}, 当前项目集{i}总长度{len(I)}")

            pidx += 1

        return self.programs

    def table(self):
        """生成LR分析表"""

        if self.action is not None and self.goto is not None:
            return {True: self.action, False: self.goto}

        self.action = {k: {i: (-1, 0) for i in list(self.ends.values()) + [-1]} for k, I in
                       enumerate(self._GetProgram())}

        self.goto = {k: {i: -1 for i in self.notends.values()} for k, I in enumerate(self._GetProgram())}

        self.prods = []

        # 遍历规约式项目族（状态）， 通过规则2、3构建表
        for k, I in enumerate(self._GetProgram()):
            for no, ls, i in I:
                if i == -1:
                    if no == -1:  # S' -> S · ,设action[k, #] = acc
                        self.action[k][-1] = (0, 0)  # -1: acc 0: 占位符
                    else:  # 标记actoin[k, a] a 为任何终结符 用产生式规约
                        r = (no, len(ls))
                        # print(self.i2k[no], [self.i2e[no] if ef else self.i2k[no] for ef, no in ls])

                        # 产生规约式表
                        if r in self.prods:
                            idx = self.prods.index(r)
                        else:
                            idx = len(self.prods)
                            self.prods.append(r)

                        # 将 2： 规约操作 idx： 所使用规约式在表中的位置
                        for a in list(self.ends.values()) + [-1]:
                            if a in self.follow(no):
                                self.action[k][a] = (2, idx)

        # 遍历go表（边）， 通过规则1，4构建表
        for frm, to, key in self.go:
            ef, no = key
            if ef:  # 如果是非终结符
                # print(f"from {frm} to {to} by {self.i2e[no]}")
                self.action[frm][no] = (1, to)  # 1: 移进操作 to：目标状态

            else:  # 如果是非终结符
                # print(f"from {frm} to {to} by {self.i2k[no]}")
                self.goto[frm][no] = to

        return {True: self.action, False: self.goto}

    def _analysis(self, ls):
        ls = [self.ends[l] for l in ls if l] + [-1]
        self.table()

        char_stack = []
        stats_stack = [0]
        now_char = ls.pop(0)

        while True:
            st = stats_stack[-1]
            no = now_char

            opt = self.action[st][no]

            optt, optno = opt
            if optt == -1:
                raise GrammarException(f"LRG into error state!form {st} by {self.i2e[no]}")
            elif optt == 0:
                print(f"进入状态{st}, 接受语法树")
                # 接受
                break

            elif optt == 1:
                print(f"将 {self.i2e[no]} 加入栈， 移进 {self.i2e[ls[0]]} 并进入状态 {optno}")
                # 移进
                stats_stack.append(optno)
                char_stack.append((True, now_char))
                now_char = ls.pop(0)
            elif optt == 2:
                # 规约
                key, count = self.prods[optno]

                print(
                    f"规约 {[self.i2e[no] if ef else self.i2k[no] for ef, no in char_stack[-count:]]} 到 {self.i2k[key]} "
                    f"并返回状态 {stats_stack[-count - 1]}")

                char_stack = char_stack[:-count] + [(False, key)]  # 弹出栈顶并将规约后的非终结符加入栈
                stats_stack = stats_stack[:-count]  # 回退状态

                st = stats_stack[-1]
                st2 = self.goto[st][key]

                if st2 is None:
                    raise GrammarException(
                        f"LRG into error state!form {st} by {self.i2e[no]}")
                stats_stack.append(st2)

                # now_char = (False, key)
            #
            # else:
            #     opt = self.goto[st][no]
            #     print(f"goto {st}, {self.i2k[no]} 移进 {self.i2e[ls[0]]} 并进入状态 {opt}")
            #     if opt is None:
            #         raise GrammarException(
            #           f"LRG into error state!form {st} by {self.i2e[no] if ef else self.i2k[no]}")
            #
            #     stats_stack.append(opt)
            #     char_stack.append(now_char)
            #     now_char = (True, ls.pop(0))
            #
            #     print(stats_stack)

    def printProgramGroup(self):
        print("项目规范族：")
        pg = self._GetProgram()
        for idx, p in enumerate(pg):
            print("I", idx, ": ")
            for k, l, i in p:
                lst = [self.key(t) for t in l]
                if i != -1:
                    lst.insert(i, '·')
                else:
                    lst.append('·')
                s = self.key((False, k)) + " -> " + " ".join(lst)

                print(s)

    def printTable(self):
        print("分析表：")
        print(
            "|状态\t|" + "action\t" + "\t\t" * (len(self.ends) - 1) + "|" + "goto" + "\t" * (len(self.notends) - 1) + "|")
        print("|\t\t|" + "\t\t".join([k for k in self.ends]) + "\t\t|" + "\t".join([k for k in self.notends]) + "\t|")

        self.table()

        for k in self.action:
            va, vg = self.action[k], self.goto[k]
            la = []
            for i in self.ends.values():
                a = self.action[k][i]
                n, v = a
                if n == -1:
                    la.append("Er")
                elif n == 0:
                    la.append("acc")
                elif n == 1:
                    la.append(f"s{v}")
                elif n == 2:
                    la.append(f"r{v}")

            print(f"|{k}\t\t|" + "\t\t".join(la) + "\t\t|" +
                  "\t".join([str(i) if i != -1 else " " for i in vg.values()]) + "|")

    def toCpp(self, name, lexer="Lexer"):
        def action2cpp() -> str:
            s = f"const Action action[{len(self.action) + 1}][{len(self.action[0]) + 1}] = {'{'}"

            for k1, actions in self.action.items():
                s += "{"
                for k2, (ac, n) in actions.items():
                    s += f"{'{'}{ac}, {n}{'}'}, "
                s += "},\n"
            s += "};"

            return s

        def goto2cpp() -> str:
            s = f"const int gotos[{len(self.goto) + 1}][{len(self.goto[0]) + 1}] = {'{'}"

            for k1, gotos in self.goto.items():
                s += "{"
                for k2, n in gotos.items():
                    if k2 != -1:
                        s += f"{n}, "
                s += "},\n"
            s += "};"

            return s

        def prod2cpp() -> str:
            s = f"const Recursion prode[{len(self.prods) + 1}] = {'{'}"

            for k, c in self.prods:
                s += f"{'{'}{k}, {c}{'}'},"

            s += "};"
            return s

        def sign2cpp(signs, t) -> str:
            s = "class{\npublic:\nenum{\n"

            for k, i in signs.items():
                if i < 0:
                    continue
                ks: str = k
                for si, ts in const_sign.items():
                    ks = ks.replace(si, f"__{ts}__")
                s += f"{ks} = {i},\n"

            s += f"{'}'};\n{'}'}{t};\n"
            return s

        def strmap(name, t) -> str:
            s = f"const std::string {name}[{len(t) + 1}] = {'{'}\n"
            for i, k in enumerate(t):
                s += f'"{k}",\n'
            s += '\n};'

            return s

        filename = name
        name = name.upper()

        hstr = f"""#pragma once
#include <stack>
#include <vector>
#include "{lexer}.h"

struct Node {'{'}
	int no;
	bool flag;
	std::string content;
	std::vector<int> childs;
	Node(int n, const std::vector<int>& inp) :no(n), childs(inp), flag(false) {'{}'}
	Node(int n, std::string word) : no(n), childs(0), content(word), flag(true) {'{}'}
	Node(int n) :no(n), content(""), flag(true) {'{}'}
{'}'};

class {name}{'{'}
public:
    {sign2cpp(self.ends, "term")}
    {sign2cpp(self.notends, "nont")}
    class {'{'}
    public:
    {strmap("term", self.ends.keys())}
    {strmap("nont", self.notends.keys())}
    {'}'} signs;
    
    const int end_symbol = {len(self.action[0]) - 1};

private:
    struct Action{'{'}
        int ac, to;
    {'}'};
    struct Symbol{'{'}
        bool ef;
        int no;
    {'}'};
    struct Recursion{'{'}
        int key, count;
    {'}'};
    
private:
    int nowState = 0;

    std::stack<Symbol> chars_stack;
    std::stack<int> state_stack;
    std::stack<int> index_stack;

    std::vector<Node> ans;
        
    {prod2cpp()}
    {action2cpp()}
    {goto2cpp()}
    
private:
    std::vector<int> temp;
public:
    {name}() = default;
	Node next(const Token& now_token);
	std::vector<Node>& analysis(std::vector<Token>& tokens);
	std::vector<Node>& str2tree(std::string str);
    
{'}'};

extern {name} {name.lower()};
"""

        cppstr = f'#include "{filename}.h"' + f"""
        
{name} {name.lower()};
        
""" + """

Node PARSER::next(const Token& now_token) {

	int st = state_stack.top();
	int no = now_token.type;

	const Action& opt = action[st][no];

	int optt = opt.ac;
	int optno = opt.to;

	if (optt == -1) {
		throw "LRG into error state!";
	}
	else if (optt == 0) {
		return Node(-1);
	}
	else if (optt == 1) {
		state_stack.push(optno);
		chars_stack.push({ true, now_token.type });
		index_stack.push(ans.size());
		return Node(no, now_token.value);
	}
	else if (optt == 2) {
		int key = prode[optno].key;
		int count = prode[optno].count;

		for (int i = 0; i < count; ++i) {
			chars_stack.pop();
			state_stack.pop();
			temp.push_back(index_stack.top());
			index_stack.pop();
		}
		chars_stack.push({ false, key });

		int st2 = gotos[state_stack.top()][key];
		if (st2 == -1) {
			throw "LRG into error state!";
		}

		state_stack.push(st2);
		index_stack.push(ans.size());
		Node tempnode(key, temp);
		temp.clear();
		return tempnode;
		
	}
	else {
		throw "Unknowing action!";
	}   
}

std::vector<Node>& """ + name + """::analysis(std::vector<Token>& tokens){
    tokens.push_back(Token(end_symbol));
    
    state_stack.push(0);
    
    ans.clear();
    int idx = 0;
    
    while (true) {
        const Token& now_token = tokens[idx];
    
        int st = state_stack.top();
        int no = now_token.type;
    
        const Action& opt = action[st][no];
    
        int optt = opt.ac;
        int optno = opt.to;
    
        if (optt == -1) {
            throw "LRG into error state!";
        }
        else if (optt == 0) {
            return ans;
        }
        else if (optt == 1) {
            state_stack.push(optno);
            chars_stack.push({ true, now_token.type });
            index_stack.push(ans.size());
            ans.push_back(Node(no, now_token.value));
            ++idx;
        }
        else if (optt == 2) {
            int key = prode[optno].key;
            int count = prode[optno].count;
    
            for (int i = 0; i < count; ++i) {
                chars_stack.pop();
                state_stack.pop();
                temp.push_back(index_stack.top());
                index_stack.pop();
            }
            chars_stack.push({ false, key });
    
            int st2 = gotos[state_stack.top()][key];
            if (st2 == -1) {
                throw "LRG into error state!";
            }
    
            state_stack.push(st2);
            index_stack.push(ans.size());
            ans.push_back(Node(key, temp));
            temp.clear();
        }
    }
}

std::vector<Node>& """ + name + """::str2tree(std::string str)
{
    std::vector<Token> tokens;

    std::string s = str + '\\0';
    for (char c : s) {
        Token t = lexer.next(c);
        if (t.type != -1) {
            tokens.push_back(t);
        }
    }

    parser.analysis(tokens);
    return ans;
}
"""
        with open(name + ".h", "w") as hfile:
            hfile.write(hstr)

        with open(name + ".cpp", "w") as cppfile:
            cppfile.write(cppstr)
        return hstr, cppstr
