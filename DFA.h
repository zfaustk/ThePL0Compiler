#pragma once
#ifndef _KH_DFA
#define _KH_DFA

#include <vector>


namespace KH{
	
	template<class _Terminator, class _State>
	class Transition{ //用于支持State的组件类，由内部逻辑填写
	public:
		_State* pNextState;
		_Terminator acceptedTerminator;
		
		Transition(_Terminator t,_State *pNext){
			acceptedTerminator = t;
			pNextState = pNext ;
		}

		_State* operator+(_Terminator t){
			if(acceptedTerminator == t){
				return nextState;
			}
			else return NULL;
		}
	
	private:
		Transition();
	};

	template<class _Terminator>
	class State{ //用来表示状态的类
	public:

		typedef _Terminator Terminator;
		std::vector<Transition<_Terminator, State>> transitions;

		State(){
			bEnableTransition = false;
		}

		State* operator+(_Terminator t){
			std::vector<Transition<Termiantor, State>>::iterator it = transitions.begin();
			for(;it != transitions.end(); it++){
				return *it + t;
			}
		}

		void AcceptTransition(_Terminator t, State *pNext){ //接受转换的函数
			if(bEnableTransition) {
				Transition<_Terminator, State> *pTTS = new Transition<_Terminator, State>(t,pNext);
				transitions.push_back(*pTTS); 
			}
			else
				throw 0;
		}

		void Begin() { bEnableTransition = true ; transitions.clear() ; } 

		void End() { bEnableTransition = false ; } 

	private:

		bool bEnableTransition;
	};

	template<class _Terminator, class _State>
	class DFA_Transition{ //用于输入转换函数的类
	public:
		typedef _Terminator Terminator;
		typedef _State State;
		DFA_Transition();
		DFA_Transition(State *pOrg, Terminator terminator, State *pNext) {
			this->pState = org;
			this->terminator = terminator;
			this->pNextState = next;
		}

		void TransitionToState(){
			this->pState->AcceptTransition(terminator, pNextState);
		}

	private:
		_State *pState;
		_State *pNextState;
		_Terminator terminator;
	};

	template<class _Terminator, class _State = State<_Terminator>>
	class DFA{ // DFA机主体
	public:
		typedef _Terminator Terminator;
		typedef _State State;

		DFA(_State &sInit, 
			std::vector<_State> &sList, 
			std::vector<_Terminator> &tList, 
			std::vector<_State> &sListFinal, 
			std::vector<DFA_Transition<_Terminator,_State>> &transitions)
		{
			pCurrentState = pInitialState = &sInit;
			pStates = &sList;
			pTerminators = &tList;
			pFinalStates = &sListFinal;

			for(std::vector<DFA_Transition<_Terminator,_State>>::iterator it = transitions.begin(); it != transitions.end(); it ++) {
				it->TransitionToState();
			}//将所有输入的transition转移到state中

		}

		//Get
		bool CheckTerminator(_Terminator t) const;
		bool CheckFinal() const;
		_State GetCurrentState() const;

		//Push
		bool InputTerminator(_Terminator t);

	private:
		_State*	pInitialState;
		_State*	pCurrentState;
		std::vector<_State>*		pStates;
		std::vector<_Terminator>*	pTerminators;
		std::vector<_State>*		pFinalStates;
	};

};

#endif