#include<gl/glut.h>



#include <fstream>
#include <sstream> 

#include  <io.h>

#include "KH_DrawText.h"
#include "KH_TextList.h"

#include "LA_View.h"

#include "ConsoleDeal.h"
#include "Test.h"

#include "DFAM_Range.h"

#include "GrammarAnalysis.h"
#include "CodeGenerate.h"

//include windows.h first
#include <shellapi.h>
GLvoid init(GLvoid)
{
}

GLint Height		(0);
GLint Width			(0);
GLint LineHeight	(0x16);
GLint LineNum		(0);
GLint FontSize		(0x13);
GLint CenterHeight  (0);
GLint SignWidth		(0x0C);
char  SignCha		('>');

void ResetHeight(GLint H);
void FileInput(std::string path);
void Compile(std::string path);
void SaveCode(std::string path);
void ShowLineNumberNow(std::string front = "");
void WaitCommand(int time);

std::string MainString = "Kinghand: a";

KH::LA_View lav;
KH::TextList tl;
float r = .75,g = 0.99 ,b= 0.8;
int line = 1;
KH::GrammarPL0 gpl0(lav.GetLA());
int timeLine = 0;
int nSleep = 0;

void display(void)
{
	timeLine += 1;
	int length;
	lav.GetDrawer().SelectFont(FontSize,100,"Verdana");
	
	glClearColor(.0,.133,.251,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	lav.GetDrawer().SetColor(1.0, 1.0, 1.0);
	lav.ShowLine(tl.strConsole,5,5);

	lav.ShowLine(":" + lav.GetLineTokenType(tl.strConsole), Width - 150, 5, KH::LA_View::Colorf(1,1,1));
	//Addition
	lav.ShowLine(":" + tl.strEcho , Width - 150, 5 + LineHeight, KH::LA_View::Colorf(-.1,-.1,-1));

	//显示行
	lav.GetDrawer().SetColor(1,g,1);
	lav.GetDrawer().RasterPos( 0 , Height - CenterHeight );
	lav.GetDrawer()<<SignCha;

	//TODO: 利用TOKENLIST优化，但在同步的时候总会出错
	//length = lav.ShowLine(lav.GetPosLine(tl),SignWidth , Height - CenterHeight ,KH::LA_View::Colorf(0.0,0.0,0.0)); //
	length = lav.ShowLine(tl.GetString(),SignWidth , Height - CenterHeight ,KH::LA_View::Colorf(0.0,0.0,0.0)); //
	length = lav.ShowLine(tl.GetCloumeString(true),SignWidth , Height - CenterHeight ,KH::LA_View::Colorf(0.2,0.3,0.2));

	
	if( nSleep > 0 ){
		lav.GetDrawer().SetColor(.1,.1,.1);
		glRectf(0 ,Height - 5.0f, Width ,Height);
		lav.GetDrawer().SetColor(1,1,1);
		glRectf(0 ,Height - 5.0f, (30 - nSleep) * (Width/30) ,Height);
		lav.GetDrawer().SetColor(1,.5,.1);
		glRectf((31 - nSleep) * (Width/30) ,Height - 5.0f, (30 - nSleep) * (Width/30) ,Height);
		nSleep --;
	}
	
	//显示插入标记
	int widthSigned = SignWidth + lav.GetDrawer().GetTextLength(tl.GetCloumeString(true))- lav.GetDrawer().GetTextLength(" ");
	int widthWord = lav.GetDrawer().GetTextLength(tl.GetCloumeString())- lav.GetDrawer().GetTextLength(" ");
	lav.GetDrawer().SetColor(.5 + (timeLine%10) / 20.0, .5 + (timeLine%10) / 20.0,.6 + (timeLine%10) / 20.0);
	/*lav.GetDrawer().RasterPos(widthSigned,Height - CenterHeight);
	lav.GetDrawer()<<"|";*/
	glRectf(widthSigned - widthWord ,Height - CenterHeight - 3.5f, widthSigned ,Height - CenterHeight - 2.0f);
	
	

	KH::TextList::iterator itUp = tl.now();
	for(int i = 1; i * LineHeight < CenterHeight; i++){
		if(itUp == tl.begin())break;
		else itUp--;
		lav.ShowLine(tl.GetString(itUp),SignWidth , Height - CenterHeight + i * LineHeight ,KH::LA_View::Colorf(-i*0.005,-i*0.001,-i*0.002));
	}
	itUp = tl.now();
	for(int i = 1; i * LineHeight < CenterHeight; i++){
		if(itUp == tl.end())break;
		else itUp++;
		if(itUp == tl.end())break;

		lav.ShowLine(tl.GetString(itUp),SignWidth , Height - CenterHeight - i * LineHeight ,KH::LA_View::Colorf(-i*0.005,-i*0.001,-i*0.002));
	}

	glFlush();

	glutSwapBuffers();
}

void reshape(const int width, const int height)
{
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	ResetHeight(height);
	Width = width;

	
}

void processTimeFunc(int p = 5000){
	if(timeLine < 10000)
		timeLine += 1;
	glutPostRedisplay();
	glutTimerFunc( p , processTimeFunc , p );
}

void processSpecialKeys(int key,int x,int y)
{
	int mod = glutGetModifiers(); 
    switch(key){
	case GLUT_KEY_F1             :
		ShowLineNumberNow();
		break;
	case GLUT_KEY_F2             :break;
	case GLUT_KEY_F3             :break;
	case GLUT_KEY_F4             :break;
	case GLUT_KEY_F5             :break;
	case GLUT_KEY_F6             :break;
	case GLUT_KEY_F7             :break;
	case GLUT_KEY_F8             :break;
	case GLUT_KEY_F9             :break;
	case GLUT_KEY_F10            :break;
	case GLUT_KEY_F11            :break;  
	case GLUT_KEY_F12            :break;  
	case GLUT_KEY_LEFT           :
		if(mod == GLUT_ACTIVE_CTRL) tl.strConsole = ":(";
		else tl.handleMoveLeft();
		break; 
	case GLUT_KEY_RIGHT          :
		if(mod == GLUT_ACTIVE_CTRL) tl.strConsole += ")";
		else tl.handleMoveRight();
		break; 
	case GLUT_KEY_UP             :
		if (mod == (GLUT_ACTIVE_CTRL)){
			tl.strConsoleLast();
		}
		else if (mod == (GLUT_ACTIVE_ALT)){
			tl.handleMoveTop();
			//lav.GetTKL().handleMoveTop();
		}
		else if (mod == (GLUT_ACTIVE_SHIFT)){
			tl.handleMoveUp(10);
			//lav.GetTKL().handleMoveUp(10);
		}
		else 
		{
			tl.handleMoveUp();
			//lav.GetTKL().handleMoveUp();
		}
		tl.strEcho = "";
		break; 
	case GLUT_KEY_DOWN           :
		if (mod == (GLUT_ACTIVE_CTRL)){
			tl.strConsoleNext();
		}
		else if (mod == (GLUT_ACTIVE_ALT)){
			tl.handleMoveButton();
			//lav.GetTKL().handleMoveButton();
		}
		else if (mod == (GLUT_ACTIVE_SHIFT)){
			tl.handleMoveDown(10);
			//lav.GetTKL().handleMoveDown(10);
		}
		else
		{
			tl.handleMoveDown();
			//lav.GetTKL().handleMoveDown();
		}
		tl.strEcho = "";
		break; 
	case GLUT_KEY_PAGE_UP        :
		LineHeight += 1;
		FontSize += 1;
		SignWidth = lav.GetDrawer().GetTextLength(">");
		break; 
	case GLUT_KEY_PAGE_DOWN      :
		LineHeight -= 1;
		FontSize -= 1;
		SignWidth = lav.GetDrawer().GetTextLength(">");
		break; 
	case GLUT_KEY_HOME           :break; 
	case GLUT_KEY_END            :break; 
	case GLUT_KEY_INSERT         :break; 
	default:	break;
	}
	glutPostRedisplay();
} 

void processNormalKeys(unsigned char key,int x,int y) 
{ 
	int mod = glutGetModifiers(); 
	switch(key){
	case 8: //backspace
		
		if(tl.strConsole.empty()) {
			tl.EraseString();
			lav.GetTKL().Change(tl);
		}
		else
			tl.strConsole.pop_back();
		
		break;
	case 9: // table
		tl.InsertString("\t ") ;break;
	case 32: //space
		tl.InsertString(tl.strConsole + " ") ; tl.strConsole = ""; lav.GetTKL().Change(tl); break;
	case 13: //enter
		if(!tl.strConsole.empty()){
			std::string s = KH::ConsoleDeal(tl.strConsole);
			if(s.length()>3 && s.substr(0,3) == "fr:") {
				if(_access( (s.substr(3,s.length()-3) + ".pl0").c_str(), 0 ) != -1) {
					WaitCommand(10);
					FileInput(s.substr(3,s.length()-3));
					tl.strEcho = "Read " + s.substr(3,s.length()-3) + " complete .";
				}
				else {
					tl.strEcho = "Read file failed ." ;
				}
			}
			else if(s == "cl:") tl.Clear();
			else if(s == "ln:") {
				ShowLineNumberNow();
			}
			else if(s == "gm:"){
				gpl0.GetInput(tl);
				gpl0.ExertGrammar();
				WaitCommand(5);
				tl.strEcho = "Grammar complete .";
				std::cout<< "====\n" << gpl0.OutErrorString();
			}
			else if(s.length()>3 && s.substr(0,3) == "cm:") {
				gpl0.GetInput(tl);
				Compile(s.substr(3,s.length()-3));
				std::ofstream fos(s.substr(3,s.length()-3) + ".exe");//创建打开文件
				WaitCommand(26);
				if(!fos) tl.strEcho = "Compile failed .";
				else tl.strEcho = "Compile complete .";
			}
			else if(s.length()>3 && s.substr(0,3) == "sv:") {
				gpl0.GetInput(tl);
				SaveCode(s.substr(3,s.length()-3));
				WaitCommand(15);
				tl.strEcho = "Save complete .";
			}
			else if(s.length()>3 && s.substr(0,3) == "jp:") {
				std::istringstream wst(s.substr(3,s.length()-3)) ;
				int ntmp ;
				wst >> ntmp ;
				tl.handleMoveTop();
				tl.handleMoveDown(ntmp);
				ShowLineNumberNow("Jump to ");
			}
			else{
				tl.InsertString(tl.strConsole + " ");
				tl.InsertLine() ;
			}
			if(s != "")tl.strConsolePush();
		}
		else
		{
			tl.InsertLine() ;
		}
		//lav.GetTKL().Change(tl);
		tl.strConsole = "";
		break;
	case 27: //esc
		exit(0);break;
	default:
		tl.strConsole += key;
		tl.strEcho = "";
	}
	
	glutPostRedisplay();
} 


//Functions

void ResetHeight(GLint H) { 
	Height = H; 
	LineNum = Height / LineHeight; 
	CenterHeight =(LineHeight * (LineNum/2)) ;
}

void Compile(std::string path){
	std::ofstream fos(path + ".c");//创建打开文件
	if(!fos) return ;
	std::string str = PL0Generate(gpl0);
	fos << str ;
	
	ShellExecute(NULL,"open","cmd.exe",("/c Compile.bat " + path + ".c").c_str() ,NULL,SW_SHOWNORMAL);
}

void SaveCode(std::string path){
	std::ofstream fos(path + ".pl0");//创建打开文件
	if(!fos) return ;
	for(KH::TextList::iterator it = tl.begin() ; it != tl.end() ; it ++ ){
		if(!it->empty())
			fos<<tl.GetString(it)<<std::endl;
	}
}

void FileInput(std::string path){
	
	std::ifstream fin(path + ".pl0",std::ios::in);
	if(!fin)return;
	std::string strf;
	char buff[256];
	while(!fin.eof() ) {

		fin.getline(buff,256,'\n');
		
		//TODO: 排除其他情况

		strf = std::string(buff);
		tl.InsertLine(strf);
		
	}
	tl.handleMoveTop();
	int max = 10;
	while(tl.now()->size() < 2){
		tl.handleMoveDown();
		if(max-- < 0)
			break;
	}
}


//

void WaitCommand(int time){
	nSleep = time;
}

void ShowLineNumberNow(std::string front){
	char ss[256];
	std::sprintf(ss,"Line -> %d ", tl.LineNumber());
	tl.strEcho = front + std::string(ss);
}

//


int main(int argc, char *argv[])
{
	try{
		DoTest();
	}
	catch(int *){
	}
	
	KH::DFAM_Range_Initial();

	lav.GetLA() 
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_BLOCK,		KH::dBlock)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_IDENTIFIER,	KH::dIdentifier)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_STRING,		KH::dString)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_ANNOTATION,	KH::dAnnotation)

		.AddTair(KH::LexicalAnalysis::TYPEDEF::_MINUS,	KH::dMinus)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_PLUS,	KH::dPlus)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_TIMES,	KH::dTimes)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_SLASH,	KH::dSlash)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_PERIOD,	KH::dPeriod)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_COMMA,	KH::dComma)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_COLON,	KH::dColon)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_SEMICOLON,	KH::dSemiColon)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_LPAREN,	KH::dLParen)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_RPAREN,	KH::dRParen)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_LANGLE,	KH::dLAngle)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_RANGLE,	KH::dRAngle)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_LBIGPAREN,	KH::dLBigParen)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_RBIGPAREN,	KH::dRBigParen)
		
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_QUOTE,	KH::dQuote)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_EQUAL,	KH::dEqual)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_IDENCITAL,	KH::dIdencital)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_LEQUAL,	KH::dLEqual)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_REQUAL,	KH::dREqual)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_ASSIGN,	KH::dAssign)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_ASSIGN,	KH::dAssignNorm)

		.AddTair(KH::LexicalAnalysis::TYPEDEF::_INT,	KH::dInt)
		.AddTair(KH::LexicalAnalysis::TYPEDEF::_FLOAT,	KH::dFloat)
				;
	tl.Initial();
	lav.GetTKL().Initial(tl);

	//File input
	if(argc == 2){
		std::string strcommand = std::string(argv[1]);
		if(strcommand == "-h") { std::cout<< "Hello world ! \n Thanks for use ! \n"  ; return 0 ; }
		else { std::cout<< "Command error [" + strcommand + "] ;\nUse command [-h] to get more detales ; \n"  ; return 0 ; }
	}
	if(argc == 3)
	{
		std::string strcommand = std::string(argv[1]);
		std::string strvalue = std::string(argv[2]);

		if(strcommand == "-r") FileInput(strvalue);
		else if(strcommand == "-g"){ FileInput(strvalue); gpl0.GetInput(tl); gpl0.ExertGrammar(); std::cout<< "====\n" << gpl0.OutErrorString(); return 0; }
		else if(strcommand == "-c"){ FileInput(strvalue); gpl0.GetInput(tl); Compile(strvalue); return 0; }
		else { std::cout<< "Command error [" + strcommand + "] ;\nUse command [-h] to get more detales ; \n"  ; return 0 ; }
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow(argv[0]);
	
	//init();
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(500, processTimeFunc , 1);
	glutMainLoop();

	

	return 0;
}

//void renderScene(void)
//{
//          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//          glLoadIdentity();
//          glBegin(GL_TRIANGLES);
//          glVertex3f(-0.5,-0.5,0.0);
//          glVertex3f(0.5,0.0,0.0);
//          glVertex3f(0.0,0.5,0.0);
//          glEnd();
//          glutSwapBuffers();
//}
//
// 
//int main(int argc, char* argv[])
//{
//          glutInit(&argc, (char**) argv);
//          glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//          glutInitWindowPosition(100,100);
//          glutInitWindowSize(800,600);
//          glutCreateWindow("Hello OpenGL");
//          //glutDisplayFunc(renderScene);
//		  glutDisplayFunc(display);
//		  //glutReshapeFunc(reshape);
//
//          glutMainLoop();//enters the GLUT event processing loop.
//          return 0;
//}