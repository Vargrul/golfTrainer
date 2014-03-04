#pragma once

#include "pos.h"
#include "testApp.h"

class guiObj
{
	pos position;
	int width, height;
	ofImage image;
public:
	guiObj(void);
	guiObj(pos p,ofImage i);
	guiObj(pos,int,int,ofImage);
	guiObj(pos,int,int,string);
	guiObj(string s);
	guiObj(pos p,string s);

	void setPos(pos);
	pos getPos();

	void setSize(int,int);
	void setWidth(int);
	void setHeight(int);
	int getWidth();
	int getHeight();

	void setImage(ofImage);
	void setImage(string s);
	ofImage getImage();

	void draw();
	bool mouseCheck(int x, int y);
};