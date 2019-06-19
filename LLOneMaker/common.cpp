#include "common.h"

namespace angelica {

	// Ĭ�Ϲ���յ��ս����
	Symbol::Symbol() {
		this->type = SymbolType::TERMINAL;
		this->value = "��";
	}

	// ʹ�õ�һvalue���й���ʱ��Ĭ��typeΪSTRUCTRUE��
	Symbol::Symbol(const string & value) {
		this->type = SymbolType::STRUCTURE;
		this->value = value;
	}

	Symbol::Symbol(SymbolType type, const string & value) {
		this->type = type;
		this->value = value;
	}

	// Ϊ���ʷ��Ŷ������
	ostream& operator << (ostream&out, const Symbol sym) {
		out << sym.value;
		return out;
	}
}