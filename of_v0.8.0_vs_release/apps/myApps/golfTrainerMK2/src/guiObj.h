#pragma once

#include "pos.h"
#include "testApp.h"

enum sourceChooser{IMAGE,VIDEO};

class guiObj
{
	pos position;
	int width, height;
	ofImage image;
	ofVideoPlayer videoSrc;
	sourceChooser sourceType;

public:
	guiObj(void);
	guiObj(pos p,ofImage i);
	guiObj(pos,int,int,ofImage);
	guiObj(pos,int,int,string,sourceChooser sc);
	guiObj(string s,sourceChooser sc);
	guiObj(pos p,string s,sourceChooser sc);

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
	void setImgFromPixels(ofPixels i);

	void setVideo(ofVideoPlayer i);
	void setVideo(string s);
	ofVideoPlayer getVideo();
	void play();
	void stop();
	void nextFrame();
	void vidUpdate();
	void setFrame(int i);
	int getCurrentFrame();
	ofPixels getPixelsRef();
	bool isFrameNew();

	void draw();
	bool mouseCheck(int x, int y);
};