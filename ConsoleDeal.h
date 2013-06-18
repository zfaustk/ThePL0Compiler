#pragma once
#ifndef _KH_LA_VIEW_CONSOLE
#define _KH_LA_VIEW_CONSOLE

#include<string>


namespace KH{

	std::string ConsoleDeal(std::string console)
	{
		
		int length = console.length();
		if(length>4){
			if(console[0] == ':' && console[1] == '(') {
				if(console[2] == 'r' && console[3] == ',') {
					int i = 4;
					for(; i < length; i ++) {
						if(console[i] == ')')
							break;
					}
					if(i <= length) {
						return "fr:" + console.substr(4,i-4);					
					}
				}
				else if(console[2] == 'c' && console[3] == 'l' && console[4] == ')') {
					return "cl:";
				}
				else if(console == ":(grammar)"){
					return "gm:";
				}
				else if(console == ":(if)"){
					return "if:";
				}
				else if(console == ":(while)"){
					return "wl:";
				}
				else if(console == ":(bk)"){
					return "bk:";
				}
				else if(console == ":(block)"){
					return "bk::";
				}
				else if(console == ":(proc)"){
					return "pr:";
				}
				else if(console == ":(line)"){
					return "ln:";
				}
				else if(console[2] == 'j' && console[3] == 'm' && console[4] == 'p') {
					int i = 6;
					for(; i < length; i ++) {
						if(console[i] == ')')
							break;
					}
					if(i <= length) {
						return "jp:" + console.substr(6,i-6);					
					}
				}
				else if(console[2] == 'c' && console[3] == ','){
					int i = 4;
					for(; i < length; i ++) {
						if(console[i] == ')')
							break;
					}
					if(i <= length) {
						return "cm:" + console.substr(4,i-4);					
					}
				}
				else if(console[2] == 's' && console[3] == ','){
					int i = 4;
					for(; i < length; i ++) {
						if(console[i] == ')')
							break;
					}
					if(i <= length) {
						return "sv:" + console.substr(4,i-4);					
					}
				}
			}
		}
		return "";
	}//ConsoleDeal

};//end of namespace

#endif
