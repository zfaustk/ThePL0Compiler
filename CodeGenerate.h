#pragma once
#ifndef __KH_CODE_GENERATE
#define __KH_CODE_GENERATE

#include"GrammarAnalysis.h"
#include<stack>
std::string PL0Generate(KH::GrammarPL0 gpl0){
	
	std::stack<int> FindMain;

	std::string strOut = 
		"	\n//Compiler Powered By KingHand \n\
		\n#include <stdio.h> \
		\n\
		\ntypedef double var;\
		\n\
		"
		;

	std::vector<std::string>::iterator it;

	//函数声明
	for(it = gpl0.funcNames.begin() ; it != gpl0.funcNames.end() ; it ++ ){
		strOut += ("\n double " + *it + " (　) ; ") ;
	}

	//函数入口
	if(gpl0.ExertGrammar(true)){
		for(it = gpl0.sGens.begin() ; it != gpl0.sGens.end() ; it ++ )
		{
			if ( it->find("( )") != std::string::npos )
			{
				FindMain.push(0);
			}

			if ( it->find("{") != std::string::npos )
			{
				if(FindMain.empty()){
					strOut += ("\n main(int argc, char *argv[] ) " + *it + 
						"// Main \
						\n\
						\n\t if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h') {	\
						\n\t	printf(\" Welcome ! PL0 Compiler powered by Kinghand . \\n\");	\
						\n\t }	\
						"
						) ;
					FindMain.push(2);
					continue;
				}
				else FindMain.push(1);
				
			}
			
			if ( it->find("}") != std::string::npos ) 
			{
				if(FindMain.top() == 1)
					FindMain.pop();
				if(FindMain.top() == 0)
					FindMain.pop();
			}

			if(it->length() <= 1 || (*it) == " ; " || (*it) == " ( " || (*it) == " ) " || (*it) == " = " || it->length() <= 3 )  
			{
					strOut += *it;
					continue;
			}
			
			strOut += "\n" + *it ;
		}
	}

	strOut += 
		"	\n \
			\n \
			//Compiler Powered By KingHand \
		"
		;

	return strOut;
};





#endif