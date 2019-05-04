#include <iostream>
#include <string>
#include <vector>

namespace angelica
{
	using namespace std;

	// 单词符号的种别
	enum class SymbolType : int
	{
		KEYWORD_MAIN = 1,
		KEYWORD_INT, KEYWORD_CHAR, KEYWORD_IF, KEYWORD_ELSE,
		KEYWORD_FOR, KEYWORD_WHILE, KEYWORD_RETURN,
		KEYWORD_VOID,
		STRING = 50, ID = 10, INT = 20,
		EQUALS = 21,  // 等号
		PLUS, SUBSTRACT, MINUS, DIVIDE,
		LS_PARENTHESIS, RS_PARENTHESIS, // 左小括号，右小括号
		LM_PARENTHESIS, RM_PARENTHESIS,
		LL_PARENTHESIS, RL_PARENTHESIS,
		COMMA, COLON, SEMICOLON,  // 逗号，冒号，分号
		RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_EQ, RELOP_NEQ
	};

	// 单词符号
	class Symbol
	{
	public:
		Symbol(SymbolType type) {
			type_ = type;
		};

		Symbol(SymbolType type, string value) {
			type_ = type;
			value_ = value;
		}

		string ToString()
		{
			if (type_ == SymbolType::STRING) {
				return string("(STRING, ") + value_ + string(")");
			}

			if (type_ == SymbolType::ID) {
				return string("(ID, ") + value_ + string(")");
			}

			if (type_ == SymbolType::INT) {
				return string("(INT, ") + value_ + string(")");
			}

			return string("(") + to_string(int(type_)) + string(", None)");
		}

	private:
		SymbolType type_;
		string value_;
	};
}

using namespace std;
using namespace angelica;


// 从标准输入中读取源代码，并输出单词符号
int main()
{
	string input;
	{  // 读取标准输入到input，直到遇到EOF
		string line;
		while (getline(cin, line)) {
			input += line;
			input += '\n';
		}
	}

	vector<Symbol> vec;
	{
		for (size_t idx = 0; idx < input.length(); ++idx)
		{
			string token(1, input[idx]);  // 将token初始化为input[idx]
			
			if (isspace(token[0])) {
				continue;
			}

			if (isalpha(token[0])) {
				size_t cur = idx + 1;  // 待分析的第一个字符的下标
				while (cur < input.length() && (isalpha(input[cur]) || isdigit(input[cur]))) {
					token += input[cur];
					cur += 1;
				}
				
				idx = cur - 1;
				vec.push_back(Symbol(SymbolType::ID, token));  // 还需要考虑是否为关键字
				continue;
			}

			if (isdigit(token[0])) {
				size_t cur = idx + 1;
				while (cur < input.length() && isdigit(input[cur])) {
					token += input[cur];
					cur += 1;
				}

				idx = cur - 1;
				vec.push_back(Symbol(SymbolType::INT, token));
				continue;
			}

			if (token[0] == '"') {
				token = "";
				size_t cur = idx + 1;
				while (cur < input.length() && input[cur] != '"') {  // 不考虑转义字符
					token += input[cur];
					cur += 1;
				}

				idx = cur;
				vec.push_back(Symbol(SymbolType::STRING, token));
				continue;
			}
		}
	}

	for (size_t idx = 0; idx < vec.size(); ++idx) {
		cout << vec[idx].ToString();
	}
}
