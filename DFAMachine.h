#pragma once 
#ifndef _KH_DFA_INTERFACE
#define _KH_DFA_INTERFACE

#include "_DFA.h"
#include "_DFA_Adapter_Range.h"
#include <stdarg.h>

namespace KH{
	
	template<class _Adapter,class _Terminator>
	class DFAMachine{
		typedef _Adapter Adapter;
		typedef _Terminator Terminator;
		typedef State<_Adapter,_Terminator> _State;
		std::vector<Terminator> Vector;
	public:

		DFAMachine(){ 
			dfa = DFA<_Adapter,_Terminator>(_Adapter());
			//pDfa = new DFA<_Adapter,_Terminator>(_Adapter());
		}

		~DFAMachine(){ 
			if(pDfa != NULL)
				delete pDfa;
		}


		DFAMachine(_Adapter a){ 
			dfa = DFA<_Adapter,_Terminator>(a);
			//pDfa = new DFA<_Adapter,_Terminator>(a);
		}

		DFAMachine(int numofstate,int numoffinal, ...){ //初始化

			std::vector<DFA_Transition<Adapter,_State>> transitions;

			this->numOfState = numofstate ;

			/*	创建指定数量的 State	*/
			//State<_Adapter,_Terminator>* pState;	
			for(int i = 0; i < numOfState; i++) {
				sList.push_back(State<_Adapter,_Terminator>());
			}

			/*	添加指定的final state	*/ 
			va_list argp; 
			int para = 0;
			va_start(argp,numoffinal);
			for(int i=0; i < numoffinal; i++)
			{
				para = va_arg(argp,int);
				if(para>=0 && para < numofstate) {
					spListFinal.push_back(&sList[para]);
				}
				else throw 0;
			}

			/* 套用 DFA */
			dfa = DFA<_Adapter,_Terminator>(sList,spListFinal,transitions);
			/*if(pDfa != NULL)
				delete pDfa;*/
			//pDfa = new DFA<_Adapter,_Terminator>(sList,spListFinal,transitions);
		}

		/*	为DFA对象添加转换规则	*/
		DFAMachine& AddTransition(int nState, int nNextState, int nAdapter, ...) {
			va_list argp; 
			_Adapter para = 0;
			va_start(argp,nAdapter);
			for(int i = 0; i < nAdapter; i ++)
			{
				para = va_arg(argp,_Adapter);
				dfa.AddTransition(nState, nNextState, para);
				//pDfa->AddTransition(nState, nNextState, para);
			}
			return (*this);
		}

		/*DFAMachine& AddTransition(int nState, int nNextState, _Adapter a) {
			AddTransition(1,1,1,a);
			return (*this);
		}*/

		/* 重置 */
		void Reset() { 
			dfa.Reset(); 
			//pDfa->Reset();
		}

		/* 检查是否为终态	*/
		bool CheckFinal(){
			//return pDfa->CheckFinal();
			return dfa.CheckFinal();
		}

		bool CheckNULL(){
			//return pDfa->CheckNULL();
			return dfa.CheckNULL();
		}

		bool InputTerminator(Terminator t){
			//return pDfa->InputTerminator(t);
			return dfa.InputTerminator(t);
			
		}

		//bool operator== (DFAMachine<class _Adapter,class _Terminator> dfam,Vector vct){
		//	dfam.Reset();
		//	for(Vector::iterator i = vct.begin(); i != vct.end(); i++){
		//		dfam.InputTerminator(*i);
		//	}
		//	bool result = dfam.CheckFinal();
		//	dfam.Reset();
		//	return result;
		//}

		friend DFAMachine& operator<<(DFAMachine& dm, Terminator t){
			dm.InputTerminator(t);
			return dm;
		}

	private :
		DFA<_Adapter,_Terminator> *pDfa;
		DFA<_Adapter,_Terminator> dfa;
		std::vector<_State> sList;
		std::vector<_State*> spListFinal;

		int numOfState;
	};

	/* Adapter define */

#ifndef _KH_DFA_INTERFACE_ADAPTER
#define _KH_DFA_INTERFACE_ADAPTER
	RangeAdapter aDigit('0','9');
	RangeAdapter aLower('a','z');
	RangeAdapter aUpper('A','Z');
	RangeAdapter aPlus('+');
	RangeAdapter aMinus('-');
	RangeAdapter aTimes('*');
	RangeAdapter aSlash('/');
	RangeAdapter aBackSlash('\\');
	RangeAdapter aLParen('(');
	RangeAdapter aRParen(')');
	RangeAdapter aLSquareParen('[');
	RangeAdapter aRSquareParen(']');
	RangeAdapter aLBigParen('{');
	RangeAdapter aRBigParen('}');
	RangeAdapter aLAngle('<');
	RangeAdapter aRAngle('>');
	RangeAdapter aEqual('=');
	RangeAdapter aComma(',');
	RangeAdapter aPeriod('.');
	RangeAdapter aColon(':');
	RangeAdapter aSemicolon(';');
	RangeAdapter aExclamation('!');
	RangeAdapter aUnderline('_');
	RangeAdapter aQuote('"');
	RangeAdapter aSharp('#');
	RangeAdapter aBlockSpace(' ');
	RangeAdapter aBlockNewline('\r');
	RangeAdapter aBlockEnter('\n');
	RangeAdapter aBlockTable('\t');
	RangeAdapter aAllChar(0,127);
#endif

	typedef DFAMachine<RangeAdapter,char> DFARange;
};


#endif