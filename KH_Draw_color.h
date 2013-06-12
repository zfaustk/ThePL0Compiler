#pragma once
#ifndef _KH_DRAW_COLOR
#define _KH_DRAW_COLOR

#include"iostream"
#include<map>

namespace KH{

	class Draw_color{
	public:
		typedef struct _Colorf{
					public:
						float r;
						float g;
						float b;
						_Colorf() { r = 1.f, g = 1.f, b = 1.f; }
						_Colorf(float rc,float gc,float bc){ r = rc; g = gc; b = bc; }
						_Colorf operator+(_Colorf c){	return _Colorf(r+c.r, g+c.g, b+c.b); }
					} Colorf;
		typedef std::map<int ,Colorf> Map;

		Draw_color() { }
		Draw_color(Colorf c) { cOrigin = c; }
		Draw_color(float rc,float gc,float bc) { cOrigin = _Colorf(rc,gc,bc); }

		void SetOrigin(Colorf c) {
			cOrigin = c;
		}

		Colorf GetTypeColor(int sign)  { //从int值获取类型的名字
			Map::iterator i = cMap.find(sign);
			if(i == cMap.end()) return cOrigin;
			else return cMap[sign];
		}

		Draw_color& AddColor(int sign, float r, float g, float b){ //加入一种颜色和标志的对
			Map::iterator i = cMap.find(sign);
			if(i != cMap.end())cMap.erase(i);
			if(r > 1)r = r / 255;
			if(g > 1)g = g / 255;
			if(b > 1)b = b / 255;
			cMap.insert( Map::value_type(sign, Colorf(r,g,b)) );
			return (*this);
		}

		Draw_color& AddColor(int signBegin, int signEnd, float r, float g, float b){ //加入一系列颜色和标志的对
			int min = 0 ,max = 0;
			min = (signBegin < signEnd )? signBegin : signEnd;
			max = signBegin + signEnd - min;
			while(max - min + 1) {
				AddColor(min++,r,g,b);
			}
			return (*this);
		}

		bool isEmpty(){ return cMap.empty(); }

		Colorf GetOrigin(){ return cOrigin; }

	private:
		Colorf	cOrigin;
		Map		cMap;
		

	};

};


#endif