#include "Lexer.h" 
LEXER lexer;

Token::Token(int type, const std::vector<char>& chs)
{
	this->type = type;
	this->value.insert(this->value.begin(), chs.begin(), chs.end());
}

Token::Token(int type){
    this->type = type;
}

int LEXER::getCharId(char c)
{
	if(this->chars.count(c) > 0)
		return this->chars[c];
	return this->chars.size();
}

Token LEXER::next(char c)
{
	Token token = Token();
	int charId = this->getCharId(c);
	//printf("<%c:%d>", c, c);
	int nextState = this->states[this->nowState][charId];
	if (nextState >= 0) {
		this->nowState = nextState;
		this->nowstr.push_back(c);
	}
	else if (nextState < -1) {
		token = Token(-nextState - 2, this->nowstr);
		this->nowstr.clear();
		this->nowState = this->states[0][charId];
		if (nowState == -1) nowState = 0;
		else this->nowstr.push_back(c);
	}
	//else throw "Into Error State!";
	
	return token;
}

    