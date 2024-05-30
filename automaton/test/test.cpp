#include "Automaton.h" 
    
Token::Token(int type, const std::vector<char>& chs)
{
	this->type = type;
	this->value.insert(this->value.begin(), chs.begin(), chs.end());
}

int Automaton::getCharId(char c)
{
	if(this->chars.count(c) > 0)
		return this->chars[c];
	return this->chars.size();
}

Token Automaton::next(char c)
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
		this->nowstr.push_back(c);
	}
	else throw "Into Error State!";
	
	return token;
}

    