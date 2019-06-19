// ll_one_analyzer.cpp
//
// LL(1)�﷨������class Analyzer��ʵ�֡�


#include "ll_one_analyzer.h"

#include <set>
#include <stack>
#include <iostream>


namespace angelica
{
	using namespace std;


	LLOneAnalyzer::LLOneAnalyzer()
	{
		//// �����ķ���ʼ����
		//DefineStartSymbol("E");

		//// ¼��������еĹ���
		//DefineGrammarRule(make_pair("E", "i"), vector<Symbol>{"T", "E'"});
		//DefineGrammarRule(make_pair("E", "("), vector<Symbol>{"T", "E'"});
		//DefineGrammarRule(make_pair("E'", "+"), vector<Symbol>{"+", "T", "E'"});
		//DefineGrammarRule(make_pair("E'", ")"), vector<Symbol>{"��"});
		//DefineGrammarRule(make_pair("E'", "#"), vector<Symbol>{"��"});
		//DefineGrammarRule(make_pair("T", "i"), vector<Symbol>{"F", "T'"});
		//DefineGrammarRule(make_pair("T", "("), vector<Symbol>{"F", "T'"});
		//DefineGrammarRule(make_pair("T'", "+"), vector<Symbol>{"��"});
		//DefineGrammarRule(make_pair("T'", "*"), vector<Symbol>{"*", "F", "T'"});
		//DefineGrammarRule(make_pair("T'", ")"), vector<Symbol>{"��"});
		//DefineGrammarRule(make_pair("T'", "#"), vector<Symbol>{"��"});
		//DefineGrammarRule(make_pair("F", "i"), vector<Symbol>{"i"});
		//DefineGrammarRule(make_pair("F", "("), vector<Symbol>{"(", "E", ")"});

		// �Ա����ʽ��ӡ������﷨����
		PrintGrammarRulesTable();
	}


	void LLOneAnalyzer::DefineStartSymbol(Symbol symbol)
	{
		start_symbol_ = symbol;
	}


	void LLOneAnalyzer::DefineGrammarRule(pair<Symbol, Symbol> line_column_pair, vector<Symbol> right_part)
	{
		table_[line_column_pair] = right_part;
	}


	void LLOneAnalyzer::PrintGrammarRules()
	{
		cout << "LL(1)������" << endl;
		for (auto tbl_it = table_.begin(); tbl_it != table_.end(); ++tbl_it)  // "tbl" for "table", "it" for "iterator"
		{
			cout << "[" << tbl_it->first.first << " " << tbl_it->first.second << "] ";  // �������
			cout << tbl_it->first.first << "��";
			for (auto sym_it = tbl_it->second.begin(); sym_it != tbl_it->second.end(); ++sym_it) {  // "sym" for "symbol"
				cout << *sym_it;
			}
			cout << endl;
		}
		cout << endl;
	}


	void LLOneAnalyzer::PrintGrammarRulesTable()
	{
		set<Symbol> terminal_symbol_set, non_terminal_symbol_set;  // �ս��������ս����
		for (auto it = table_.begin(); it != table_.end(); ++it) {
			non_terminal_symbol_set.insert(it->first.first);  // ���б꣨��һ�����ս����������ս���ļ�����
			terminal_symbol_set.insert(it->first.second);     // ���б꣨��һ���ս���������ս���ļ�����
		}
		
		cout << "LL(1)������" << endl;
		
		// ���һ���ս��
		for (auto t_it = terminal_symbol_set.begin(); t_it != terminal_symbol_set.end(); ++t_it) {  // "t" for "terminal symbol"
			cout << "\t" << *t_it;
		}
		cout << endl;

		// ����������е��к���
		for (auto nt_it = non_terminal_symbol_set.begin(); nt_it != non_terminal_symbol_set.end(); ++nt_it) {  // "nt" for "non-terminal symbol"
			cout << *nt_it;
			for (auto t_it = terminal_symbol_set.begin(); t_it != terminal_symbol_set.end(); ++t_it) {
				cout << "\t";
				
				auto line_column_pair = make_pair(*nt_it, *t_it);
				if (table_.find(line_column_pair) != table_.end()) {  // ����������ж�Ӧ���еĹ���Ϊ��
					vector<Symbol> right_part(table_[line_column_pair]);
					cout << line_column_pair.first << "��";  // �����
					for (auto sym_it = right_part.begin(); sym_it != right_part.end(); ++sym_it) {  // ����Ҳ�
						cout << *sym_it;
					}
				}
			}
			cout << endl;
		}
		cout << endl;
	}


	bool LLOneAnalyzer::Judge(vector<Symbol> sequence)
	{
		stack<Symbol> symbol_stack;        // ����ջ
		unsigned next_symbol_index = 0;    // ��������һ���������ķ��ŵ��±�

		sequence.push_back(Symbol("#"));           // �ھ���ĩβ���ӽ������
		symbol_stack.push(Symbol("#"));            // ѹ��������
		symbol_stack.push(start_symbol_);  // ����ʼ������ջ
		
		cout << "����ջ\t\t�������ķ���" << endl;
		while (!symbol_stack.empty())  // ������ջ��Ϊ��
		{
			{  // �������ջ
				stack<Symbol> copy(symbol_stack);
				stack<Symbol> rev;
				while (!copy.empty()) {
					rev.push(copy.top()); copy.pop();
				}
				while (!rev.empty()) {
					cout << rev.top(); rev.pop();
				}
				cout << "\t\t";
			}

			{  // ����������ĵ��ʷ��Ŵ�
				for (unsigned i = next_symbol_index; i < sequence.size(); ++i) {
					cout << sequence[i];
				}
				cout << endl;
			}

			if (next_symbol_index == sequence.size()) { // ������봮�������
				return false;  // ��ʱ����ջ��û�з�����ϣ�˵�����봮���������ķ��ľ���
			}

			Symbol next_symbol = sequence[next_symbol_index];  // ��һ���������ķ���

			// ��������������봮�е�һ���ַ���ջ��Ԫ����ͬ����ô����ջ��Ԫ�أ������ַ��Խ�
			if (symbol_stack.top() == next_symbol) {
				symbol_stack.pop();
				++next_symbol_index;
				continue;
			}

			pair<Symbol, Symbol> line_column_pair = make_pair(symbol_stack.top(), next_symbol);  // �������ս��-�ս����
			if (table_.find(line_column_pair) != table_.end()) {  // ������������ж�Ӧ��ǰ���ս��-�ս���ԵĹ���
				vector<Symbol> symbols(table_[line_column_pair]);  // ȡ���Ƶ������е��Ҳ�
				symbol_stack.pop();  // ��������ջջ��Ԫ��
	
				if (symbols[0] == NULL_SYMBOL) {  // ����Ҳ�Ϊ���ַ�
					continue;
				}
				else {
					for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
						symbol_stack.push(*it);  // ���Ҳ�����ѹ��ջ��
					}
				}
			}
			else {
				return false;
			}
		}

		return next_symbol_index == sequence.size();  // ������ջΪ��������������з��Ŷ��Ѿ������������봮Ϊ�ķ��ľ���
	}
} 
