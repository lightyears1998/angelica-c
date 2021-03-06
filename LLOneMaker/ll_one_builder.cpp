// ll_one_builder.cpp
//
// LL(1)分析表生成器的实现。

#include "ll_one_builder.h"

namespace angelica {
	using namespace std;

	LLOneAnalyzer LLOneBuilder::BuildAnalyzer()
	{ 
		getInputFromParser();     // 读取词法分析器的输入
		diminishLeftRecursion();  // 消除左递归
		removeLookBack();         // 消除回溯
		
		printNonterminalSymbolSet();  // 打印非终结符集合
		printFirstSet();              // 打印First集合
		printFollowSet();             // 打印Follow集

		buildAnalyzer();  // 生成文法对应的分析器
		return analyzer_;
	}

	void LLOneBuilder::getInputFromParser()
	{
		vector<Symbol> line = parser_.ParseLineFromInputStream(); // 从Parser中获取第一行输入

		// 将第一条产生式的左部定义为文法的开始符号
		start_symbol_ = line[0];
		analyzer_.DefineStartSymbol(start_symbol_);

		for (line; line.size() != 0; line = parser_.ParseLineFromInputStream()) {
			// 程序假定来自Parser的输出符合LL(1)文法。
			// 对于每个生成式，第一个符号是终结符，第二个符号是分隔左部与右部的空格
			Symbol left = line[0];
			vector<Symbol> right(line.begin() + 2, line.end());

			nonterminal_set_.insert(left);

			// 程序仅考虑形如 A→Aα|β 和 A→α 两种形式的产生式
			if (line[2] == line[0]) {  // A→Aα|β 需要消除左递归的情况
				auto delim = find(right.begin(), right.end(), Symbol(SymbolType::STRUCTURE, "|"));  // 竖线的位置

				// 产生式形如 A→Aα|β， 需要将 A→Aα|β 改写为 A→βA', A'→αA'|ε

				// α和β
				vector<Symbol> alpha(right.begin() + 1, delim);
				vector<Symbol> beta(delim + 1, right.end());

				Symbol adapted{ SymbolType::NONTERMINAL, left.value + "'" };
				nonterminal_set_.insert(adapted);

				// βA'
				vector<Symbol> beta_adapted(beta);
				beta_adapted.push_back(adapted);

				// αA'|ε
				vector<Symbol> alpha_adapted_epsilon(alpha);
				alpha_adapted_epsilon.push_back(adapted);
				alpha_adapted_epsilon.push_back(Symbol(SymbolType::STRUCTURE, "|"));
				alpha_adapted_epsilon.push_back(SYMBOL_NULL);

				// A→βA', A'→αA'|ε
				left_to_right_[left] = beta_adapted;
				left_to_right_[adapted] = alpha_adapted_epsilon;
			}
			else {  // A→α 不需要消除左递归的情况
				left_to_right_[left] = right;
			}
		}
		cout << endl;
	}

	void LLOneBuilder::diminishLeftRecursion()
	{
		cout << "消除左递归后的文法：" << endl;

		// 算法的局限性：只能消除直接左递归，只能处理 A→Aα|β 和 A→α 两种形式的产生式
		for (auto it = left_to_right_.begin(); it != left_to_right_.end(); ++it) {
			cout << it->first;
			cout << "→";
			for (Symbol sym : it->second) {
				cout << sym;
			}
			cout << endl;
		}
		cout << endl;
	}

	void LLOneBuilder::removeLookBack()
	{
		// 程序不考虑回溯，因此这部分留空
	}

	void LLOneBuilder::printNonterminalSymbolSet()
	{
		cout << "文法的非终结符集合：";
		for (auto it = nonterminal_set_.begin(); it != nonterminal_set_.end(); ++it) {
			cout << it->value << " ";
		}
		cout << endl;
		cout << "其中，文法的开始符号为：" << start_symbol_ << endl << endl;
	}

	void LLOneBuilder::printFirstSet()
	{
		cout << "构造的First集合" << endl;
		for (Symbol left : nonterminal_set_) {
			cout << "First(" << left << ")\t= { ";
			for (Symbol elem : getPossibleFirstTerminalSymbol(left)) {
				cout << elem << " ";
			}
			cout << "}" << endl;
		}
		cout << endl;


	}

	void LLOneBuilder::printFollowSet()
	{
		cout << "构造的Follow集合：" << endl;
		for (Symbol sym : nonterminal_set_) {
			cout << "Follow(" << sym << ")\t= { ";

			auto next_set = getPossibleFollowTerminalSymbol(sym);
			for (Symbol sym : next_set) {
				cout << sym << " ";
			}
			cout << "}" << endl;
		}
		cout << endl;
	}

	void LLOneBuilder::buildAnalyzer()
	{
		// 根据产生式产生分析表
		for (auto it = nonterminal_set_.begin(); it != nonterminal_set_.end(); ++it) {
			Symbol left = *it;
			auto right = left_to_right_[left];

			// 程序仅考虑形如 A→Aα|β 和 A→α 两种形式的产生式
			// 对于形如 A→Aα|β 的产生式，要将右部按“|”分隔为A→Aα，A→β两个产生式进行处理
			for (size_t it = 0; it < right.size(); ++it) {
				vector<Symbol> current_right;  // 每个current_righht是一个不包含“|”的产生式
				while (it < right.size() && right[it].value != "|") {
					current_right.push_back(right[it++]);
				}

				set<Symbol> possible_terminal;
				if (current_right[0].type == SymbolType::NONTERMINAL) {
					// 若右部的第一个符号为非终结符，则考虑这个非终结符可能推导出的终结符
					// 特别的，若是这个非终结符可能推导出空终结符，则还需要考虑下一个终结符可能推导出的非终结符，以此类推
					// 这个分支本质上是求解First集合的一部分
					for (size_t it = 0; it < current_right.size(); ++it) {
						set<Symbol> inner_possible_terminal = getPossibleFirstTerminalSymbol(current_right[it]);
						possible_terminal.insert(inner_possible_terminal.begin(), inner_possible_terminal.end());

						if (inner_possible_terminal.count(SYMBOL_NULL) == 0) break;
					}

				}
				else if (current_right[0].type == SymbolType::TERMINAL && current_right[0] != SYMBOL_NULL) {
					// 若右部的第一个符号为终结符，则该产生式只可能推导出这个终结符
					possible_terminal.insert(current_right[0]);
				}
				else {  // current_right[0] == SYMBOL_NULL
					// 若右部是一个空终结符，则需要考虑其他产生式才能得到该产生式所可能推导出的终结符
					// 这个分支本质上是求Follow集
					possible_terminal = getPossibleFollowTerminalSymbol(left);
				}

				// 对此产生式，在分析表中进行标记
				for (Symbol terminal : possible_terminal) {
					analyzer_.DefineGrammarRule(make_pair(left, terminal), current_right);
				}
			}
		}

		// 打印产生的分析表
		analyzer_.PrintGrammarRulesTable();
	}

	set<Symbol> LLOneBuilder::getPossibleFirstTerminalSymbol(Symbol left)
	{
		set<Symbol> possible_terminal;

		auto right = left_to_right_[left];
		for (size_t it = 0; it < right.size(); ++it) {
			Symbol current = right[it];
			if (current.type == SymbolType::TERMINAL) {
				possible_terminal.insert(current);

				while (it < right.size() && right[it].value != "|") ++it;  // 跳至下一个“|”之后
			}
			else if (current.type == SymbolType::NONTERMINAL) {
				set<Symbol> inner_possible_terminal = getPossibleFirstTerminalSymbol(current);
				possible_terminal.insert(inner_possible_terminal.begin(), inner_possible_terminal.end());

				if (inner_possible_terminal.count(SYMBOL_NULL) == 0) {
					while (it < right.size() && right[it].value != "|") ++it;  // 跳至下一个“|”之后
				}
			}
		}
		return possible_terminal;
	}

	set<Symbol> LLOneBuilder::getPossibleFollowTerminalSymbol(Symbol left)
	{
		set<Symbol> possible_terminal;

		// 遍历所有的产生式
		for (auto it = nonterminal_set_.begin(); it != nonterminal_set_.end(); ++it) {
			Symbol current_left = *it;
			auto current_right = left_to_right_[current_left];

			// 遍历一条复杂产生式中所有的字符
			bool continueInNeed = false;  // 在一些情况下需要忽略循环中current_right[it] == left的判定而继续
			for (size_t it = 0; it < current_right.size(); ++it) {
				if (current_right[it] == left || continueInNeed) {
					continueInNeed = false;  // 重置标记

					if (it + 1 == current_right.size() || current_right[it + 1] == Symbol(SymbolType::STRUCTURE, "|")) { // 右边的一个字符是界
						if (current_left != left) {
							auto next_set_of_current_left = getPossibleFollowTerminalSymbol(current_left);
							possible_terminal.insert(next_set_of_current_left.begin(), next_set_of_current_left.end());
						}
					}
					else {  // 右边字符是终结符或非终结符
						Symbol next_symbol = current_right[it + 1];

						if (next_symbol.type == SymbolType::TERMINAL) {
							possible_terminal.insert(next_symbol);
						}
						else {  // next_symbol.type == SymbolType::NONTERMINAL
							auto first_set_of_next_symbol = getPossibleFirstTerminalSymbol(next_symbol);
							if (first_set_of_next_symbol.count(SYMBOL_NULL) != 0) {
								continueInNeed = true;
								first_set_of_next_symbol.erase(SYMBOL_NULL);
							}
							possible_terminal.insert(first_set_of_next_symbol.begin(), first_set_of_next_symbol.end());
						}
					}
				}
			}
		}

		if (left == start_symbol_) {
			possible_terminal.insert(SYMBOL_END);
		}
		return possible_terminal;
	}
}
