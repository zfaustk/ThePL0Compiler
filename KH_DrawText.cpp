#include "KH_DrawText.h"
#include <sstream>
#include <gl/glut.h>


KH::TextDrawer::TextDrawer()
{}

void KH::TextDrawer::SetColor(float R, float G, float B)
{
	glColor3f(R, G, B);
}

void KH::TextDrawer::SetColor(Draw_color::Colorf c)
{
	glColor3f(c.r, c.g, c.b);
}

void KH::TextDrawer::RasterPos(const int & x, const int & y)
{
	
	glRasterPos2i(x, y);
	
	
}

void KH::TextDrawer::SelectFont(int size, int charset, const char* face = "Verdana") 
{ 
	fontName = std::string(face);
	fontSize = size;
	//创建指定字体 
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, 
							OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
							ANTIALIASED_QUALITY | CLEARTYPE_QUALITY , 
							DEFAULT_PITCH | FF_SWISS  , face
							); 
	//把创建的字体选入设备上下文,保存旧字体     
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont); 
}

void KH::TextDrawer::DrawEngString(const char* str) {     
	static int isFirstCall = 1;     
	static GLuint lists;     
	if( isFirstCall ) { 
		// 如果是第一次调用，执行初始化         
		// 为每一个ASCII字符产生一个显示列表         
		isFirstCall = 0;         // 申请MAX_CHAR个连续的显示列表编号         
		lists = glGenLists(_DRAW_MAX_CHAR);         // 把每个字符的绘制命令都装到对应的显示列表中         
		wglUseFontBitmaps(wglGetCurrentDC(), 0, _DRAW_MAX_CHAR, lists);     
	}     // 调用每个字符对应的显示列表，绘制每个字符     
	for(; *str!='\0'; ++str)        
		glCallList(lists + *str);
} 

void KH::TextDrawer::Out(const char * str)
{ 
	//DrawEngString(str);return;

	int len=0, i=0; wchar_t * wstring; 
	HDC hDC=wglGetCurrentDC(); 
	GLuint list=glGenLists( 1 ); //计算字符的个数 
								// 如果是双字节字符的（比如中文字符），两个字节才算一个字符     
								// 否则一个字节算一个字符 
	for( i=0; str[i]!='\0'; i++ ) {    //判断字符str[i]是否由两个字节组成    
		if( IsDBCSLeadByte( str[i] ))     
			i++;    
		len++; 
	} //将混合字符转化为宽字符 
	wstring=(wchar_t*)malloc((len+1)*sizeof(wchar_t)); 
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len ); 
	wstring[len]=L'\0'; //逐个输出字符 
	for( i=0; i<len; i++ ) {    
		wglUseFontBitmapsW( hDC, wstring[i], 1, list );    
		glCallList( list ); 
	} //资源回收 
	free( wstring ); 
	glDeleteLists( list, 1 ); 
}

KH::TextDrawer & KH::operator<<(KH::TextDrawer & glos, const char & ch)
{
	std::string str;
	str.push_back(ch);
	glos.Out(str.c_str());
	return glos;
}
KH::TextDrawer & KH::operator<<(KH::TextDrawer & glos, const std::string & str)
{
	glos.Out(str.c_str());
	return glos;
}
KH::TextDrawer & KH::operator<<(KH::TextDrawer & glos, const int & d)
{
	std::ostringstream ostr;
	ostr << d;
	glos << ostr.str();
	return glos;
}
KH::TextDrawer & KH::operator<<(KH::TextDrawer & glos, const float & f)
{
	std::ostringstream ostr;
	ostr << f;
	glos << ostr.str();
	return glos;
}

KH::TextDrawer & KH::operator<<(KH::TextDrawer & glos, const double & lf)
{
	std::ostringstream ostr;
	ostr << lf;
	glos << ostr.str();
	return glos;
}


