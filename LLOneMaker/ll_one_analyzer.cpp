// ll_one_analyzer.cpp
//
// LL(1)语法分析器class Analyzer的实现。


#include "ll_one_analyzer.h"

#include <set>
#include <stack>
#include <iostream>


namespace angelica
{
	using namespace std;


	LLOneAnalyzer::LLOneAnalyzer()
	{
		//// 定义文法开始符号
		//DefineStartSymbol("E");

		//// 录入分析表中的规则
		//DefineGrammarRule(make_pair("E", "i"), vector<Symbol>{"T", "E'"});
		//DefineGrammarRule(make_pair("E", "("), vector<Symbol>{"T", "E'"});
		//DefineGrammarRule(make_pair("E'", "+"), vector<Symbol>{"+", "T", "E'"});
		//DefineGrammarRule(make_pair("E'", ")"), vector<Symbol>{"ε"});
		//DefineGrammarRule(make_pair("E'", "#"), vector<Symbol>{"ε"});
		//DefineGrammarRule(make_pair("T", "i"), vector<Symbol>{"F", "T'"});
		//DefineGrammarRule(make_pair("T", "("), vector<Symbol>{"F", "T'"});
		//DefineGrammarRule(make_pair("T'", "+"), vector<Symbol>{"ε"});
		//DefineGrammarRule(make_pair("T'", "*"), vector<Symbol>{"*", "F", "T'"});
		//DefineGrammarRule(make_pair("T'", ")"), vector<Symbol>{"ε"});
		//DefineGrammarRule(make_pair("T'", "#"), vector<Symbol>{"ε"});
		//DefineGrammarRule(make_pair("F", "i"), vector<Symbol>{"i"});
		//DefineGrammarRule(make_pair("F", "("), vector<Symbol>{"(", "E", ")"});

		// 以表格形式打印定义的语法规则
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
		cout << "LL(1)分析表：" << endl;
		for (auto tbl_it = table_.begin(); tbl_it != table_.end(); ++tbl_it)  // "tbl" for "table", "it" for "iterator"
		{
			cout << "[" << tbl_it->first.first << " " << tbl_it->first.second << "] ";  // 输出行列
			cout << tbl_it->first.first << "→";
			for (auto sym_it = tbl_it->second.begin(); sym_it != tbl_it->second.end(); ++sym_it) {  // "sym" for "symbol"
				cout << *sym_it;
			}
			cout << endl;
		}
		cout << endl;
	}


	void LLOneAnalyzer::PrintGrammarRulesTable()
	{
		set<Symbol> terminal_symbol_set, non_terminal_symbol_set;  // 终结符集与非终结符集
		for (auto it = table_.begin(); it != table_.end(); ++it) {
			non_terminal_symbol_set.insert(it->first.first);  // 将行标（是一个非终结符）加入非终结符的集合中
			terminal_symbol_set.insert(it->first.second);     // 将列标（是一个终结符）加入终结符的集合中
		}
		
		cout << "LL(1)分析表：" << endl;
		
		// 输出一行终结符
		for (auto t_it = terminal_symbol_set.begin(); t_it != terminal_symbol_set.end(); ++t_it) {  // "t" for "terminal symbol"
			cout << "\t" << *t_it;
		}
		cout << endl;

		// 输出分析表中的行和列
		for (auto nt_it = non_terminal_symbol_set.begin(); nt_it != non_terminal_symbol_set.end(); ++nt_it) {  // "nt" for "non-terminal symbol"
			cout << *nt_it;
			for (auto t_it = terminal_symbol_set.begin(); t_it != terminal_symbol_set.end(); ++t_it) {
				cout << "\t";
				
				auto line_column_pair = make_pair(*nt_it, *t_it);
				if (table_.find(line_column_pair) != table_.end()) {  // 如果分析表中对应行列的规则不为空
					vector<Symbol> right_part(table_[line_column_pair]);
					cout << line_column_pair.first << "→";  // 输出左部
					for (auto sym_it = right_part.begin(); sym_it != right_part.end(); ++sym_it) {  // 输出右部
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
		stack<Symbol> symbol_stack;        // 符号栈
		unsigned next_symbol_index = 0;    // 句子中下一个待分析的符号的下标

		sequence.push_back(Symbol("#"));           // 在句子末尾附加结束标记
		symbol_stack.push(Symbol("#"));            // 压入结束标记
		symbol_stack.push(start_symbol_);  // 将开始符号入栈
		
		cout << "符号栈\t\t待分析的符号" << endl;
		while (!symbol_stack.empty())  // 当符号栈不为空
		{
			{  // 输出符号栈
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

			{  // 输出待分析的单词符号串
				for (unsigned i = next_symbol_index; i < sequence.size(); ++i) {
					cout << sequence[i];
				}
				cout << endl;
			}

			if (next_symbol_index == sequence.size()) { // 如果输入串分析完毕
				return false;  // 此时符号栈还没有分析完毕，说明输入串不是所给文法的句子
			}

			Symbol next_symbol = sequence[next_symbol_index];  // 下一个待分析的符号

			// 如果待分析的输入串中第一个字符与栈顶元素相同，那么弹出栈顶元素，并将字符吃进
			if (symbol_stack.top() == next_symbol) {
				symbol_stack.pop();
				++next_symbol_index;
				continue;
			}

			pair<Symbol, Symbol> line_column_pair = make_pair(symbol_stack.top(), next_symbol);  // 建立非终结符-终结符对
			if (table_.find(line_column_pair) != table_.end()) {  // 如果分析表中有对应当前非终结符-终结符对的规则
				vector<Symbol> symbols(table_[line_column_pair]);  // 取得推导规则中的右部
				symbol_stack.pop();  // 弹出符号栈栈顶元素
	
				if (symbols[0] == NULL_SYMBOL) {  // 如果右部为空字符
					continue;
				}
				else {
					for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
						symbol_stack.push(*it);  // 将右部反向压入栈中
					}
				}
			}
			else {
				return false;
			}
		}

		return next_symbol_index == sequence.size();  // 若符号栈为空且输出串的所有符号都已经分析，则输入串为文法的句子
	}
} 
