#pragma once
#ifndef _KH_DRAW_TOKEN_LIST
#define _KH_DRAW_TOKEN_LIST

#include<string>
#include<list>
#include<vector>
#include"KH_TextList.h"
#include"LexicalAnalysis.h"
#include"LA_View.h"

namespace KH 
{
	class TokenList
	{
	public:
		typedef std::list<std::vector<KH::Token>> LLV;
		typedef std::vector<KH::Token> LV;
		typedef KH::Token ValueType;
		typedef LLV::iterator iterator;

		//Set;
		void Initial(KH::TextList tl){
			Change(tl);
			
		}

		void Change(KH::TextList tl){
			Content.push_back(std::vector<Token>());
			posLine = Content.begin();
			
			KH::TextList::iterator itText = tl.begin();
			KH::Token tk ;
			for(itText = tl.begin() ; itText != tl.end() ; itText ++ ){
				std::string str = tl.GetString(itText);
				while(!str.empty()) 
				{
					tk = la.GetAToken(str);
					posLine->push_back(tk);
				}
				if(!posLine->empty()){
					Content.push_back(std::vector<Token>());
					posLine ++;
				}
			}
		}

		void Clear(){
			this->Content.clear();
		}
		//Erase
		void EraseString() { 
			if(posCloumn != posLine->begin() && posCloumn != posLine->end() ){
				LV::iterator it = posCloumn;
				it ++;
				posLine->erase(posCloumn); 
				it --;
				posCloumn = it;
			}
			else
			CheckLine();
		}
		//Get iterator;
		iterator now() {
			return posLine;
		}
		iterator begin(){ return Content.begin(); }
		iterator end(){ return Content.end(); }

		void handleMoveUp(int nline = 1) { 
			for(int i = 0 ; i < nline ; i ++ ){
				if(posLine != Content.begin()){
					posLine --; 
				}
			}
		}
		void handleMoveTop() { 
				posLine = Content.begin(); 
		}
		void handleMoveDown(int nline = 1) { 
			if(posLine == Content.end())return ;
			iterator itl = posLine; 
			for(int i = 0 ; i < nline ; i ++ ){
				itl = posLine;
				itl ++;
				if(itl != Content.end()) posLine ++; 
			}
		}
		void handleMoveButton() { 
			posLine = Content.end(); 
			posLine --;
		}
		
		int LineNumber(bool BlankPass = false) {
			LLV::iterator it = Content.begin();
			for(int i = 0 ; it != Content.end() ; it ++ , i ++ ){
				if(it == posLine) return i;
			}
			return -1;
		}
		
		//得到当前行到选中单词为止的字符串
		KH::Token GetCloume();
		//得到当前行的Tokens;
		LV GetTokenList(){
			GetTokenList(posLine);
		}
		//得到某行的Tokens;
		LV GetTokenList(iterator tki){
			return LV(*tki);
		}

	public:
		LexicalAnalysis	la;
	private:
		LLV		Content;
		LLV::iterator	posLine;
		LV::iterator	posCloumn;
		
		//
		void CheckLine(){
			if(Content.size() > 1 && posLine->size() <= 1 && posLine != Content.begin()) {
				iterator i = posLine;
				i++;
				Content.erase(posLine);
				i--;
				posLine = i;

			}
			ResetCloumn();
		}

		void ResetCloumn() {
			LV::iterator it = posLine->end();
			it --;
			posCloumn = it; 
		}
	};

};

#endif

