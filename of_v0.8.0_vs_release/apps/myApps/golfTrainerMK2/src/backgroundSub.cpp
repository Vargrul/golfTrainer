#include "backgroundSub.h"

ofImage gt_averageBackground(vector<ofImage> frames){
	int imgWidth = frames[0].getWidth();
	int imgHeight = frames[0].getHeight();

	vector<vector<float> > tempRed(imgWidth, vector<float>(imgHeight));
	vector<vector<float> > tempGreen(imgWidth, vector<float>(imgHeight));
	vector<vector<float> > tempBlue(imgWidth, vector<float>(imgHeight));
	vector<vector<float> > tempIntens(imgWidth, vector<float>(imgHeight));
	ofImage average = frames[0];

	for (int i=0; i<frames.size();i++){
		for(int x=0; x<frames[i].getWidth();x++){
			for(int y=0; y<frames[i].getHeight();y++){
				tempRed[x][y] += frames[i].getColor(x,y).r;
				tempGreen[x][y] += frames[i].getColor(x,y).g;
				tempBlue[x][y] += frames[i].getColor(x,y).b;
				tempIntens[x][y] += frames[i].getColor(x,y).a;
			}
		}
	}
	for(int x=0; x<frames[0].getWidth();x++){
		for(int y=0; y<frames[0].getHeight();y++){
			average.setColor(x,y,ofColor((tempRed[x][y]/frames.size()),(tempGreen[x][y]/frames.size()),(tempBlue[x][y]/frames.size()),(tempIntens[x][y]/frames.size())));
		}
	}
	return average;
};

ofImage gt_backgroundSubtraction(ofImage backgroundImg, ofImage currentFrame){
	ofImage foregroundImg = currentFrame;
	for(int x=0; x<backgroundImg.getWidth();x++){
		for(int y=0; y<backgroundImg.getHeight();y++){
			foregroundImg.setColor(x,y,ofColor(ABS(currentFrame.getColor(x,y).r - backgroundImg.getColor(x,y).r),ABS(currentFrame.getColor(x,y).g - backgroundImg.getColor(x,y).g),ABS(currentFrame.getColor(x,y).b - backgroundImg.getColor(x,y).b),ABS(currentFrame.getColor(x,y).a - backgroundImg.getColor(x,y).a)));
		}
	}
	return foregroundImg;
};

ofImage gt_backgroundSubtraction(ofImage backgroundImg, ofImage currentFrame, int roiX, int roiY, int roiW, int roiH){
	ofImage foregroundImg = currentFrame;
	foregroundImg.crop(0,0,roiW,roiH);
	for(int x=0; x<roiW;x++){
		for(int y=0; y<roiH;y++){
			foregroundImg.setColor(x,y,ofColor(ABS(currentFrame.getColor(x + roiX,y + roiY).r - backgroundImg.getColor(x + roiX,y + roiY).r),ABS(currentFrame.getColor(x + roiX,y + roiY).g - backgroundImg.getColor(x + roiX,y + roiY).g),ABS(currentFrame.getColor(x + roiX,y + roiY).b - backgroundImg.getColor(x + roiX,y + roiY).b),ABS(currentFrame.getColor(x + roiX,y + roiY).a - backgroundImg.getColor(x + roiX,y + roiY).a)));
		}
	}
	return foregroundImg;
};

ofImage gt_updateReference(ofImage backgroundImg, ofImage currentFrame, float gt_alpha){
	ofImage newRef = currentFrame;
	for(int x=0; x<backgroundImg.getWidth();x++){
		for(int y=0; y<backgroundImg.getHeight();y++){
			newRef.setColor(x,y,ofColor(gt_alpha*backgroundImg.getColor(x,y).r+(1-gt_alpha)*currentFrame.getColor(x,y).r,gt_alpha*backgroundImg.getColor(x,y).g+(1-gt_alpha)*currentFrame.getColor(x,y).g,gt_alpha*backgroundImg.getColor(x,y).b+(1-gt_alpha)*currentFrame.getColor(x,y).b,gt_alpha*backgroundImg.getColor(x,y).a+(1-gt_alpha)*currentFrame.getColor(x,y).a));
		}
	}
	return newRef;
};