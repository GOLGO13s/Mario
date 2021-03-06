#pragma once

#include<map>
#include<vector>
#include"VECTOR2.h"


class ImageMng
{
private:
	ImageMng() {}
	ImageMng(const ImageMng&) {}
	ImageMng& operator=(const ImageMng&){}
	~ImageMng() {}

	//-----æo^pmapzñ
	std::map<std::string, int>imgMap;	//1æp
	std::map<std::string, std::vector<int>>imgDivMap;	//Aj[Vp



public:
	static ImageMng& GetInstance() {
		static ImageMng imgInst;
		return imgInst;
	}

	//o^
	//void SetID(std::string idName, std::string fileName);
	const int& SetID(std::string idName, std::string fileName);

	//o^(Aj[V)
	const std::vector<int>& SetID(std::string idName, std::string fileName, VECTOR2 divSize, VECTOR2 divNum);

	//`æ(1æ)
	void DrawImage(std::string idName, int x, int y, bool flag ,int lr);
	//void DrawImage(std::string idName, int x, int y,int lr, bool flag);

	//`æ(Aj[V)
	void DrawImage(std::string idName, int x, int y,int animNo, bool flag, int lr);

};