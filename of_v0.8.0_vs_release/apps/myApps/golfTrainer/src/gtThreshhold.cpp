#include "gtThreshhold.h"

ofImage threshhold(ofImage imgIn, float hueMinIn, float hueMaxIn, float satMinIn, float satMaxIn, float brigMinIn, float brigMaxIn){
	ofImage imgOut = imgIn;

	for(int i = 0 ; i < imgIn.getWidth ; i++){
		for(int j = 0 ; j < imgIn.getHeight ; j++){

			ofColor pixColor = imgIn.getColor(i,j);

			if (pixColor.getHue() > hueMinIn && pixColor.getHue() < hueMaxIn && pixColor.getSaturation() > satMinIn && pixColor.getSaturation() < satMaxIn && pixColor.getBrightness() > brigMinIn && pixColor.getBrightness() < brigMaxIn){
				imgOut.setColor(ofColor(255,255,255));
			}
			else imgOut.setColor(ofColor(0,0,0));
		}
	}
};

tuple<float,float,float,float,float,float> adapThreshVal(ofImage imgIn){
	float hueMin, hueMax, satMin, satMax, brigMin, brigMax; //the output variable in the outputoging order

	return tuple<float,float,float,float,float,float> (hueMin, hueMax, satMin, satMax, brigMin, brigMax);
};

