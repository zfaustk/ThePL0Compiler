#pragma once

#ifndef _KH_DFA_INTERFACE
#include "DFAMachine.h"
#endif

#ifndef _KH_DFA_DFAM_RANGE
#define _KH_DFA_DFAM_RANGE

namespace KH{

	//DFA_Range ÉùÃ÷
	KH::DFARange dMinus(KH::aMinus),	dPlus(KH::aPlus),		dTimes(KH::aTimes),		dSlash(KH::aSlash),
				 dLParen(KH::aLParen),	dRParen(KH::aRParen),	dLAngle(KH::aLAngle),	dRAngle(KH::aRAngle),
				 dLBigParen(KH::aLBigParen),					dRBigParen(KH::aRBigParen),
				 dLSquareParen(KH::aLSquareParen),				dRSquareParen(KH::aRSquareParen),
				 dExclamation(KH::aExclamation),
				 dPeriod(KH::aPeriod),
				 dComma(KH::aComma),
				 dColon(KH::aColon),
				 dSemiColon(KH::aSemicolon),
				 dQuote(KH::aQuote),
				 dAssignNorm(KH::aEqual)
				 ;

	KH::DFARange dEqual(3,1,2);
	KH::DFARange dIdencital(4,1,3);
	KH::DFARange dLEqual(3,1,2);
	KH::DFARange dREqual(3,1,2);
	KH::DFARange dAssign(3,1,2);
	KH::DFARange dBlock(2,1,1);
	KH::DFARange dIdentifier(2,1,1);
	KH::DFARange dString(3,1,2);
	KH::DFARange dFloat(3,1,2);
	KH::DFARange dInt(2,1,1);
	KH::DFARange dAnnotation(3,1,2);

	void DFAM_Range_Initial() { //³õÊ¼»¯

			dEqual	.AddTransition(0,1,1,KH::aEqual)	.AddTransition(1,2,1,KH::aEqual);

			dLEqual	.AddTransition(0,1,1,KH::aLAngle)	.AddTransition(1,2,1,KH::aEqual);

			dREqual	.AddTransition(0,1,1,KH::aRAngle)	.AddTransition(1,2,1,KH::aEqual);

			dIdencital.AddTransition(0,1,1,KH::aEqual)	.AddTransition(1,2,1,KH::aEqual) .AddTransition(2,3,1,KH::aEqual);

			dAssign	.AddTransition(0,1,1,KH::aColon)	.AddTransition(1,2,1,KH::aEqual);

			dBlock	.AddTransition(0,1,4,KH::aBlockEnter,KH::aBlockNewline,KH::aBlockSpace,KH::aBlockTable)
					.AddTransition(1,1,4,KH::aBlockEnter,KH::aBlockNewline,KH::aBlockSpace,KH::aBlockTable);

			dIdentifier	.AddTransition(0,1,3,KH::aUpper,KH::aLower,KH::aUnderline) 
						.AddTransition(1,1,4,KH::aDigit,KH::aUpper,KH::aLower,KH::aUnderline);

			dString	.AddTransition(0,1,1,KH::aQuote) 
					.AddTransition(1,1,2,KH::RangeAdapter(0,'"'-1),KH::RangeAdapter('"'+1,127))
					.AddTransition(1,2,1,KH::aQuote);

			dInt	.AddTransition(0,1,1,KH::aDigit) .AddTransition(1,1,1,KH::aDigit);

			dFloat	.AddTransition(0,1,1,KH::aDigit) .AddTransition(1,1,1,KH::aDigit) 
						.AddTransition(1,2,1,KH::aPeriod) .AddTransition(2,2,1,KH::aDigit);

			dAnnotation	.AddTransition(0,1,1,KH::aSlash).AddTransition(1,2,1,KH::aSlash)
								.AddTransition(2,2,1,KH::aAllChar);

	};

	

};

#endif



	////DFA
	//KH::DFARange dMinus(KH::aMinus),	dPlus(KH::aPlus),	dTimes(KH::aTimes),		dSlash(KH::aSlash),
	//			 dLParen(KH::aLParen),
	//			 dRParen(KH::aRParen),
	//			 dPeriod(KH::aPeriod),
	//			 dComma(KH::aComma),
	//			 dColon(KH::aColon),
	//			 dSemiColon(KH::aSemicolon),
	//			 dQuote(KH::aQuote),
	//			 dAssignNorm(KH::aEqual)
	//			 /*dASD(KH::RangeAdapter('`'))*/
	//			 ;

	//KH::DFARange dEqual(3,1,2);
	//			dEqual	.AddTransition(0,1,1,KH::aEqual)	.AddTransition(1,2,1,KH::aEqual);

	//KH::DFARange dIdencital(4,1,3);
	//			 dIdencital	.AddTransition(0,1,1,KH::aEqual).AddTransition(1,2,1,KH::aEqual).AddTransition(2,3,1,KH::aEqual);

	//KH::DFARange dAssign(3,1,2);
	//			 dAssign	.AddTransition(0,1,1,KH::aColon)	.AddTransition(1,2,1,KH::aEqual);

	//KH::DFARange dBlock(2,1,1);
	//			 dBlock	.AddTransition(0,1,4,KH::aBlockEnter,KH::aBlockNewline,KH::aBlockSpace,KH::aBlockTable)
	//						.AddTransition(1,1,4,KH::aBlockEnter,KH::aBlockNewline,KH::aBlockSpace,KH::aBlockTable);

	//KH::DFARange dIdentifier(2,1,1);
	//			 dIdentifier	.AddTransition(0,1,3,KH::aUpper,KH::aLower,KH::aUnderline) 
	//							.AddTransition(1,1,3,KH::aDigit,KH::aUpper,KH::aLower,KH::aUnderline);

	//KH::DFARange dString(3,1,2);
	//			 dString	.AddTransition(0,1,1,KH::aQuote) .AddTransition(1,1,2,KH::RangeAdapter(0,'"'-1),KH::RangeAdapter('"'+1,127))
	//						.AddTransition(1,2,1,KH::aQuote);

	//KH::DFARange dFloat(3,1,2);
	//			 dFloat	.AddTransition(0,1,2,KH::aMinus,KH::aDigit) .AddTransition(1,1,2,KH::aDigit) 
	//					.AddTransition(1,2,1,KH::aPeriod) .AddTransition(2,2,1,KH::aDigit);

	//KH::DFARange dInt(2,1,1);
	//			 dInt	.AddTransition(0,1,2,KH::aMinus,KH::aDigit) .AddTransition(1,1,1,KH::aDigit);

	//KH::DFARange dAnnotation(3,1,2);
	//			 dAnnotation	.AddTransition(0,1,1,KH::aSlash).AddTransition(1,2,1,KH::aSlash)
	//							.AddTransition(2,2,1,KH::aAllChar);
				 //TAIR