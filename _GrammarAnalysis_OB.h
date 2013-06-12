#pragma once
#ifndef _GRAMMAR_ANALYSIS_OB
#define _GRAMMAR_ANALYSIS_OB

#include "DFAMachine.h"
#include "_DFA_Adapter_Token.h"
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <map>

namespace KH {

	template< class _TokenSign>
	class _Grammar {
	public :
		typedef _TokenSign TokenSign;
		
		TokenSign operator[] (int i){
			if('t' = Format[i])return TokenSignList[FormatNum[i]];
			else if('G' = Format[i]) return GrammarList[FormatNum[i]];
			return 0;
		}

		void insertToken(TokenSign ts) {
			TokenSignList += ts;
			FormatNum += TokenSignList.length - 1;
		}

		void insertGrammar(TokenSign ts) {
			GrammarList += ts;
			FormatNum += GrammarList.length - 1;
		}

	private:
		std::string Format;
		std::vector<int> FormatNum;
		std::vector<TokenSign> TokenSignList;
		std::vector<TokenSign> GrammarList;
	};
	

	template< class _TokenSign>
	class GrammarSentence {
	public:
		typedef _TokenSign TokenSign;

		GrammarSentence &operator()(std::string sFormat,...) { //格式化输入 as " sentence("A->tGt",KH::Identifiar,"B",KH::Int);
			/*	添加指定的final state	*/ 
			std::string::size_type pos = 0;
			std::string buff = sFormat.substr(pos, sFormat.find('->' ,0)- 1);
			std::string sGrammar;
			sGrammar.assign(buff.begin() + buff.find_first_not_of(' '), buff.begin() + buff.find_last_not_of(' ') + 1); 
	
			std::string format;
			for(pos = sFormat.find("->",pos)+2;0 < sFormat.length() - pos; pos ++){
				char c = sFormat[pos];
				if( c != 't' && c != 'G') break;
				format += c;
			}

			

			/*va_list argp; 
			int para = 0;
			va_start(argp,g);
			for(int i = 0; i < format.length(); i++)
			{
				para = va_arg(argp,_Grammar);
				if(para>=0 && para < numofstate) {
					spListFinal.push_back(&sList[para]);
				}
				else throw 0;
			}*/
			return *this;
		}

	private:
		std::map<std::string,TokenSign> gMap;
		std::vector<_Grammar<TokenSign>> gList;
	};








	template <class _Adapter, class _Terminator>
	class GrammarAnalysis {
	
	public:
		typedef _Adapter TokenAdapter;
		typedef _Terminator Token;
		typedef DFAMachine<TokenAdapter, Token>  Machine;



		GrammarAnalysis<TokenAdapter, Token> &AddTransition(int org, int aim, TokenAdapter ta) {
			dfam.AddTransition(org, aim, 1, ta);
			return *this;
		}


	private:
		Machine dfam;

	}; //end of class GA

}; // end of namespace 


#endif