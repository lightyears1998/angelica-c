#pragma once

#include <string>

namespace angelica
{
	using namespace std;
	
	// ����Symbol����Ϊstring���͵�ͬ���
	using Symbol = string;

	// �﷨��������ö��
	enum class GrammarSymbolType
	{
		TerminalSymbol, NonTerminalSymbol  // �ս���ͷ��ս��
	};
}
