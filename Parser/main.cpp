#include <iostream>
#include <string>
#include <vector>

namespace angelica
{
	using namespace std;

	// ���ʷ��ŵ��ֱ�
	enum class SymbolType : int
	{
		KEYWORD_MAIN = 1,
		KEYWORD_INT, KEYWORD_CHAR, KEYWORD_IF, KEYWORD_ELSE,
		KEYWORD_FOR, KEYWORD_WHILE, KEYWORD_RETURN,
		KEYWORD_VOID,
		STRING = 50, ID = 10, INT = 20,
		EQUALS = 21,  // �Ⱥ�
		PLUS, SUBSTRACT, MINUS, DIVIDE,
		LS_PARENTHESIS, RS_PARENTHESIS, // ��С���ţ���С����
		LM_PARENTHESIS, RM_PARENTHESIS,
		LL_PARENTHESIS, RL_PARENTHESIS,
		COMMA, COLON, SEMICOLON,  // ���ţ�ð�ţ��ֺ�
		RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_EQ, RELOP_NEQ
	};

	// ���ʷ���
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


// �ӱ�׼�����ж�ȡԴ���룬��������ʷ���
int main()
{
	string input;
	{  // ��ȡ��׼���뵽input��ֱ������EOF
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
			string token(1, input[idx]);  // ��token��ʼ��Ϊinput[idx]
			
			if (isspace(token[0])) {
				continue;
			}

			if (isalpha(token[0])) {
				size_t cur = idx + 1;  // �������ĵ�һ���ַ����±�
				while (cur < input.length() && (isalpha(input[cur]) || isdigit(input[cur]))) {
					token += input[cur];
					cur += 1;
				}
				
				idx = cur - 1;
				vec.push_back(Symbol(SymbolType::ID, token));  // ����Ҫ�����Ƿ�Ϊ�ؼ���
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
				while (cur < input.length() && input[cur] != '"') {  // ������ת���ַ�
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
