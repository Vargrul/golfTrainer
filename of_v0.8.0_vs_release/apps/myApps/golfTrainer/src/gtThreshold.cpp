#include "gtThreshold.h"

ofImage thresholdRGB(ofImage imgIn, int minR, int minG, int minB){
	ofImage imgOut = imgIn;
	
	for(int i = 0 ; i < imgIn.getWidth() ; i++){
		for(int j = 0 ; j < imgIn.getHeight() ; j++){

			ofColor pixColor = imgIn.getColor(i,j);

			if(pixColor.r > minR && pixColor.g > minG && pixColor.b > minB){
				imgOut.setColor(i,j,ofColor(255,255,255));
			}else{
				imgOut.setColor(i,j,ofColor(0,0,0));
			}

		}
	}

	return imgOut;
}

ofImage thresholdHSB(ofImage imgIn, float hueMinIn, float hueMaxIn, float satMinIn, float satMaxIn, float brigMinIn, float brigMaxIn){
	ofImage imgOut = imgIn;

	for(int i = 0 ; i < imgIn.getWidth() ; i++){
		for(int j = 0 ; j < imgIn.getHeight() ; j++){

			ofColor pixColor = imgIn.getColor(i,j);

			if (pixColor.getHue() > hueMinIn && pixColor.getHue() < hueMaxIn && pixColor.getSaturation() > satMinIn && pixColor.getSaturation() < satMaxIn && pixColor.getBrightness() > brigMinIn && pixColor.getBrightness() < brigMaxIn){
				imgOut.setColor(i,j,ofColor(255,255,255));
			}
			else imgOut.setColor(i,j,ofColor(0,0,0));
		}
	}
	return imgOut;
};

tuple<float,float,float,float,float,float> adapThresVal(ofImage imgIn){
	float hueMin, hueMax, satMin, satMax, brigMin, brigMax; //the output variable in the outputoging order

	return tuple<float,float,float,float,float,float> (hueMin, hueMax, satMin, satMax, brigMin, brigMax);
};

float otsuThreshVal(ofImage img){
	return NULL;
};

