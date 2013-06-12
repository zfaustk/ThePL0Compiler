#include "KH_TextList.h"
#include <iostream>

KH::TextList::TextList(void)
{
	Initial();
}

KH::TextList::~TextList(void)
{
}

void KH::TextList::Clear()
{
	this->Content.clear();
	Initial();
}

void KH::TextList::Initial(std::string sBegin, std::string sEnd){
	LV lv;
	if(!sBegin.empty())lv.push_front(sBegin);
	lv.push_back(sEnd);
	Content.push_back(lv);
	posLine = Content.begin();
	posCloumn = posLine->begin();
	if(ConsoleList.empty())ConsoleList.push_back("");
	nPosInner = 0;
	pConsole = ConsoleList.begin();
}

//// Console
void KH::TextList::strConsolePaste(){
	strConsole = *pConsole ;
}

void KH::TextList::strConsoleLatest(){
	pConsole = ConsoleList.end();
	pConsole -- ;
	strConsolePaste();
}

void KH::TextList::strConsoleLast(){
	if(pConsole != ConsoleList.begin())
		pConsole --;
	strConsolePaste();
}

void KH::TextList::strConsoleNext(){
	if(pConsole != ConsoleList.end())
		pConsole ++;
	if(pConsole == ConsoleList.end())
		pConsole --;
	strConsolePaste();
}

void KH::TextList::strConsolePush(){
	if(strConsole.length() > 0 ){
		if(ConsoleList.size()>20)
			ConsoleList.pop_front(); //大于20跳时把栈底弹出
		ConsoleList.pop_back();
		ConsoleList.push_back(strConsole);
		ConsoleList.push_back("");
	}
	strConsoleLatest();
}


//void KH::TextList::Format(LexicalAnalysis la){
//	std::string strTmp = "";
//	Token tkTmp;
//	bool ClearAlready = false;
//	for(iterator it = Content.begin(); it != Content.end(); it ++)
//	{
//		ClearAlready = false;
//		strTmp = GetString(it);
//		while(!strTmp.empty()) {
//			tkTmp = la.GetAToken(strTmp);
//			if(tkTmp.GetSign() != KH::_BLOCK ) {
//				if(!ClearAlready){
//					it->clear();
//					ClearAlready = true;
//				}
//				it->push_back(tkTmp.GetValue());
//			}
//		}
//	}
//}

void KH::TextList::AddLine(){
	KH::TextList::LV lv;
	lv.push_back("");
	posLine ++ ;
	Content.insert(posLine,lv);
	posLine --;
	posCloumn = posLine->begin();
}

void KH::TextList::InsertString(std::string str){
	if(str.empty()) return;
	posCloumn++;
	posLine->insert(posCloumn, str);
	posCloumn--;
}
void KH::TextList::InsertLine(std::string str){
	AddLine();
	std::string strTmp = "";
	for(std::string::iterator i = str.begin(); i != str.end(); i ++){
		if(*i != ' ' && *i != '\r'  && *i != '\n'){
			if(*i != '\t') strTmp += *i;
			else {
				if(!strTmp.empty()){
					InsertString(strTmp + " ");
					strTmp = "";
				}
				InsertString("\t ");
			}
		}
		else{
			if(!strTmp.empty()){
				InsertString(strTmp + " ");
				strTmp = "";
			}
		}
	}
	if(!strTmp.empty()){
		InsertString(strTmp + " ");
	}
}

void KH::TextList::InsertChar(char c){
	posCloumn->insert(nPosInner,1,c);
	std::string s = *posCloumn;
	std::cout << nPosInner++;
}

KH::TextList::iterator KH::TextList::now() const{
	return posLine;
}

std::string KH::TextList::GetString(){
	return GetString(posLine);
}

std::string KH::TextList::GetString(iterator i){
	if(i != end());
	LV::iterator it = i->begin();
	std::string s = "";
	for(;it != i->end(); it++ ) {
		s += *it;
	}
	return s;
}

std::string KH::TextList::GetCloumeString(bool Until){
	LV::iterator it = posLine->begin();
	std::string s = "";
	for(;it != posLine->end(); it++ ) {
		if(Until || it == posCloumn)
			s += *it;
		if(it == posCloumn) break;
	}
	return s;
}

KH::TextList::LV KH::TextList::GetStringLine(){
	return GetStringLine(posLine);
}

KH::TextList::LV KH::TextList::GetStringLine(iterator i){
	return LV(*i);
}

KH::TextList::iterator KH::TextList::GetPosLine(){
	if(posLine != Content.end())
		return posLine;
	else return Content.begin();
}