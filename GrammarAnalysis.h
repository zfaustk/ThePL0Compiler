#pragma once
#ifndef _GRAMMAR_ANALYSIS_
#define _GRAMMAR_ANALYSIS_

#include "LexicalAnalysis.h"

#include "GrammarErrorType.h"

#include "TokenAnalysis.h"

#include "KH_TextList.h"

#include <string.h>
#include <vector>



namespace KH {

	class GrammarPL0{
	public :
		typedef KH::LA_Def			LA_Def;
		typedef KH::_ErrorType		ErrorType;
		typedef KH::_ErrorTypeList	ErrorTypeList;
		typedef KH::Token			Token;
		typedef std::vector<Token>		TokenVector ;
		typedef std::vector<TokenVector>	TokenMap	;
		typedef std::vector<std::string>	ErrorListOutputType ;
		typedef KH::LexicalAnalysis LA;

		//使用LA初始化
		GrammarPL0(LA &la){
			pla = &la;
			tkMap.clear();
			Reset();
		}

		//使用LA和TextList初始化
		GrammarPL0(LA &la,KH::TextList tl){
			pla = &la;
			tkMap.clear();
			GetInput(tl);
			Reset();	
		}

		//接受一个textlist并转换为tokenlist
		void GetInput(KH::TextList tl){
			Reset();
			KH::TextList::iterator it = tl.begin();
			
			TokenVector TV;
			std::string str;
			tkMap.clear();
			for(int i = 0;it != tl.end(); it++,i++)	{
				str = tl.GetString(it);
				TV = GetTokenVector(i,str);
				if(TV.size() >0)
				tkMap.push_back(TV);
			}
			Reset(false);
		}

		//从一个string加入到一个Token序列
		TokenVector GetTokenVector(TokenVector TV, int line, std::string str){
			Token tk;
			int word = 0;
			bool blank = true;
			while(!str.empty()) {
				tk = pla->GetAToken(str);
				if(!tk.IsDefined()) {
					char sword[20] = {0};
					sprintf(sword,"%d",word);
					ErrorList.push_back(ErrorType(line," " + std::string(sword) + " " + tk.GetValue() +  " | Undefine Word"));//
				}
				else {
					if(tk.GetSign() != KH::_BLOCK){
						word += 1;
						TV.push_back(tk);
						blank = false;
					}
				}
			}
			if(blank)TV.push_back(Token("",KH::_BLOCK));
			return TV;
		}

		TokenVector GetTokenVector(int line, std::string str){
			TokenVector TV = GetTokenVector(TV,line,str);
			return TV;
		}
		
		//获取当前指针所指位置的Token
		Token GetWord(bool AddToNext = false){
			Token word = Token();
			if(itLine == tkMap.end())return word;
			if(itWord != itLine->end())word = *itWord;
			if(AddToNext)
			{
				if(itWord != itLine->end()){
					itWord ++;
				}
				if(itWord == itLine->end()){
					itLine ++;
					itWord = itLine->begin();
				}
			}
			else return word;
		}

		//获取当前指针所指+偏移量位置的Token
		Token GetWord(int offset, bool NotSkipLine) const{
			TokenMap::iterator itL = itLine;
			TokenVector::iterator itW = itWord;

			if( itL == tkMap.end() ) return Token();

			for(int i = 0 ; i < offset ; i ++ ) {
				itW ++;
				if(itW == itL->end()){
					if( NotSkipLine == true)return Token();
					itL++;
					if(itL != tkMap.end())
						itW == itL->begin();
					else return Token();
				}
				if(itL != tkMap.end() && itW != itLine->end())
					if(itW->GetSign() == KH::_BLOCK) 
						offset += 1;
			}

			return *itW;
		}

		//检查是否到末尾
		bool CheckEnd() {
			if(itLine == tkMap.end() || nLine >= tkMap.size())
				return true;
			return false;
		}
		
		bool ExertGrammar(bool isGen = false);

		//当前指针往前跳
		GrammarPL0& skip(int offset, bool NotSkipLine = false){
			if(itLine == tkMap.end())
					return *this;
			for(int i = 0 ; i < offset ; i ++ ) {
				if(itWord != itLine->end())
					itWord ++;
				if(itWord == itLine->end()){
					if( NotSkipLine == true){
						break;
					}
					LineMoveForward();
				}
				if(itLine != tkMap.end() && itWord != itLine->end())
					if(itWord->GetSign() == KH::_BLOCK) 
						offset += 1;
			}
			return *this;
		}

		//下移一行
		void LineMoveForward(){	//TODO：有时会越界！！比如在khtest的代码里end之前加个a
			if(itLine != tkMap.end()){
				nLine++;
				itLine++;
				if(itLine != tkMap.end())
					itWord = itLine->begin();
			}
		}

		//获得当前所指行
		int GetLine(){
			return nLine;
		}

		//插入错误信息
		void InsertError(ErrorType e){
			ErrorList.push_back(e);
		}

		//输出错误信息的表
		ErrorListOutputType OutErrorList(){ 
			char str[20]="";
			ErrorListOutputType sL;
			ErrorTypeList::iterator it = ErrorList.begin() ;
			for(;it != ErrorList.end(); it++){
				sprintf(str,"%d",it->GetLine());
				sL.push_back( std::string(str) + it->Message());
			}
			return sL;
		}

		//是否成功
		bool IsPassed(){
			return ErrorList.empty();
		}

		//输出错误信息（string）
		std::string	OutErrorString(){
			ErrorListOutputType sL = OutErrorList();
			ErrorListOutputType::iterator it = sL.begin();
			std::string str = "";
			for(;it != sL.end(); it++){
				str += (*it + "\n");
			}
			if(str.length() <= 1)str = "Success\n";
			return str;
		}

		//重置当前位置和错误信息表
		void Reset(bool ClearErrorList = true){
			nLine = 0;
			if(ClearErrorList)
				ErrorList.clear();
			itLine = tkMap.begin();
			if(itLine != tkMap.end())
				itWord = itLine->begin();
		}

//#======================================================================================

	private :

		bool GrammarSign(KH::GrammarPL0::Token t,const int d);
		//错误处理
		void Error(bool &result, std::string message, bool skip = true );
		//分程序语法判断
		bool Block();
		//条件
		bool ConditionParsing();
		//"表达式"语法分析
		bool ExpressionParsing();
		//"项"语法分析
		bool TermParsing();
		//"因子"语法分析
		bool FactorParsing();
		//"语句"语法分析
		bool StatementParsing();
//#======================================================================================
		void GenPush(std::string str){ //生成的C代码
			if(IsGenerate && !str.empty())
				sGens.push_back(str);
		}

	private	:
		TokenMap tkMap;
		int nLine;
		TokenMap::iterator itLine;
		//TokenVector	tkVector;
		TokenVector::iterator itWord;
		LA* pla;
		ErrorTypeList ErrorList;
		
		bool IsGenerate;
	public:
		std::vector<std::string> sGens;
		std::vector<std::string> funcNames;
	};//end of class GrammarPL0

}; // end of namespace 


#endif