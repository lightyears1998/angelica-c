#include "common.h"


namespace angelica 
{
	using namespace std;

	Symbol::Symbol(SymbolType type) {
		type_ = type;
	}

	Symbol::Symbol(SymbolType type, string value) {
		type_ = type;
		value_ = value;
	}

	string Symbol::ToString()
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
}
