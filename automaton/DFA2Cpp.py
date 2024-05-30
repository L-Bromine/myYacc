from automaton.MergeDFA import DFA


def DFA2Cpp(dfa: DFA, name="Lexer"):
    filename = name
    name = name.upper()
    auto_h = f"""#pragma once
#include <map>
#include <vector>
#include <string>
struct Token
{"{"}
	int type = -1;
	std::string value;
	Token() = default;
	Token(int,const std::vector<char>&);
	Token(int);
{"}"};
class {name}
{"{"}
private:
	int nowState = 0;
    {dfa.chars2Cpp("chars")}
    {dfa.state2Cpp("states")}
    
	std::vector<char> nowstr;
	
private:
	int getCharId(char c);

public:
    {name}() = default;
	Token next(char c);
	int getState() const {"{"} return nowState; {"}"}
{"}"};

extern {name} {name.lower()};
    """

    auto_cpp = f"""#include "{filename}.h" \n"""
    auto_cpp += f"""{name} {name.lower()};\n"""
    auto_cpp += """
Token::Token(int type, const std::vector<char>& chs)
{
	this->type = type;
	this->value.insert(this->value.begin(), chs.begin(), chs.end());
}

Token::Token(int type){
    this->type = type;
}

int """ + name + """::getCharId(char c)
{
	if(this->chars.count(c) > 0)
		return this->chars[c];
	return this->chars.size();
}

Token """ + name + """::next(char c)
{
	Token token = Token();
	int nextState = this->states[this->nowState][this->getCharId(c)];
	if (nextState >= 0) {
		this->nowState = nextState;
		this->nowstr.push_back(c);
	}
	else if (nextState < -1) {
		token = Token(-nextState - 2, this->nowstr);
		this->nowstr.clear();
		this->nowState = this->states[0][this->getCharId(c)];
		if (nowState == -1) nowState = 0;
		else this->nowstr.push_back(c);
	}
	
	return token;
}

    """

    return auto_h, auto_cpp
