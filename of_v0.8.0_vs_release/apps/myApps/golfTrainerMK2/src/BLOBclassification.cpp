#include "BLOBclassification.h"

void BLOBclassification(ofxCvContourFinder &contIn, float check_Ratio, int max_nPts, int min_nPts){
	//Check the ratio of height and width and Area
	for(int i = 0 ; i < contIn.nBlobs ; i++){
		
		//Calculate and check Ratio
		float ratio;

		if(contIn.blobs[i].boundingRect.getHeight() > contIn.blobs[i].boundingRect.getWidth()){
			ratio = contIn.blobs[i].boundingRect.getHeight()/contIn.blobs[i].boundingRect.getWidth();
		}else{
			ratio = contIn.blobs[i].boundingRect.getWidth()/contIn.blobs[i].boundingRect.getHeight();
		}

		//Check ration
		if(ratio > check_Ratio){
			//Check size
			if(contIn.blobs[i].nPts > max_nPts || contIn.blobs[i].nPts < min_nPts){
				contIn.blobs.erase(contIn.blobs.begin() + i);
				contIn.nBlobs --;
				i--;
			}
		}
	}
}