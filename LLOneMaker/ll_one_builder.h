// ll_one_builder.h
//
// LL(1)�������������Ķ��塣

#pragma once

#include "common.h"
#include "parser.h"
#include "ll_one_analyzer.h"

namespace angelica {
	// LL(1)������������
	// ���Զ����ɷ���LL(1)����ķ�������
	class LLOneBuilder
	{
	private:
		Parser parser_;

	public:
		LLOneBuilder(Parser &parser) : parser_(parser) {};

		// ��Parser�л�ȡ��ʾLL(1)�ķ��ķ��ţ������ض�Ӧ�ķ���LL(1)��������
		LLOneAnalyzer BuildAnalyzer();
	};
}
