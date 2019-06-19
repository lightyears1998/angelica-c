#include "common.h"

namespace angelica {

	// 默认构造空的终结符。
	Symbol::Symbol() {
		this->type = SymbolType::TERMINAL;
		this->value = "ε";
	}

	// 使用单一value进行构造时，默认type为STRUCTRUE。
	Symbol::Symbol(const string & value) {
		this->type = SymbolType::STRUCTURE;
		this->value = value;
	}

	Symbol::Symbol(SymbolType type, const string & value) {
		this->type = type;
		this->value = value;
	}

	// 为单词符号定义输出
	ostream& operator << (ostream&out, const Symbol sym) {
		out << sym.value;
		return out;
	}
}