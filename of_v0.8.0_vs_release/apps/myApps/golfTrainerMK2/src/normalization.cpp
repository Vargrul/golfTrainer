#include "normalization.h"

ofImage normalizeImage(ofImage inImg){
	ofImage outImg;
	outImg.allocate(inImg.getWidth(),inImg.getHeight(),OF_IMAGE_COLOR_ALPHA);
	for(int p = 0;p < inImg.getHeight();p++){
		for(int q = 0; q < inImg.getWidth();q++){
			outImg.setColor(q, p, RGB2rgb(inImg.getColor(q,p)));
		}
	}
	//Normalization of Alpha channel
		//http://en.wikipedia.org/wiki/Normalization_(image_processing)
	int min = 0, max = 0, newMin = 0, newMax = 255;

	for(int x = 0 ; x < inImg.getWidth() ; x++){
		for(int y = 0 ; y < inImg.getHeight() ; y++){
			if(min > outImg.getColor(x,y).a) min = outImg.getColor(x,y).a;
			if(max < outImg.getColor(x,y).a) max = outImg.getColor(x,y).a;
		}
	}
	for(int x = 0 ; x < inImg.getWidth() ; x++){
		for(int y = 0 ; y < inImg.getHeight() ; y++){
			ofColor temp = outImg.getColor(x,y);
			temp.a = (outImg.getColor(x,y).a - min)*((newMax - newMin)/(max - min))+newMin;
			outImg.setColor(x,y,temp);
		}
	}

	return outImg;
}

ofImage normalizeROI(vector<vector<pos>> i, ofImage inROI){
	//Output image
	ofImage outROI;
	outROI.allocate(inROI.getWidth(),inROI.getHeight(),OF_IMAGE_COLOR_ALPHA);

	//Loop through each position pair
	for(int j = 0; j < i.size(); j++){

		//Get the two positions
		pos upperleft = i[j][0], lowerright = i[j][1];
		
		//Get width and height of the current ROI
		int ROIwidth = lowerright.getX() - upperleft.getX();
		int ROIheight = lowerright.getY() - upperleft.getY();

		//Loop through each pixel in the ROI and convert pixels to chromatic rg
		for(int p = 0;p < ROIheight;p++){
			for(int q = 0; q < ROIwidth;q++){
				pos inColPos(upperleft.getX()+q,upperleft.getY()+p,0);
				outROI.setColor(inColPos.getX(), inColPos.getY(), RGB2rgb(inROI.getColor(inColPos.getX(),inColPos.getY())));
			}
		}
	}
	//Return output
	return outROI;
}

ofColor RGB2rgb(ofColor inCol){
	//convert to rg -> r = \frac{R}{R+G+B}  g = \frac{G}{R+G+B}  b = \frac{B}{R+G+B}
	//we only need the r and g values since r+g+b=1 so we can calculate b value when needed
	ofColor outCol = inCol;

	if(inCol.r != 0)outCol.r = (unsigned char)(((float)inCol.r/((float)inCol.r + (float)inCol.g + (float)inCol.b))*255.0f);
	if(inCol.g != 0)outCol.g = (unsigned char)(((float)inCol.g/((float)inCol.r + (float)inCol.g + (float)inCol.b))*255.0f);
	outCol.b = (unsigned char)abs(((int)outCol.r + (int)outCol.g) - 255);
	//The intensity is getting stored in the alpha channel
		

	int tempR,tempG,tempB;

	if(inCol.r < 1)tempR = 1; else tempR = inCol.r;
	if(inCol.g < 1)tempG = 1; else tempG = inCol.g;
	if(inCol.b < 1)tempB = 1; else tempB = inCol.b;

	float f1 = (float)MIN(tempR,tempG)/(float)MAX(tempR,tempG);
	float f2 = (float)MIN(tempG,tempB)/(float)MAX(tempG,tempB);
	float f3 = (float)MIN(tempB,tempR)/(float)MAX(tempB,tempR);

	//cout << (f1+f2+f3)/3 << " " << ((f1+f2+f3)/3)*255 << endl;

	outCol.a = (unsigned char)(((f1+f2+f3)/3)*255);
	if(outCol.a  < 100) outCol.a = (unsigned char)100;
	//return the new rg color
	return outCol;
}