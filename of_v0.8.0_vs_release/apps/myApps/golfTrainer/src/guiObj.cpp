#include "guiObj.h"

guiObj::guiObj(void){
	position.setX(0.0f);
	position.setY(0.0f);
	position.setZ(0.0f);
	width, height = 0;
	image;
};
guiObj::guiObj(pos p,ofImage i){
	position = p;
	image = i;
	width = image.getWidth();
	height = image.getHeight();
};
guiObj::guiObj(pos p,int w,int h,ofImage i){
	position = p;
	width = w;
	height = h;
	image = i;
};
guiObj::guiObj(pos p,int w,int h,string s){
	position = p;
	width = w;
	height = h;
	image.loadImage(s);
};
guiObj::guiObj(string s){
	setImage(s);
	width = image.getWidth();
	height = image.getHeight();
	position = pos(0.0f,0.0f,0.0f);
};
guiObj::guiObj(pos p,string s){
	setImage(s);
	width = image.getWidth();
	height = image.getHeight();
	position = p;
};

void guiObj::setPos(pos p){position = p;};
pos guiObj::getPos(){return position;};

void guiObj::setSize(int w,int h){width = w;height = h;};
void guiObj::setWidth(int w){width = w;};
void guiObj::setHeight(int h){height = h;};
int guiObj::getWidth(){return width;};
int guiObj::getHeight(){return height;};

void guiObj::setImage(ofImage i){image = i;};
void guiObj::setImage(string s){
	image.loadImage(s);
	height = image.getHeight();
	width = image.getWidth();
};
ofImage guiObj::getImage(){return image;};

void guiObj::draw(){
	image.draw(position.getX(),position.getY());
};
