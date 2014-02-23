#include "guiObj.h"

guiObj::guiObj(void){
	position.setX, position.setY, position.setZ = 0.0f;
	width, height = 0.0f;
	image;
};

guiObj::guiObj(pos p,float w,float h,ofImage i){
	position = p;
	width = w;
	height = h;
	image = i;
};

void guiObj::setPos(pos p){position = p;};
pos guiObj::getPos(){return position;};

void guiObj::setSize(float w,float h){width = w;height = h;};
void guiObj::setWidth(float w){width = w;};
void guiObj::setHeight(float h){height = h;};
float guiObj::getWidth(){return width;};
float guiObj::getHeight(){return height;};

void guiObj::setImage(ofImage i){image = i;};
ofImage guiObj::getImage(){return image;};
