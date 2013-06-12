PL0 Compiler ( for windows )
===================================    
 
	by kinghand ( zfaustk )

How to use  
-----------------------------------  
### settin
	first you should setting the path to ensure it contains the folder of cl (vs2010) .
		for example :
		D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin;	(for cl.exe)
		D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib;	(for lib)
		D:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;(for vcvarsall.bat)
		D:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include; (for lib)    

### Console
	1.	open cmd .
	2.	cd to the fold .
	3.	use ThePL0Compiler [command] [value] .
   	4.	[command]
		-r [file name] : open editor then read the file autoly .	
			example : >ThePL0Compiler -r test
		-g [file name] : check grammar of the file .
			example : >ThePL0Compiler -g test
		-c [file name] : compile the code file and generate an .exe file .
			example : >ThePL0Compiler -c test
		-h : get more infomation . 

	5.	the you will get the .exe file on the folder code where .
	
### Editor
	1.	double click ThePL0Compiler to exert the program .
	2.	try some input like hello world ! .
	3.	all character you typed will appear where the consloe is until the blank input.
	4.	if you type the blank(' ') the word you type will be infused to the code area where the cursor is , if the type is enter('\n') , it will creat a new line under the word infused . if the type is table('\t') , it will go directly to the code area . 
	5.	you can use "up" "down" "left" "right" to change the cursor's position .
	6.	you can use "pgUp" and "pgDn" to change the size of word .
	7.	there are some function key :
		F1 : show the line number where the cursor is .
		shift + up/down : 10 line up/down .
		alt   + up/down	: reseek to top/button .
		ctrl  + up/down	: last/next command.
		ctrl  + left/right :	input ":("/")" to console .
	8.	there are some command : the only legal format of command is like this :(type[,value])
		:(r,value)	read the file named value .
		:(s,value)	save codes to file value.pl0 .
		:(grammar)	check grammar .
		:(c,value)	compile the code .
		:(line)		show the line number .
		:(jmp,value)	jump tp line value .
		:(cl)		clear contents .

  