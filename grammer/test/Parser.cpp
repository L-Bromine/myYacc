#include "Parser.h"
        
PARSER parser;
        


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

std::vector<Node>& PARSER::analysis(std::vector<Token>& tokens){
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

std::vector<Node>& PARSER::str2tree(std::string str)
{
    std::vector<Token> tokens;

    std::string s = str + '\0';
    for (char c : s) {
        Token t = lexer.next(c);
        if (t.type != -1) {
            tokens.push_back(t);
        }
    }

    parser.analysis(tokens);
    return ans;
}
