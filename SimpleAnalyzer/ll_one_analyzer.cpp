// ll_one_analyzer.cpp
//
// LL(1)�﷨������class Analyzer��ʵ�֡�


#include "ll_one_analyzer.h"


namespace angelica
{
	LLOneAnalyzer::LLOneAnalyzer()
	{
		// �����ս��
		DefineGrammarSymbol("E", GrammarSymbolType::NonTerminalSymbol);
		DefineGrammarSymbol("E'", GrammarSymbolType::NonTerminalSymbol);
		DefineGrammarSymbol("T", GrammarSymbolType::NonTerminalSymbol);
		DefineGrammarSymbol("T'", GrammarSymbolType::NonTerminalSymbol);
		DefineGrammarSymbol("F", GrammarSymbolType::NonTerminalSymbol);

		// ������ս��
		DefineGrammarSymbol("i", GrammarSymbolType::TerminalSymbol);
		DefineGrammarSymbol("(", GrammarSymbolType::TerminalSymbol);
		DefineGrammarSymbol(")", GrammarSymbolType::TerminalSymbol);
		DefineGrammarSymbol("+", GrammarSymbolType::TerminalSymbol);
	}


	void LLOneAnalyzer::DefineGrammarSymbol(string mark, GrammarSymbolType type)
	{
		symbols_[mark] = type;
	}


	void LLOneAnalyzer::DefineStartSymbol(string mark)
	{
		start_symbol_ = mark;
	}


	void LLOneAnalyzer::DefineGrammarRule(pair<string, string> line_column_pair, pair<string, string> left_right_part_pair)
	{

	}


	GrammarSymbolType LLOneAnalyzer::getGrammarSymbolType(string mark)
	{
		return GrammarSymbolType();
	}
}