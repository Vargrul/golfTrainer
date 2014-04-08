#include "backgroundSub.h"

ofImage averageBackground(vector<ofImage> frames){
	int imgWidth = frames[0].getWidth();
	int imgHeight = frames[0].getHeight();

	vector<vector<float> > tempRed;
	vector<vector<float> > tempGreen;
	vector<vector<float> > tempBlue;
	ofImage average;

	for (int i=0; i<frames.size();i++){
		for(int x=0; x<frames[i].getWidth();x++){
			for(int y=0; y<frames[i].getHeight();y++){
				tempRed[x][y] += frames[i].getColor(x,y).r;
				tempGreen[x][y] += frames[i].getColor(x,y).g;
				tempBlue[x][y] += frames[i].getColor(x,y).b;
			}
		}
	}
	for (int i=0; i<frames.size();i++){
		for(int x=0; x<frames[i].getWidth();x++){
			for(int y=0; y<frames[i].getHeight();y++){
				average.setColor(x,y,ofColor((tempRed[x][y]/frames.size()),(tempGreen[x][y]/frames.size()),(tempBlue[x][y]/frames.size())));
			}
		}
	}
	return average;
}

ofImage backgroundSubtraction(ofImage backgroundImg, ofImage currentFrame){
	ofImage foregroundImg;
	for(int x=0; x<backgroundImg.getWidth();x++){
		for(int y=0; y<backgroundImg.getHeight();y++){
			foregroundImg.setColor(x,y,ofColor(ABS(currentFrame.getColor(x,y).r - backgroundImg.getColor(x,y).r),ABS(currentFrame.getColor(x,y).g - backgroundImg.getColor(x,y).g),ABS(currentFrame.getColor(x,y).b - backgroundImg.getColor(x,y).b)));
		}
	}
	return foregroundImg;
}

ofImage updateReference(ofImage backgroundImg, ofImage currentFrame, float a = 0.95){
	float a;		//a = update speed (alpha)
	ofImage newRef;
	for(int x=0; x<backgroundImg.getWidth();x++){
		for(int y=0; y<backgroundImg.getHeight();y++){
			newRef.setColor(x,y,ofColor(a*backgroundImg.getColor(x,y).r+(1-a)*currentFrame.getColor(x,y).r,a*backgroundImg.getColor(x,y).g+(1-a)*currentFrame.getColor(x,y).g,a*backgroundImg.getColor(x,y).b+(1-a)*currentFrame.getColor(x,y).b));
		}
	}
	return newRef
}