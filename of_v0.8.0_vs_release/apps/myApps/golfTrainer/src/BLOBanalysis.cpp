#include "BLOBanalysis.h"

vector<BLOB> BLOBanalysis(ofImage inputImg){
	//Vector for holding BLOBs
	vector<BLOB> BLOBlist;
	ofPixels pixels = inputImg.getPixelsRef;

	//Loop through every pixel in the input image
	for(int i = 0;i<inputImg.getHeight();i++){
		for(int j = 0;j<inputImg.getWidth();j++){
			//Look for pixels that aren't black.
			int tempVal = pixels[i * inputImg.getHeight() + j];
			if(tempVal != 0){
				//Starts the connected componant analysis and inserts the resulting
				//BLOB object in the BLOB list.
				BLOBlist.push_back(connectedComponantAnalysis(j,i,inputImg));
			}
		}
	}

	return BLOBlist;
}

BLOB connectedComponantAnalysis(int x, int y, ofImage& inputImg){
	//return BLOB
	BLOB blob;

	//Do neighborhood check for white pixels
	neighborCheck(x, y, inputImg, blob);

	return blob;
}
void burnPixel(int x, int y, ofImage& inputImg, BLOB& blob){
	//Adding the pixel to the list of pixels in the given BLOB.
	pos tempPos(x,y,0);
	blob.addPixel(tempPos);
	//Remove the starting pixel from the input image. 
	// Sets the pixel to 0,0,0(Black)
	inputImg.setColor(x, y, ofColor(0,0,0));
	
}
void neighborCheck(int x, int y, ofImage& inputImg, BLOB& blob){
	ofColor blackCol(0,0,0);
	//Remove the starting pixel from the input image.
	burnPixel(x, y, inputImg, blob);
	//Start looking through the neighborhood
	if(inputImg.getColor(x+1,y)!=blackCol){
		//Recursive call
		neighborCheck(x+1, y, inputImg, blob);
	}
	if(inputImg.getColor(x,y+1)!=blackCol){
		//Recursive call
		neighborCheck(x, y+1, inputImg, blob);
	}
	if(inputImg.getColor(x-1,y)!=blackCol){
		//Recursive call
		neighborCheck(x-1, y, inputImg, blob);
	}
	if(inputImg.getColor(x,y-1)!=blackCol){
		//Recursive call
		neighborCheck(x, y-1, inputImg, blob);
	}
	return;
}