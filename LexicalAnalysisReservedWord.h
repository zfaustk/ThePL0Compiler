#pragma once
#ifndef _DFA_LEXICAL_ANALYSIS_RESERVEDWORD
#define _DFA_LEXICAL_ANALYSIS_RESERVEDWORD

#include<map>

namespace KH{
	
	//RESERVEDWORD	0x03
	const int _BEGIN		= 0x0301;
	const int _END			= 0x0302;
	const int _CONST		= 0x0303;
	const int _DO			= 0x0304;
	const int _CALL			= 0x0305;
	const int _IF			= 0x0306;
	const int _ODD			= 0x0307;
	const int _PROC			= 0x0308;
	const int _READ			= 0x0309;
	const int _WRITE		= 0x030A;
	const int _VAR			= 0x030B;
	const int _WHILE		= 0x030C;
	const int _THEN			= 0x030D;
	const int _FOR			= 0x030E;
	const int _IMPORT		= 0x030F;
	const int _NAMESPACE	= 0x0310;
	const int _GO			= 0x0311;
	const int _TO			= 0x0312;
	const int _MARK_RESERVEDWORD_BEGIN = _BEGIN ;
	const int _MARK_RESERVEDWORD_END = _TO;

	struct LEXICAL_ANALYSIS_RESERVEDWORD_DEFINE{
		typedef int LA_type;
		static const int _BEGIN			= _BEGIN;
		static const int _END			= _END;
		static const int _CONST			= _CONST;
		static const int _DO			= _DO;
		static const int _CALL			= _CALL;
		static const int _IF			= _IF;
		static const int _ODD			= _ODD;
		static const int _PROC			= _PROC;
		static const int _READ			= _READ;
		static const int _WRITE			= _WRITE;
		static const int _VAR			= _VAR;
		static const int _WHILE			= _WHILE;
		static const int _THEN			= _THEN;
		static const int _FOR			= _FOR;
		static const int _IMPORT		= _IMPORT;
		static const int _NAMESPACE		= _NAMESPACE;
		static const int _GO			= _GO;
		static const int _TO			= _TO;
		static	const int _MARK_RESERVEDWORD_BEGIN = _BEGIN ;
		static	const int _MARK_RESERVEDWORD_END = _TO;

		static const bool IsDefined(int sign) { //Sign 是否在定义中 , 死循环时检查此处
			if(sign >= _MARK_RESERVEDWORD_BEGIN && sign <= _MARK_RESERVEDWORD_END) return true;
			return false;
		}

		static const std::string GetReservedWord(int sign)  { //从int值获取类型的名字
			if(!IsDefined(sign))return "UNKNOW RESERVEDWORD";
			switch(sign) {
				//System
				case  _BEGIN		: return "BEGIN"; break;
				case  _END			: return "END"; break;
				case  _CONST		: return "CONST"; break;
				case  _DO			: return "DO"; break;
				case  _CALL			: return "CALL"; break;
				case  _IF			: return "IF"; break;
				case  _ODD			: return "ODD"; break;
				case  _PROC			: return "PROC"; break;
				case  _READ			: return "READ"; break;
				case  _WRITE		: return "WRITE"; break;
				case  _VAR			: return "VAR"; break;
				case  _WHILE		: return "WHILE"; break;
				case  _THEN			: return "THEN"; break;
				case  _FOR			: return "FOR"; break;
				case  _IMPORT		: return "IMPORT"; break;
				case  _NAMESPACE	: return "NAMESPACE"; break;
				case  _GO			: return "GO"; break;
				case  _TO			: return "TO"; break;
				default			: return "UNKNOW RESERVEDWORD" ;		break;
			}
			return "UNKNOW RESERVEDWORD";
		}

	};

	typedef LEXICAL_ANALYSIS_RESERVEDWORD_DEFINE LA_RWordDef;


	template<class _WordType, class _SignType>
	class  _ReservedWord{
	public:
		typedef _WordType WordType;
		typedef _SignType SignType;
		typedef std::map<_WordType,_SignType> Map;

		_SignType Find(_WordType w) {
			Map::iterator i = ReservedWords.find(w);
			if(i == ReservedWords.end()) return (_SignType)0;
			else return ReservedWords[w];
		}

		_ReservedWord& Add(_WordType w, _SignType sign) {
			Map::iterator i = ReservedWords.find(w);
			if(i != ReservedWords.end())ReservedWords.erase(i);
			ReservedWords.insert( Map::value_type(w, sign ) );
			return (*this);
		}

	private:
		std::map<_WordType,_SignType> ReservedWords;
	};

};

#endif