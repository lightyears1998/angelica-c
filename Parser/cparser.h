#pragma once

#include "parser.h"

namespace angelica
{
	class CParser : public Parser
	{
	public:
		CParser();
		void Parse();
	};
}