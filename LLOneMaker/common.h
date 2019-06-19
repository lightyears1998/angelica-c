// commom.h
//
// ���嵥�ʷ��ŵ��ֱ�enum SymbolType��
// �Լ����ʷ���struct Symbol��


#pragma once

#include <string>
#include <ostream>

namespace angelica
{
	using namespace std;

	// ���ʷ��ŵ��ֱ�
	// TERMINAL    - �ս��
	// NONTERMINAL - ���ս��
	// STRUCTURE   - �ķ��еġ���������|���Ƚṹ���ַ�
	enum class SymbolType : int
	{
		TERMINAL, NONTERMINAL, STRUCTURE
	};

	// ���ʷ���
	// ���ս��ʹ��Symbol(SymbolType::TERMINAL, "��")��ʾ��
	struct Symbol
	{
		SymbolType type;  // ���ʷ����ֱ�
		string value;     // ���ʷ��ŵ�ֵ

		// Ĭ�Ϲ���յ��ս����
		Symbol();

		// ʹ�õ�һvalue���й���ʱ��Ĭ��typeΪSTRUCTRUE��
		Symbol(const string& value);
		
		Symbol(SymbolType type, const string& value);

		bool operator == (const Symbol& rhs) const {
			return type == rhs.type && value == rhs.value;
		}

		bool operator != (const Symbol& rhs) const {
			return type != rhs.type || value != rhs.value;
		}

		bool operator < (const Symbol& rhs) const {
			if (type != rhs.type) {
				return type < rhs.type;
			}
			return value < rhs.value;
		}
	};

	ostream& operator << (ostream&out, const Symbol sym);

	const Symbol NULL_SYMBOL = Symbol(SymbolType::TERMINAL, "��");
}
