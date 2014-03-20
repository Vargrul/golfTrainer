#include "img2integralImg.h"

void img2integralImg(ofImage imgIn, colorImg2integral sIn,vector<vector<int>>& outVec){
	
	int height = imgIn.getHeight;
	int width = imgIn.getWidth;

	for(int i = 0 ; i < height ; i++){
		for(int j = 0 ; j < width ; j++){

			//Choose what color to make it from
			if(sIn == 0){int currentVal = imgIn.getColor(i,j).r;}
			else if(sIn == 1){int currentVal = imgIn.getColor(i,j).g;}
			else if(sIn == 2){int currentVal = imgIn.getColor(i,j).b;}
			else if(sIn == 3){int currentVal = (imgIn.getColor(i,j).r + imgIn.getColor(i,j).g + imgIn.getColor(i,j).b) / 3;}

			//Error massage for when colorImg2integral sIn is out of range
			else{cout << "invalid input for img2integralImg" << endl;}


		}
	}
};