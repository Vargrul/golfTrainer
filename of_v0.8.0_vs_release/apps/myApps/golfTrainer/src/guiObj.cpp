#include "guiObj.h"

guiObj::guiObj(void){
	position.setX(0.0f);
	position.setY(0.0f);
	position.setZ(0.0f);
	width, height = 0;
	image;
	videoSrc;
};
guiObj::guiObj(pos p,ofImage i){
	position = p;
	image = i;
	width = image.getWidth();
	height = image.getHeight();
	videoSrc;
	sourceType = IMAGE;
};
guiObj::guiObj(pos p,int w,int h,ofImage i){
	position = p;
	width = w;
	height = h;
	image = i;
	videoSrc;
	sourceType = IMAGE;
};
guiObj::guiObj(pos p,int w,int h,string s,sourceChooser sc){
	position = p;
	width = w;
	height = h;
	if(sc == VIDEO)	setVideo(s);
	else setImage(s);
	sourceType = sc;
};
guiObj::guiObj(string s,sourceChooser sc){
	width = image.getWidth();
	height = image.getHeight();
	position = pos(0.0f,0.0f,0.0f);
	if(sc == VIDEO)	setVideo(s);
	else setImage(s);
	sourceType = sc;
};
guiObj::guiObj(pos p,string s,sourceChooser sc){
	width = image.getWidth();
	height = image.getHeight();
	position = p;
	if(sc == VIDEO) setVideo(s);
	else setImage(s);
	sourceType = sc;
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
void guiObj::setImgFromPixels(ofPixels i){image.setFromPixels(i);};

void guiObj::setVideo(ofVideoPlayer i){videoSrc = i;};
void guiObj::setVideo(string s){
	videoSrc.loadMovie(s);
	height = videoSrc.getHeight();
	width = videoSrc.getWidth();
}
void guiObj::play(){videoSrc.play();};
void guiObj::nextFrame(){videoSrc.nextFrame();};
void guiObj::vidUpdate(){videoSrc.update();};
void guiObj::setFrame(int i){videoSrc.setFrame(i);};
int guiObj::getCurrentFrame(){return videoSrc.getCurrentFrame();};
ofPixels guiObj::getPixelsRef(){if(sourceType == VIDEO)return videoSrc.getPixelsRef();else return image.getPixelsRef();};
ofVideoPlayer guiObj::getVideo(){return videoSrc;};

void guiObj::draw(){
	if(sourceType == IMAGE)	image.draw(position.getX(),position.getY());
	else videoSrc.draw(position.getX(),position.getY());
};

bool guiObj::mouseCheck(int x, int y){
	if (x > position.getX() && x < position.getX() + getWidth()){
		if(y > position.getY() && y < position.getY() + getHeight()){
			return true;
		}
	}
	else return false;
};
