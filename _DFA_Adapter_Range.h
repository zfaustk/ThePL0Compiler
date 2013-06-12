#pragma once 
#ifndef _KH_DFA_ADAPTER_RANGE
#define _KH_DFA_ADAPTER_RANGE

#include "_DFA.h"

namespace KH{

	class _RangeAdapter{
	public:
		_RangeAdapter(){};
		_RangeAdapter(char min, char max) {
			Min = min;
			Max = max;
		}

		_RangeAdapter(char c) {
			Min = Max = c;
		}

		bool operator==(char c) const{
			if(c>=Min && c<=Max) return true;
			return false;
		}

	private:
		char Min;
		char Max;
	};

	typedef _RangeAdapter RangeAdapter;
};

#endif