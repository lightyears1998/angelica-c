// ll_one_builder.cpp
//
// LL(1)��������������ʵ�֡�

#include "ll_one_builder.h"

#include <set>
#include <functional>

namespace angelica {
	using namespace std;

	LLOneAnalyzer LLOneBuilder::BuildAnalyzer()
	{
		LLOneAnalyzer analyzer;

		set<Symbol> nonterminal_set;                // �������з��ս���ļ���
		map<Symbol, vector<Symbol>> left_to_right;  // �󲿷��ս�����Ҳ����ŵ�ӳ��

		vector<Symbol> line = parser_.ParseLineFromInputStream(); // ��Parser�л�ȡ��һ������
													
		// ����һ������ʽ���󲿶���Ϊ�ķ��Ŀ�ʼ����
		Symbol start_symbol(line[0]);
		analyzer.DefineStartSymbol(start_symbol);

		for (line; line.size() != 0; line = parser_.ParseLineFromInputStream()) {
			// ����ٶ�����Parser���������LL(1)�ķ���
			// ����ÿ������ʽ����һ���������ս�����ڶ��������Ƿָ������Ҳ��Ŀո�
			Symbol left = line[0];
			vector<Symbol> right(line.begin() + 2, line.end());

			nonterminal_set.insert(left);

			// ������������� A��A��|�� �� A���� ������ʽ�Ĳ���ʽ
			if (line[2] == line[0]) {  // A��A��|�� ��Ҫ������ݹ�����
				auto delim = find(right.begin(), right.end(), Symbol(SymbolType::STRUCTURE, "|"));  // ���ߵ�λ��
				
				// ����ʽ���� A��A��|�£� ��Ҫ�� A��A��|�� ��дΪ A����A', A'����A'|��

				// ���ͦ�
				vector<Symbol> alpha(right.begin() + 1, delim); 
				vector<Symbol> beta(delim + 1, right.end());

				Symbol adapted{ SymbolType::NONTERMINAL, left.value + "'" };
				nonterminal_set.insert(adapted);

				// ��A'
				vector<Symbol> beta_adapted(beta); 
				beta_adapted.push_back(adapted);
				
				// ��A'|��
				vector<Symbol> alpha_adapted_epsilon(alpha); 
				alpha_adapted_epsilon.push_back(adapted);
				alpha_adapted_epsilon.push_back(Symbol(SymbolType::STRUCTURE, "|"));
				alpha_adapted_epsilon.push_back(SYMBOL_NULL);

				// A����A', A'����A'|��
				left_to_right[left] = beta_adapted;
				left_to_right[adapted] = alpha_adapted_epsilon;
			}
			else {  // A���� ����Ҫ������ݹ�����
				left_to_right[left] = right;
			}
		}
		cout << endl;

		cout << "������ݹ����ķ���" << endl;
		for (auto it = left_to_right.begin(); it != left_to_right.end(); ++it) {
			cout << it->first;
			cout << "��";
			for (Symbol sym : it->second) {
				cout << sym;
			}
			cout << endl;
		}
		cout << endl;

		// ���򲻿��ǻ���

		cout << "�ķ��ķ��ս�����ϣ�";
		for (auto it = nonterminal_set.begin(); it != nonterminal_set.end(); ++it) {
			cout << it->value << " ";
		}
		cout << endl;
		cout << "���У��ķ��Ŀ�ʼ����Ϊ��" << start_symbol << endl << endl;
		
		// ��ȡһ���ս���������Ƶ����ĵ�һ�����ս���ļ��ϣ�First����
		function<set<Symbol>(Symbol)> getPossibleFirstTerminalSymbol = [&](Symbol left) {
			set<Symbol> possible_terminal;
			
			auto right = left_to_right[left];
			for (size_t it = 0; it < right.size(); ++it) {
				Symbol current = right[it];
				if (current.type == SymbolType::TERMINAL) {
					possible_terminal.insert(current);

					while (it < right.size() && right[it].value != "|") ++it;  // ������һ����|��֮��
				}
				else if (current.type == SymbolType::NONTERMINAL) {
					set<Symbol> inner_possible_terminal = getPossibleFirstTerminalSymbol(current);
					possible_terminal.insert(inner_possible_terminal.begin(), inner_possible_terminal.end());
						
					if (inner_possible_terminal.count(SYMBOL_NULL) == 0) {
						while (it < right.size() && right[it].value != "|") ++it;  // ������һ����|��֮��
					}
				}
			}
			return possible_terminal;
		};

		cout << "�����First����" << endl;
		for (Symbol left : nonterminal_set) {
			cout << "First(" << left << ") = {";
			
			for (Symbol elem : getPossibleFirstTerminalSymbol(left)) {
				cout << elem << " ";
			}
			cout << "}" << endl;
		}
		cout << endl;

		// ���ݲ���ʽ����������
		for (auto it = nonterminal_set.begin(); it != nonterminal_set.end(); ++it) {
			Symbol left = *it;
			auto right = left_to_right[left];

			// ������������� A��A��|�� �� A���� ������ʽ�Ĳ���ʽ
			// �������� A��A��|�� �Ĳ���ʽ��Ҫ���Ҳ�����|���ָ�ΪA��A����A������������ʽ���д���
			for (size_t it = 0; it < right.size(); ++it) {
				vector<Symbol> current_right;  // ÿ��current_righht��һ����������|���Ĳ���ʽ
				while (it < right.size() && right[it].value != "|") {
					current_right.push_back(right[it++]);
				}

				set<Symbol> possible_terminal;
				if (current_right[0].type == SymbolType::NONTERMINAL) {
					// ���Ҳ��ĵ�һ������Ϊ���ս��������������ս�������Ƶ������ս��
					// �ر�ģ�����������ս�������Ƶ������ս��������Ҫ������һ���ս�������Ƶ����ķ��ս�����Դ�����
					// �����֧�����������First���ϵ�һ����
					for (size_t it = 0; it < current_right.size(); ++it) {
						set<Symbol> inner_possible_terminal = getPossibleFirstTerminalSymbol(current_right[it]);
						possible_terminal.insert(inner_possible_terminal.begin(), inner_possible_terminal.end());

						if (inner_possible_terminal.count(SYMBOL_NULL) == 0) break;
					}
					
				}
				else if (current_right[0].type == SymbolType::TERMINAL) {
					// ���Ҳ��ĵ�һ������Ϊ�ս������ò���ʽֻ�����Ƶ�������ս��
					possible_terminal.insert(current_right[0]);
				}
				else {  // current_right[0] == SYMBOL_NULL
					// ���Ҳ���һ�����ս��������Ҫ������������ʽ���ܵõ��ò���ʽ�������Ƶ������ս��
					// �����֧����������Follow��
					for (Symbol consider_left : nonterminal_set) {
						if (consider_left == left) continue;

						auto consider_right = left_to_right[consider_left];
						for (size_t it = 0; it < consider_right.size(); ++it) {
							if (consider_right[it] == left) {
								// NEED FOLLOW
							}
						}
					}
				}

				// �Դ˲���ʽ���ڷ������н��б��
				for (Symbol terminal : possible_terminal) {
					analyzer.DefineGrammarRule(make_pair(left, terminal), current_right);
				}
			}
		}
		
		// ��ӡ�����ķ�����
		analyzer.PrintGrammarRulesTable();

		return analyzer;
	}
}
