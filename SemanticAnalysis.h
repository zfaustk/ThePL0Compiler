#pragma once
#ifndef _SEMANTIC_ANALYSIS_
#define _SEMANTIC_ANALYSIS_

#include <algorithm>
#include <vector>
#include <string.h>

#include "GrammarErrorType.h"

namespace KH {

	class SemanticAnalysis{
	public :
		//查询变量是否存在
		bool ExistVariable(int line, std::string str){
			if(pExistVariable(line,str)){
				return true;
			}
			else {
				str += " not declaired . ";
				InsertError(line , str );
				return false;
			}
		}

		//插入变量名
		bool PushVariable(int line, std::string str) {
			if(pExistVariable(line ,str)) {
				str += " have been declaired . ";
				InsertError(line , str );
				return false;
			}
			vVariable.push_back(str);
			return true;
		}

		//按行插入错误信息
		void InsertError(int line, std::string str) {
			std::string stemp = ": ";
			stemp += str;
			ErrorList.push_back(KH::_ErrorType(line,stemp));

		}

		//输出错误信息（string）
		std::string	OutErrorString(){
			char str[20] = {0};
			std::string ErrorMSG = "";
			for(KH::_ErrorTypeList::iterator it = ErrorList.begin() ;it != ErrorList.end(); it++){
				sprintf(str,"%d",it->GetLine());
				ErrorMSG += str;
				ErrorMSG += it->Message();
				ErrorMSG += "\n";
			}
			if(ErrorMSG.length() <= 1)ErrorMSG = "";
			else ErrorMSG += "===== Semantic End ====\n";
			return ErrorMSG;
		}

		//
		void Reset(){
			vVariable.clear();
			ErrorList.clear();
		}

	private:
		std::vector<std::string> vVariable;
		KH::_ErrorTypeList ErrorList;

		bool pExistVariable(int line, std::string str){
			for(std::vector<std::string>::iterator it = vVariable.begin() ; it != vVariable.end() ; it ++ )
			{
				if( strcmp(it->c_str(),str.c_str()) == 0 ) return true;
			}
			return false;
		}
	};//end of class

}; // end of namespace 


#endif