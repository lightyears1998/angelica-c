// parser.h
//
// ���������л���ս�������ս�����ķ��ṹ���ŵ�Parser��

#pragma once

#include "common.h"

#include <vector>
#include <iostream>

namespace angelica
{
	using namespace std;

	class Parser
	{
	private:
		istream &in_;

	public:
		Parser(istream& in) : in_(in) {};
		~Parser() = default;

		// ���������н������ʷ��ţ�ֱ���������з���
		vector<Symbol> ParseLineFromInputStream();
	};
}
