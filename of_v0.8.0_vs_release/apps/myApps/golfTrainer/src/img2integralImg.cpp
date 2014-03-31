#include "img2integralImg.h"

void img2integralImg(ofImage imgIn, colorImg2integral sIn,vector<vector<int>>& outVec){
	
	int height = imgIn.getHeight();
	int width = imgIn.getWidth();
	
	for(int i = 0 ; i < width ; i++){
		int sum = 0;
		for(int j = 0 ; j < height ; j++){
			
			int currentVal;
			int currentVal_im1;

			//Choose what color to make it from
			if(sIn == 0){currentVal = imgIn.getColor(i,j).r; if(i!=0){currentVal_im1 = imgIn.getColor(i - 1,j).r;} }
			else if(sIn == 1){currentVal = imgIn.getColor(i,j).g; if(i!=0){currentVal_im1 = imgIn.getColor(i - 1,j).g;} }
			else if(sIn == 2){currentVal = imgIn.getColor(i,j).b; if(i!=0){currentVal_im1 = imgIn.getColor(i - 1,j).b;} }
			else if(sIn == 3){currentVal = (imgIn.getColor(i,j).r + imgIn.getColor(i,j).g + imgIn.getColor(i,j).b) / 3;  if(i!=0){currentVal_im1 = (imgIn.getColor(i-1,j).r + imgIn.getColor(i-1,j).g + imgIn.getColor(i-1,j).b) / 3;} }
			//Error massage for when colorImg2integral sIn is out of range
			else{cout << "invalid input for img2integralImg" << endl; return;}

			//Updating the integral image with the value for the given pixel
			sum = sum + currentVal;
			if(i == 0){
				outVec.insert(outVec.end(),vector<int>());
				outVec[i].insert(outVec[i].end(),sum);
			}else{
				outVec[i].insert(outVec[i].end(),currentVal_im1 + sum);
			}
		}
	}
};