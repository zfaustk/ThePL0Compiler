#pragma once
#ifndef _KH_DFA
#define _KH_DFA

#include <vector>


namespace KH{
	
	//要用boost::shared_ptr吗？还是算了吧..

	template<class _Terminator, class _Adapter, class _State>
	class Transition{ //用于支持State的组件类，由内部逻辑填写
	public:
		_State* pNextState;
		_Adapter acceptedAdapter; //如果改成指针就不对了？？？
		
		Transition(_Adapter &a, _State *pNext){
			acceptedAdapter = a;
			pNextState = pNext ;
		}

		_State* operator+(_Terminator t){
			if(acceptedAdapter == t){
				return pNextState;
			}
			else return NULL;
		}
	};

	template<class _Adapter, class _Terminator>
	class State{ //用来表示状态的类
	public:
		typedef _Adapter Adapter;
		typedef _Terminator Terminator;
		std::vector<Transition<_Terminator,_Adapter,State>> transitions;

		~State(){
			transitions.swap(std::vector<Transition<_Terminator,_Adapter,State>>() );
		}

		State* operator+(_Terminator t){
			State* nextState;
			std::vector<Transition<_Terminator, Adapter, State>>::iterator it;
			if(!transitions.empty())
				it = transitions.begin();
			else
				return NULL;
			for(;it != transitions.end(); it++){
				nextState = *it + t;
				if(NULL != nextState) return nextState;
			}
			return NULL;
		}

		void AcceptTransition(_Adapter &a, State *pNext){ //接受转换的函数
			Transition<_Terminator,_Adapter,State> *pTAS = new Transition<_Terminator,_Adapter,State>(a,pNext);
			transitions.push_back(*pTAS); 
		}
	};

	template<class _Adapter, class _State>
	class DFA_Transition{ //用于输入转换函数的类
	public:
		typedef _Adapter Adapter;
		typedef _State State;
		DFA_Transition();
		DFA_Transition(State *pOrg, _Adapter &adapter, State *pNext) {
			this->pState = pOrg;
			this->adapter = adapter;
			this->pNextState = pNext;
		}

		void TransitionToState(){
			this->pState->AcceptTransition(adapter, pNextState);
		}

	private:
		_State *pState;
		_State *pNextState;
		_Adapter adapter;
	};

	template<class _Adapter,class _Terminator, class _State = State<_Adapter,_Terminator>>
	class DFA{ // DFA机主体
	public:
		typedef _Terminator Terminator;
		typedef _State State;
		typedef _Adapter Adapter;

		DFA() {
			pStates = new std::vector<_State>();
			pStates->push_back(_State());
			pStates->push_back(_State());
			pFinalStates = new std::vector<_State*>();
			pFinalStates->push_back(&(*pStates)[1]);
			AddTransition(0,0,_Adapter());
			pCurrentState = &(*pStates)[0];
		}

		DFA(_Adapter &a) {
			//pAdapterOnly = _Adapter(a);//单适配模式
			pStates = new std::vector<_State>();
			pStates->push_back(_State());
			pStates->push_back(_State());
			pFinalStates = new std::vector<_State*>();
			pFinalStates->push_back(&(*pStates)[1]);
			AddTransition(0,1,a);
			pCurrentState = &(*pStates)[0];
		}

		DFA(std::vector<_State> &sList, 
			//std::vector<_Adapter> &tList, 
			std::vector<_State*> &sListFinal, 
			std::vector<DFA_Transition<_Adapter,_State>> &transitions
			)
		{	//注意这里实际上都是引用指针，所以如果在外部释放掉，里头也会没有

			//pAdapterOnly = NULL;

			pCurrentState = &sList[0];
			pStates = &sList;
			//pTerminators = &tList;
			pFinalStates = &sListFinal;

			for(std::vector<DFA_Transition<_Adapter,_State>>::iterator it = transitions.begin(); it != transitions.end(); it ++) {
				it->TransitionToState();
			}//将所有输入的transition转移到state中

			transitions.swap(std::vector<DFA_Transition<_Adapter,_State>>() ); //清空输入的DFA_transition
		}

		//Get
		bool CheckTerminator(_Adapter a, _Terminator t) const {
			return a == t;
		}

		bool CheckFinal(){ //单适配模式中没有意义
			for(std::vector<_State*>::iterator iS = pFinalStates->begin(); iS != pFinalStates->end(); iS ++) {
				if(*iS == pCurrentState)return true;
			}
			return false;
		}

		bool CheckNULL(){
			return pCurrentState == NULL;
		}

		int CheckStateNum() const{
			return pStates->size();
		}

		_State* GetCurrentState() const {
			return pCurrentState;
		}

		//Push
		void AddTransition(int nState, int nNextState, _Adapter &adapter){//增加一个转换函数

			if(nState > (int)pStates->size() || nNextState > (int)pStates->size() ) {
				throw 0;
				return;
			}

			DFA_Transition<_Adapter,_State> trans( &(*pStates)[nState], adapter, &(*pStates)[nNextState] );
			trans.TransitionToState();
		}

		bool InputTerminator(_Terminator t) {
			//if(pAdapterOnly != NULL) { //单适配模式中，直接判断
			//	return *pAdapterOnly == t;
			//}

			if(pCurrentState != NULL){
				pCurrentState = *pCurrentState + t;
				return CheckFinal();
			}
			return false;
		};

		bool operator<<( _Terminator &t) {
			return InputTerminator(t);
		}

		void Reset() { 
			/*if(pAdapterOnly == NULL)*/
			pCurrentState = &(*pStates)[0]; 
		}

		/*~DFA() {
			free(pCurrentState);
			free(pStates);
			free(pFinalStates);
		}*/

	private:
		State*	pCurrentState;
		std::vector<_State>*		pStates;
		//std::vector<_Adapter>*	pTerminators;
		std::vector<_State*>*		pFinalStates;
		//_Adapter* pAdapterOnly; //不为NULL时，启用单适配模式
	};

};

#endif