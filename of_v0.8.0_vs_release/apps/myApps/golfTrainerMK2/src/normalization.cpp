#include "normalization.h"

ofImage normalizeImage(ofImage inImg){
	ofImage outImg = inImg;
	for(int p = 0;p < inImg.getHeight();p++){
		for(int q = 0; q < inImg.getWidth();q++){
			outImg.setColor(q, p, RGB2rgb(inImg.getColor(q,p)));
		}
	}
	return outImg;
}

ofImage normalizeROI(vector<vector<pos>> i, ofImage inROI){
	//Output image
	ofImage outROI=inROI;

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

	//cout << "red: " << (int)outCol.r << " green: " << (int)outCol.g << " blue: " << (int)outCol.g << endl;

	//return the new rg color
	return outCol;
}