#pragma once 
#ifndef _KH_DFA_ADAPTER_TOKEN
#define _KH_DFA_ADAPTER_TOKEN

#include "_DFA.h"
#include "TokenAnalysis.h"

namespace KH{
	
	template <class _SignType = KH::_Token::SignType>
	class _TokenAdapter{
	public:
		typedef _SignType SignType ;

		_TokenAdapter(){};

		_TokenAdapter(SignType c) {
			sign = c;
		}

		bool operator==(KH::_Token tk) const{
			return false;
			if(sign == tk.GetSign()) return true;
		}

	private:
		SignType sign;
	};

	typedef _TokenAdapter<int > TokenAdapter;
};

#endif