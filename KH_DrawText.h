#pragma once 
#ifndef _KH_DRAW_TEXT
#define _KH_DRAW_TEXT

#define _AFXDLL

#include <stdlib.h>
#include <string>
#include <afxwin.h>
#include <Windows.h>
#include "GdiPlus.h"
#include "GdiplusBase.h"
#include "GdiPlusPath.h"
#include "KH_Draw_color.h"

namespace KH 
{
	const int _DRAW_MAX_CHAR = 128 ;

	class TextDrawer{
	public:
		TextDrawer();
		void RasterPos(const int & X, const int & Y);	//设定位置
		void SelectFont(int Size, int, const char* FontName);		//设定字体
		void SelectFont(int size, std::string FontName);
		void SetColor(float R, float G, float B);
		void SetColor(Draw_color::Colorf c);
		void Out(const char *);					//输出字符串
		void DrawEngString(const char*);		//只绘出英文
		int GetTextLength(std::string str){
			wchar_t w;
			HDC hDC = wglGetCurrentDC();
			// 转化为宽字符
			int count = 0;
			if(!str.empty()){
				std::string::iterator i = str.begin();
				for(;i!=str.end();i++){
					MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, &(*i), 2, &w, 1);
					int width;
					GetCharWidth32W(hDC, w, w, &width);    // 取得字符的宽度
					count += width;
				}
			}
			return count;
		}

		friend TextDrawer& operator<<(TextDrawer &, const char &);
		friend TextDrawer& operator<<(TextDrawer &, const std::string &);
		friend TextDrawer& operator<<(TextDrawer &, const int &);
		friend TextDrawer& operator<<(TextDrawer &, const float &);
		friend TextDrawer& operator<<(TextDrawer &, const double &);

	private:
		TextDrawer(const TextDrawer &);
		TextDrawer & operator =(const TextDrawer &);
		std::string fontName;
		int  fontSize;
	};	
};

#endif