#pragma once
#ifndef _DFA_LEXICAL_ANALYSIS_DEFINE
#define _DFA_LEXICAL_ANALYSIS_DEFINE

#include <string>
#include "LexicalAnalysisReservedWord.h"

namespace KH{

	const int _NULL			= 0x0000; 
	//System	0x00
	const int _BLOCK		= 0x0001;
	const int _MARK_SYSTEM_BEGIN =	_BLOCK;
	const int _MARK_SYSTEM_END =	_BLOCK;
	//Symbol	0x01
	const int _PLUS			= 0x0101;//	+
	const int _MINUS		= 0x0102;//	-
	const int _TIMES		= 0x0103;//	*
	const int _SLASH		= 0x0104;//	/
	const int _BACKSLASH	= 0x0105;//	
	const int _LPAREN		= 0x0106;//	(
	const int _RPAREN		= 0x0107;//	)
	const int _LSQUAREPAREN	= 0x0108;//	[
	const int _RSQUAREPAREN	= 0x0109;//	]
	const int _LBIGPAREN	= 0x010A;//	{
	const int _RBIGPAREN	= 0x010B;//	}
	const int _LANGLE		= 0x010C;//	<
	const int _RANGLE		= 0x010D;//	>
	const int _EQUAL		= 0x010F;//	==
	const int _NEQUAL		= 0x0110;//	!=
	const int _IDENCITAL	= 0x0111;//	===
	const int _LEQUAL		= 0x0112;//	<=
	const int _REQUAL		= 0x0113;//	>=
	const int _COMMA		= 0x0114;//	,
	const int _PERIOD		= 0x0115;//	.
	const int _EXCLAMATION	= 0x0116;//	!
	const int _QUESTION		= 0x0117;//	?
	const int _QUOTE		= 0x0118;//	"
	const int _SINGLEQUOTE	= 0x0119;//	'
	const int _COLON		= 0x011A;// :
	const int _SEMICOLON	= 0x011B;//	;
	const int _DOLLAR		= 0x011C;//	$
	const int _PERCENT		= 0x011D;//	%
	const int _POWER		= 0x011E;//	^
	const int _AT			= 0x011F;//	@
	const int _NON			= 0x0120;//	~
	const int _AND			= 0x0121;//	&
	const int _OR			= 0x0122;//	|
	const int _UNDERLINE	= 0x0123;//	_
	const int _ASSIGN		= 0x0124;//	:=
	const int _MARK_SYMBOL_BEGIN = _PLUS ;
	const int _MARK_SYMBOL_END = _ASSIGN;
	//Data	0x02
	const int _INT			= 0x0201;
	const int _FLOAT		= 0x0202;
	const int _IDENTIFIER	= 0x0203;
	const int _STRING		= 0x0204;
	const int _RESERVEDWORD = 0x0205;
	const int _ANNOTATION	= 0X0206;
	const int _MARK_DATASYMBOL_BEGIN = _INT ;
	const int _MARK_DATASYMBOL_END = _ANNOTATION;

	struct LEXICAL_ANALYSIS_DEFINE{
		typedef int LA_type;
		//System
		static const int _NULL				= _NULL;
		static const int _BLOCK				= _BLOCK;
		static const int _MARK_SYSTEM_BEGIN = _MARK_SYSTEM_BEGIN ;
		static const int _MARK_SYSTEM_END	= _MARK_SYSTEM_END ;
		//Symbol
		static const int _PLUS				= _PLUS;		//	+
		static const int _MINUS				= _MINUS;		//	-
		static const int _TIMES				= _TIMES;		//	*
		static const int _SLASH				= _SLASH;		//	/
		static const int _BACKSLASH			= _BACKSLASH;	//	.	static const int _LPAREN		= 0x0106;//	(
		static const int _LPAREN			= _LPAREN;		//	(
		static const int _RPAREN			= _RPAREN;		//	)
		static const int _LSQUAREPAREN		= _LSQUAREPAREN;//	[
		static const int _RSQUAREPAREN		= _RSQUAREPAREN;//	]
		static const int _LBIGPAREN			= _LBIGPAREN;	//	{
		static const int _RBIGPAREN			= _RBIGPAREN;	//	}
		static const int _LANGLE			= _LANGLE;		//	<
		static const int _RANGLE			= _RANGLE;		//	>
		static const int _EQUAL				= _EQUAL;		//	==
		static const int _NEQUAL			= _NEQUAL;		//	!=
		static const int _IDENCITAL			= _IDENCITAL;	//	===
		static const int _LEQUAL			= _LEQUAL;		//	<=
		static const int _REQUAL			= _REQUAL;		//	>=
		static const int _COMMA				= _COMMA;		//	,
		static const int _PERIOD			= _PERIOD;		//	.
		static const int _EXCLAMATION		= _EXCLAMATION;	//	!
		static const int _QUESTION			= _QUESTION;	//	?
		static const int _QUOTE				= _QUOTE;		//	"
		static const int _SINGLEQUOTE		= _SINGLEQUOTE; //	'
		static const int _COLON				= _COLON;		//	:
		static const int _SEMICOLON			= _SEMICOLON;	//	;
		static const int _DOLLAR			= _DOLLAR;		//	$
		static const int _PERCENT			= _PERCENT;		//	%
		static const int _POWER				= _POWER;		//	^
		static const int _AT				= _AT;			//	@
		static const int _NON				= _NON;			//	~
		static const int _AND				= _AND;			//	&
		static const int _OR				= _OR;			//	|
		static const int _UNDERLINE			= _UNDERLINE;	//	_
		static const int _ASSIGN			= _ASSIGN;		//	:=
		static const int _MARK_SYMBOL_BEGIN = _MARK_SYMBOL_BEGIN ;
		static const int _MARK_SYMBOL_END	= _MARK_SYMBOL_END ;
		//Data
		static const int _INT			= _INT;
		static const int _FLOAT			= _FLOAT;
		static const int _IDENTIFIER	= _IDENTIFIER;
		static const int _STRING		= _STRING;
		static const int _RESERVEDWORD  = _RESERVEDWORD;
		static const int _ANNOTATION	= _ANNOTATION;
		static const int _MARK_DATASYMBOL_BEGIN = _MARK_DATASYMBOL_BEGIN ;
		static const int _MARK_DATASYMBOL_END	= _MARK_DATASYMBOL_END ; 
		static const std::string GetTypeString(int sign)  { //从int值获取类型的名字
			if(LA_RWordDef::IsDefined(sign)) {
				return LA_RWordDef::GetReservedWord(sign);
			}
			switch(sign) {
				//System
				case _BLOCK			:return "BLOCK";		break;
				//Symbol
				case _PLUS			: return "PLUS"	;		break;
				case _MINUS			: return "MINUS";		break;
				case _TIMES			: return "TIMES";		break;
				case _SLASH			: return "SLASH";		break;
				case _BACKSLASH		: return "BACKSLASH";	break;
				case _LPAREN		: return "LPAREN"	;	break;
				case _RPAREN		: return "RPAREN"	;	break;
				case _RSQUAREPAREN	: return "RSQUAREPAREN"	;	break;
				case _LBIGPAREN		: return "LBIGPAREN"	;	break;
				case _RBIGPAREN		: return "RBIGPAREN"	;	break;
				case _LANGLE		: return "LANGLE"	;	break;
				case _RANGLE		: return "RANGLE"	;	break;
				case _EQUAL			: return "EQUAL"	;	break;
				case _NEQUAL		: return "NEQUAL"	;	break;
				case _IDENCITAL		: return "IDENCITAL";	break;
				case _LEQUAL		: return "LEQUAL"	;	break;
				case _REQUAL		: return "REQUAL"	;	break;
				case _COMMA			: return "COMMA"	;	break;
				case _PERIOD		: return "PERIOD"	;	break;
				case _EXCLAMATION	: return "EXCLAMATION"	;	break;
				case _QUESTION		: return "QUESTION"		;	break;
				case _QUOTE			: return "QUOTE"		;	break;
				case _SINGLEQUOTE	: return "SINGLEQUOTE"	;	break;
				case _COLON			: return "COLON"		;	break;
				case _SEMICOLON		: return "SEMICOLON"	;	break;
				case _DOLLAR		: return "DOLLAR"	;	break;
				case _PERCENT		: return "PERCENT"	;	break;
				case _POWER			: return "POWER"	;	break;
				case _AT			: return "AT"		;	break;
				case _NON			: return "NON"		;	break;
				case _AND			: return "AND"		;	break;
				case _OR			: return "OR"		;	break;
				//Data
				case _INT			: return "INT"		;	break;
				case _FLOAT			: return "FLOAT"	;	break;
				case _IDENTIFIER	: return "IDENTIFIER";	break;
				case _STRING		: return "STRING"	;	break;
				case _RESERVEDWORD	: return "RESERVEDWORD"	;	break;
				case _ANNOTATION	: return "ANNOTATION"	;	break;
				case _ASSIGN	: return "ASSIGN"	;	break;
				default			: return "UNDEFINE" ;		break;
			}
			return "UNDEFINE";
		}

		static const bool IsTypeDefined(int sign) { //Sign 是否在定义中 , 死循环时检查此处
			if(sign >= _MARK_SYSTEM_BEGIN && sign <= _MARK_SYSTEM_END) return true;
			if(sign >= _MARK_SYMBOL_BEGIN && sign <= _MARK_SYMBOL_END) return true;
			if(sign >= _MARK_DATASYMBOL_BEGIN && sign <= _MARK_DATASYMBOL_END) return true;
			if(LA_RWordDef::IsDefined(sign)) return true;
			return false;
		}
	};
	
		typedef LEXICAL_ANALYSIS_DEFINE LA_Def;
	
};
#endif

