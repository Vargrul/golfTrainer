#include "img2integralImg.h"

void img2integralImg(ofImage imgIn, colorImg2integral sIn,vector<vector<int>>& outVec){
	
	int height = imgIn.getHeight();
	int width = imgIn.getWidth();
	
	for(int i = 0 ; i < width ; i++){
		for(int j = 0 ; j < height ; j++){
			
			int currentVal;

			//Choose what color to make it from
			switch (sIn){
			case RED :
				currentVal = imgIn.getColor(i,j).r;
				break;
			case GREEN :
				currentVal = imgIn.getColor(i,j).g;
				break;
			case BLUE :
				currentVal = imgIn.getColor(i,j).b;
				break;
			case MEAN : 
				currentVal = (imgIn.getColor(i,j).r + imgIn.getColor(i,j).g + imgIn.getColor(i,j).b) / 3;
				break;
			//Error massage for when colorImg2integral sIn is out of range
			default : 
				cout << "invalid input for img2integralImg" << endl;
			}

			//Updating the integral image with the value for the given pixel
			currentVal;
			if(j == 0 && i == 0){
				outVec.push_back(vector<int>());
				outVec[i].push_back(currentVal);
			}else if(j == 0){
				outVec.push_back(vector<int>());
				outVec[i].push_back(outVec[i-1][j] + currentVal);
			}else if(i == 0){
				outVec[i].push_back(outVec[i][j-1] + currentVal);
			}else{
				outVec[i].push_back(outVec[i-1][j] + outVec[i][j-1] + currentVal - outVec[i-1][j-1]);
			}
		}
	}
};

int intImgAreaSum(vector<vector<int>> inImg, pos upLeft, pos botRight){
	int a = inImg[upLeft.getX()][upLeft.getY()];
	int b = inImg[botRight.getX()][upLeft.getY()];
	int c = inImg[botRight.getX()][botRight.getY()];
	int d = inImg[upLeft.getX()][botRight.getY()];

	int returnVal;

	returnVal = c+a-b-d;

	return returnVal;
}