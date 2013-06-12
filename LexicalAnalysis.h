#pragma once
#ifndef _DFA_LEXICAL_ANALYSIS
#define _DFA_LEXICAL_ANALYSIS

#include"TokenAnalysis.h"

#include"DFAMachine.h"
#include"LexicalAnalysisDefine.h"

#include"string"
#include<stdarg.h>

namespace KH{

	class LexicalAnalysis { //分析机
	public:
		typedef _Token<std::string, int> Token;
		typedef TokenAnalysis<int, KH::DFARange> TAIR;
		typedef LEXICAL_ANALYSIS_DEFINE TYPEDEF;
		typedef KH::_ReservedWord<std::string, int>  ReservedWord;
		typedef LA_RWordDef Def;

		LexicalAnalysis(){
			VTAIR.clear();
			InitialReservedWord();
		}

		//Set
		friend LexicalAnalysis& operator<<(LexicalAnalysis& la, TAIR ta) {  //插入TAIR
			la.GetTAIRList()->push_back(ta);
			return la;
		}

		LexicalAnalysis& AddTair(int sign, TAIR::DFAMachine &dfam) {	//直接增加tair
			TAIR tair(sign, dfam);
			return (*this)<<tair;
		}

		//Get
		inline std::vector<TAIR>* GetTAIRList() {
			return &VTAIR;
		}

		Token GetAToken( std::string &strInput) {//获取token后将识别出的串从输入中剔除
			std::string::iterator it = strInput.begin();
			std::vector<TAIR>::iterator itTAIR = VTAIR.begin();
			std::string sResult = "";
			int imax = 0;
			TAIR::SignType sign = Token::DefSign ;

			for(; itTAIR != VTAIR.end(); itTAIR ++) { //获取最长可接受Token
				int i = 0;
				it = strInput.begin();
				std::string sTemp = "";
				while(it != strInput.end()){
					sTemp += *it;
					if( itTAIR-> GetPMachine()->InputTerminator(*it) && !itTAIR->GetPMachine()->CheckNULL()) { //如果接受并未跳出DFA机则继续输入
						if( i >= imax) { //i始终比当前数小1
							sResult = sTemp;
							sign = itTAIR->GetSign();
							imax = i + 1;
							//continue;
						}
					}
				
					it ++;
					i++;
				}
			}
			Token t;
			if(!strInput.empty() && sResult.empty()){
				std::string sttr;
				sttr.push_back(*strInput.begin());
				t = Token(sttr,sign);
			}
			else 
				t = Token(sResult, sign);

			itTAIR = VTAIR.begin();
			for(; itTAIR != VTAIR.end(); itTAIR ++) {
				itTAIR->GetPMachine()->Reset();
			}

			if(!t.IsDefined())strInput.erase(strInput.begin()); //如果找不到，则删除一位
			else {
				it = strInput.begin(); //否则，删除imax位
				for(int i = 0; i < imax; i ++) {
					it ++;
				}
				strInput.erase(strInput.begin(), it);
			}
		
			if(t.GetSign() == LA_Def::_IDENTIFIER) {
				int signWord = reservedWord.Find(t.GetValue());
				std::string s = t.GetValue(); 
				if(signWord != 0) {
					if(Def::IsDefined(signWord))
						t.SetToken( s, signWord); //有定义时记录sign
					else
						t.SetToken( s, LA_Def::_RESERVEDWORD);
				}
			}

			return t; //通过.Token::IsUndefine()来检测
		}

		Token GetFirstToken(std::string s) { //安全取用方式，不会修改输入的string值
			return GetAToken(s);
		}

	private:
		std::vector<TAIR> VTAIR;
		ReservedWord	reservedWord;

		void InitialReservedWord(){ 
			reservedWord
				.Add("begin",Def::_BEGIN)	.Add("call",Def::_CALL)	.Add("const",Def::_CONST)	.Add("do",Def::_DO)
				.Add("end",Def::_END)		.Add("if",Def::_IF)		.Add("odd",Def::_ODD)		.Add("procedure",Def::_PROC)
				.Add("read",Def::_READ)		.Add("then",Def::_THEN)	.Add("var",Def::_VAR)		.Add("while",Def::_WHILE)
				.Add("write",Def::_WRITE);		
		}

	};

	typedef LexicalAnalysis _LA;

};//end of name space

#endif


