#pragma once

#include "pos.h"
#include "testApp.h"

class guiObj
{
	pos position;
	float width, height;
	ofImage image;
public:
	guiObj(void);
	guiObj(pos,float,float,ofImage);

	void setPos(pos);
	pos getPos();

	void setSize(float,float);
	void setWidth(float);
	void setHeight(float);
	float getWidth();
	float getHeight();

	void setImage(ofImage);
	ofImage getImage();
};