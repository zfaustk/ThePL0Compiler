#pragma once
#ifndef _KH_DRAW_TEXT_LIST
#define _KH_DRAW_TEXT_LIST

#include<string>
#include<list>
//#include"LexicalAnalysis.h"

namespace KH 
{
	class TextList
	{
	public:
		typedef std::list<std::list<std::string>> LLV;
		typedef std::list<std::string> LV;
		typedef std::string ValueType;
		typedef LLV::iterator iterator;

		TextList(void);
		~TextList(void);

		//Set;
		void Initial(std::string sBegin = "",std::string sEnd = "");
		void AddLine();
		void Clear();
		/*void Format(LexicalAnalysis	la);*/
		void InsertString(std::string str);
		void InsertLine(std::string str = "");
		void InsertChar(char c);
		//Erase
		void EraseString() { 
			if(posCloumn != posLine->begin() && posCloumn != posLine->end() && !posCloumn->empty()){
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
		iterator now() const;
		iterator begin(){ return Content.begin(); }
		iterator end(){ return Content.end(); }

		void handleMoveUp(int nline = 1) { 
			for(int i = 0 ; i < nline ; i ++ ){
				if(posLine != Content.begin()){
					posLine --; 
					ResetCloumn();
				}
			}
		}
		void handleMoveTop() { 
				posLine = Content.begin(); 
				ResetCloumn();
		}
		void handleMoveDown(int nline = 1) { 
			iterator itl = posLine; 
			for(int i = 0 ; i < nline ; i ++ ){
				itl = posLine;
				itl ++;
				if(itl != Content.end()) posLine ++; 
				ResetCloumn();
			}
		}
		void handleMoveButton() { 
			posLine = Content.end(); 
			posLine --;
			ResetCloumn();
		}
		void handleMoveLeft(int nCloumn = 1) { 
			if(posLine->end() == posCloumn){
				posCloumn --;
				return ;
			}
			for(int i = 0 ; i < nCloumn ; i ++ ){
				if(posLine->begin() != posCloumn){
					posCloumn --; 
				}
			}
		}
		void handleMoveRight(int nCloumn = 1) { 
			LV::iterator itC = posCloumn; 
			for(int i = 0 ; i < nCloumn ; i ++ ){
				itC = posCloumn;
				itC ++;
				if(itC != posLine->end()) posCloumn ++; 
			}
		}



		int LineNumber(bool BlankPass = false) {
			LLV::iterator it = Content.begin();
			for(int i = 0 ; it != Content.end() ; it ++ , i ++ ){
				if(it == posLine) return i;
			}
			return -1;
		}
		//得到当前行的字符串;
		std::string GetString();
		//得到当前行到选中单词为止的字符串
		std::string GetCloumeString(bool Until = false);
		//将某行转化成字符串
		std::string GetString(iterator i);	
		LV GetStringLine();				//得到当前行指针
		LV GetStringLine(iterator i);	//得到某行指针
		iterator KH::TextList::GetPosLine();
	public:
		std::string strConsole;
		std::string strEcho;
		LV ConsoleList;
		LV::iterator pConsole;
		void strConsoleLatest();
		void strConsoleLast();
		void strConsoleNext();
		void strConsolePush();
		void strConsolePaste();
		
	private:
		LLV		Content;
		LLV::iterator	posLine;
		LV::iterator	posCloumn;
		ValueType::size_type	nPosInner;
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

