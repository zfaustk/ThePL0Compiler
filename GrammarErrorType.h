#pragma once
#ifndef _GRAMMAR_ANALYSIS_ERRORTYPE
#define _GRAMMAR_ANALYSIS_ERRORTYPE

#include <string.h>
#include <vector>

namespace KH {

	class _ErrorType{
	public :
		_ErrorType(){}
		_ErrorType(int line){
			LineNum = line;
			ErrorMessage = "";
		}
		_ErrorType(int line,std::string error){
			LineNum = line;
			ErrorMessage = error;
		}

		int GetLine() { return LineNum; }
		std::string Message() { return ErrorMessage; }
	private	:
		int LineNum;
		std::string ErrorMessage;
	};//end of class GrammarPL0

	typedef std::vector<_ErrorType> _ErrorTypeList ;

}; // end of namespace 


#endif