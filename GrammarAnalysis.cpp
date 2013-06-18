#define _KH_DFA_INTERFACE_ADAPTER
#include "GrammarAnalysis.h"
#undef _KH_DFA_INTERFACE_ADAPTER


//程序语法判断
bool KH::GrammarPL0::ExertGrammar(bool isGen){
	bool result = true;
	this->Reset(false);

	if(isGen){
		IsGenerate = isGen;
		sGens.clear();
		funcNames.clear();
	}

	Sa.Reset();

	while(! this->CheckEnd()){
		if(! Block()) //TODO:第五行出错（var）
			result = false;
	}

	return result;
}

bool KH::GrammarPL0::GrammarSign(KH::GrammarPL0::Token t,const int sign) {
	bool result = true;
	if(t == KH::GrammarPL0::Token()){
		Error(result, " UnDefined Word !");
		return false;
	}
	else if(t.GetSign() == sign)return true;
	return false;
}

void KH::GrammarPL0::Error(bool &result, std::string message, bool skipit){

	InsertError(KH::GrammarPL0::ErrorType( GetLine(),": " + message) );
	if(skipit) skip(1);
	result = false;

}

//分程序语法判断
bool KH::GrammarPL0::Block(){
	bool result = true;

	if( GetWord(false).GetSign() == KH::_BLOCK) skip(1); //自然会跳过所有的block
	if( CheckEnd()) {
		Error( result, " Empty Input ! " );
		return false;
	}

	if( GetWord(false).GetSign() == KH::_CONST){
		 skip(1);
		if( GetWord(false).GetSign() == KH::_IDENTIFIER){
			if(	 GetWord(1,false).GetSign() == KH::_ASSIGN &&
				 GetWord(2,false).GetSign() == KH::_INT ||
				 GetWord(2,false).GetSign() == KH::_FLOAT 
				) 
			{
				Sa.PushVariable(GetLine(),GetWord(false).GetValue());

				//Gen  int a = 11
				if(GetWord(2,false).GetSign() == KH::_INT)
					GenPush("const int " + GetWord(false).GetValue() + " = " + GetWord(2,false).GetValue() + "; " );
				else
					GenPush("const float " + GetWord(false).GetValue() + " = " + GetWord(2,false).GetValue() + "; " );
				
				 skip(3,false);
				while( GetWord(false).GetSign() == KH::_COMMA){
					if(	 GetWord(1,false).GetSign() == KH::_IDENTIFIER &&
						 GetWord(2,false).GetSign() == KH::_ASSIGN &&
						 GetWord(3,false).GetSign() == KH::_INT ||
						 GetWord(3,false).GetSign() == KH::_FLOAT 
						)
					{
						Sa.PushVariable(GetLine(),GetWord(1,false).GetValue());

						//Gen  , int a = 11
						if(GetWord(3,false).GetSign() == KH::_INT)
							GenPush("const int " + GetWord(1,false).GetValue() + " = " + GetWord(3,false).GetValue() + "; " );
						else
							GenPush("const float " + GetWord(1,false).GetValue() + " = " + GetWord(3,false).GetValue() + "; " );

						 skip(4,false);
					}
					else
					{
						Error( result, " Const Loop Error : " + GetWord(false).GetValue() + GetWord(1,false).GetValue() + GetWord(2,false).GetValue() + GetWord(3,false).GetValue() );
						break;
					}
				}
				if( GetWord(false) == KH::_SEMICOLON)
					 skip(1);
				else{
					Error( result, " Const Not End : " + GetWord(false).GetValue() );
				}
			}
			else
			{
				Error( result, " Const sentence Error : " + GetWord(false).GetValue() );
			}

		}
		else
		{
			Error( result, " Const Identifier Error : " + GetWord(false).GetValue() + GetWord(1,false).GetValue() + GetWord(2,false).GetValue() );
		}
	}//End of if const ;

	if( GetWord(false).GetSign() == KH::_VAR)//如果单词是"var"
	{
		 skip(1);//取下一个单词
		if( GetWord(false).GetSign() == KH::_IDENTIFIER){
			Sa.PushVariable(GetLine(),GetWord(false).GetValue());

			//Gen  var a
			GenPush("double " + GetWord(false).GetValue() + " = 0 ; " );
			 skip(1);
			while( GetWord(false).GetSign() == KH::_COMMA){
				if(	 GetWord(1,false).GetSign() == KH::_IDENTIFIER )
				{
					Sa.PushVariable(GetLine(),GetWord(1,false).GetValue());

					//Gen  var .. , a
					GenPush("double " + GetWord(1,false).GetValue() + " = 0 ; " );
					 skip(2);
				}
				else
				{
					Error( result," Var Loop Error : " + GetWord(false).GetValue() + GetWord(1,false).GetValue());
					break;
				}
			}
			if( GetWord(false).GetSign() == KH::_SEMICOLON){
				 skip(1);
			}
			else 
			{
				Error( result," Var Not End : " + GetWord(false).GetValue() );
			}
		}
		else
		{
			Error( result," Var Identifier Error : " + GetWord(false).GetValue() );
		}
	}//End of if var

	while ( GetWord(false).GetSign() == KH::_PROC)//如果单词是"procedure",则进入"函数定义"语法分析
	{
		 skip(1);
		if(	 GetWord(false).GetSign() == KH::_IDENTIFIER && 
			 GetWord(1,false).GetSign() == KH::_SEMICOLON)//"procedure"后应为标识符
		{
			Sa.PushVariable(GetLine(),GetWord(false).GetValue());

			//Gen  var .. , a
				GenPush("double " + GetWord(false).GetValue() + "( ) { " ); //注意闭合！
				funcNames.push_back(GetWord(false).GetValue());

			 skip(2);
			 Block();

			 //Gen  var .. , a
			 GenPush(" return 0 ; } " ); //注意闭合！

		}
		else{
			Error( result," Proc define Error : " + GetWord(false).GetValue() + GetWord(1,false).GetValue() ) ;
		}
	}//End of if procedure

	if(!StatementParsing()){
		Error( result," Parsing Error . " );
	}//End of if Parsing

	return result;
}

//条件
bool KH::GrammarPL0::ConditionParsing()//nIndentNum是打印时要缩进的空格数
{
	bool result = true;

	if( GetWord(false).GetSign() == KH::_ODD)//如果有"odd"单词
	{
		//Gen  if (
				GenPush("( "); //注意闭合！

		 skip(1);
		if(! ExpressionParsing()) {
			Error( result," Condition Parsing Error , There should be a Expression .");
		}

		//Gen  if .. )
				GenPush(" ) "); //注意闭合！
	}
	else
	{
		//Gen  if (
				GenPush(" ( "); //注意闭合！

		if(! ExpressionParsing()) {
			Error( result," Condition Parsing Error , There should be a Expression .");
		}
		if(		 GetWord(false).GetSign() == KH::_EQUAL	//如果后面有逻辑运算符
			||	 GetWord(false).GetSign() == KH::_NEQUAL
			||	 GetWord(false).GetSign() == KH::_LANGLE
			||	 GetWord(false).GetSign() == KH::_LEQUAL
			||	 GetWord(false).GetSign() == KH::_RANGLE
			||	 GetWord(false).GetSign() == KH::_REQUAL)
		{
			//Gen  if ( == )
				GenPush(GetWord(false).GetValue()); //注意闭合！

			 skip(1);
			if(! ExpressionParsing()) {
				Error( result," Condition Parsing Error , There should be a Expression .");
			}
		}
		else
		{
			Error( result," Condition Parsing Error , Logic Error : " + GetWord(false).GetValue());
		}

		//Gen  if .. )
			GenPush(" ) "); //注意闭合！
	}
	return result;
}

//"表达式"语法分析
bool KH::GrammarPL0::ExpressionParsing()//nIndentNum是打印时要缩进的空格数
{
	bool result = true;

	if( GetWord(false).GetSign() == KH::_PLUS ||  GetWord(false).GetSign() == KH::_MINUS)
	{//如果开头有正负号,则此时表达式应被看作一个正的或负的项

		//Gen  +-
			GenPush(GetWord(false).GetValue());

		 skip(1);
	}

	if( TermParsing() )//表达式可以是一个"项"
	{
		while( GetWord(false).GetSign() == KH::_PLUS ||  GetWord(false).GetSign() == KH::_MINUS)
		{	
			//Gen  +-
			GenPush(GetWord(false).GetValue());

			 skip(1);
			if( !TermParsing() ){
				Error( result," Expression Parsing Error , There should be a Term ." );
			}
		}
	}
	else 
	{
		Error( result," Expression Parsing Error , There should be a Term .");
	}

	return result;
}

//"项"语法分析
bool KH::GrammarPL0::TermParsing()//nIndentNum是打印时要缩进的空格数
{
	bool result = true;

	if(! FactorParsing()){
		Error( result," Term Parsing Error , There should be a Factor .");
	}

	while( GetWord(false).GetSign() == KH::_TIMES ||  GetWord(false).GetSign() == KH::_SLASH)
	{//如果"因子"后面还有单词'*'或'/'
		//Gen  */
			GenPush(GetWord(false).GetValue());
		 skip(1);
		if(!FactorParsing()){
			Error( result," Term Parsing Error , There should be a Factor .");
		}
	}

	return result;
}

//"因子"语法分析
bool KH::GrammarPL0::FactorParsing()
{
	bool result = true;

	switch( GetWord(false).GetSign())
	{
		case KH::_IDENTIFIER://因子可以是一个常量或变量
			Sa.ExistVariable(GetLine(),GetWord(false).GetValue());

			//Gen  ident
			GenPush(GetWord(false).GetValue());
			 skip(1);
			break;

		case KH::_INT:	//因子可以是一个数
		case KH::_FLOAT:
			//Gen  ident
			GenPush(GetWord(false).GetValue());
			 skip(1);
			break;

		case KH::_LPAREN :	//如果看到左括号'('
			//Gen (
			GenPush(" ( ");
			 skip(1);

			if(!ExpressionParsing())
			{
				Error( result," Factor Error , There should be a Expression .");
			}

			if( GetWord(false).GetSign() == KH::_RPAREN)//"表达式"后面应是右括号')'
			{
				//Gen )
				GenPush(" ) ");
				 skip(1);
			}
			else{
				Error( result," Factor Error , There should be a Right Paren : " + GetWord(false).GetValue());
			}

			break;

		default:	
			Error( result," Factor Error , There should be a Factor .");
			break;
	}//End of switch
	return result;
}

bool KH::GrammarPL0::StatementParsing(){

	bool result = true;

	switch( GetWord(false).GetSign()){
		case KH::_IDENTIFIER: //Identifire
			Sa.ExistVariable(GetLine(),GetWord(false).GetValue());

			//Gen a = ..
			GenPush(GetWord(false).GetValue() + " = ");//注意闭合

			 skip(1);
			if( GetWord(0,false).GetSign() == KH::_ASSIGN){
				//Gen )
				 skip(1);
				if(!ExpressionParsing())
					Error( result," Statement Error , There should be a Expression .");
			}
			else{
				Error( result," Statement Error , Assign required : " + GetWord(false).GetValue());
			}

			//Gen a = .. ;
			GenPush(" ; ");//注意闭合

			break;
		case KH::_CALL:	//Call
			 skip(1);
			if( GetWord(0,false).GetSign() == KH::_IDENTIFIER){
				Sa.ExistVariable(GetLine(),GetWord(false).GetValue());

				//Gen a();
				GenPush(GetWord(false).GetValue() + " () ;");
				 skip(1);
			}
			else{
				Error( result," Statement Error , Identifier required : " + GetWord(false).GetValue());
			}
			break;
		case KH::_LBIGPAREN: //Begin
		case KH::_BEGIN:
			 skip(1);
			 //Gen { 
			GenPush(" { ");//注意闭合
			if(Block()){
				while( GetWord(0,false).GetSign() == KH::_SEMICOLON){
					//Gen ;
						GenPush(";");
					skip(1);
					if(GetWord(0,false).GetSign() == KH::_END || GetWord(0,false).GetSign() == KH::_RBIGPAREN) {
						break;
					}
					if(!StatementParsing())
						Error( result," Statement Error , Statement required .");
				}

				if(	 GetWord(0,false).GetSign() == KH::_RBIGPAREN || 
					 GetWord(0,false).GetSign() == KH::_END)
				{
					//Gen }
						GenPush(" } ");//注意闭合
					 skip(1);
				}
				else
					Error( result," Statement Error , 'end' or '}' required : " + GetWord(false).GetValue() );
			}
			else{
				Error( result," Statement Error , Statement required .");
			}

			break;
		case KH::_IF:
			//Gen if
				GenPush(" if ");
			 skip(1);
			if( ConditionParsing()){
				 //skip(1);
				if( GetWord(0,false).GetSign() == KH::_THEN){
					//Gen if .. { }
					GenPush(" { ");
					 skip(1);
					if(!StatementParsing())
						Error( result," Statement Error , Statement required .");
					//Gen if .. { }
					GenPush(" } ");
				}
				else{
					Error( result," Statement Error , 'Then' required : " + GetWord(false).GetValue());
				}
			}
			else{
				Error( result," Statement Error , Condition required .");
			}
			break;
		case KH::_WHILE:
			//Gen while
				GenPush(" while ");
			 skip(1);
			if( ConditionParsing()){
				if( GetWord(0,false).GetSign() == KH::_DO){
					//Gen while .. {}
					GenPush(" { ");

					 skip(1);
					if(!StatementParsing())
						Error( result," Statement Error , Statement required .");

					//Gen while .. {}
					GenPush(" } ");
				}
				else{
					Error( result," Statement Error , 'Do' required : " + GetWord(false).GetValue());
				}
			}
			else{
				Error( result," Statement Error , Condition required .");
			}
			break;
		case KH::_READ:
			 skip(1);
			if( GetWord(0,false).GetSign() == KH::_LPAREN &&  GetWord(1,false).GetSign() == KH::_IDENTIFIER){
				Sa.ExistVariable(GetLine(),GetWord(1,false).GetValue());
				//Gen read
					GenPush(" scanf(\"%lf\" , &" + GetWord(1,false).GetValue() + ") ;");
				 skip(2);
				 while( GetWord(0,false).GetSign() == KH::_COMMA){
					 skip(1);
					if( GetWord(0,false).GetSign() == KH::_IDENTIFIER){
						Sa.ExistVariable(GetLine(),GetWord(false).GetValue());
						//Gen read
							GenPush(" scanf(\"%lf\" , &" + GetWord(0,false).GetValue() + ") ;");
						 skip(1);
					}
					else Error( result," Statement Error , Identifire required : " + GetWord(false).GetValue());
				}

				if(	 GetWord(0,false).GetSign() == KH::_RPAREN )
				{
					 skip(1);
				}
				else
					Error( result," Statement Error , ')' required : " + GetWord(false).GetValue());
			}
			else{
				Error( result," Statement Error , Identifire required : " + GetWord(false).GetValue());
			}
			break;
		case KH::_WRITE:
			 skip(1);
			if( GetWord(0).GetSign() == KH::_LPAREN ){
				//Gen write(.. 
					GenPush(" printf(\"%lf \\n \" , ");
				 skip(1);
				if(ExpressionParsing()){
					//Gen write .. a .. 
					GenPush(" ) ;");
					while( GetWord(0,false).GetSign() == KH::_COMMA){
						//Gen write .. ,
							GenPush(" printf(\"%lf \\n \" , ");
						 skip(1);
						if(!ExpressionParsing())
							Error( result," Statement Error , 【Expression required】 .");
						//Gen write .. ,
							GenPush(" ) ; ");
					}
				}
				else
				{
					Error( result," Statement Error , 【First Expression required】 .");
				}

				if(	 GetWord(0,false).GetSign() == KH::_RPAREN )
				{
					 skip(1);
				}
				else
					Error( result," Statement Error , 【Right Paren required】 .");
			}
			else{
				Error( result," Statement Error , 【Left Paren required】 .");
			}
			break;
		case KH::_SEMICOLON:
			 skip(1);
			break;
		default:
			Error( result," Statement Error , 【Unexpected word " + GetWord(0,false).GetValue() + "】 .",false);
			break;
	}

	return result;

}