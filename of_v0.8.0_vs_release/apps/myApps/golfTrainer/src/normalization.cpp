#include "normalization.h"

ofImage normalizeROI(vector<pos[2]> i, ofImage inROI){
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
				pos tempPos(upperleft.getX()+q,upperleft.getY()+p,0);
				outROI.setColor(tempPos.getX(), tempPos.getY(), RGB2rgb(tempPos, inROI));
				
			}
		}
	}
	//Return output
	return outROI;
}

ofColor RGB2rgb(pos i, ofImage inROI){
	//Get RBG of pixel position i
	ofColor temp;// = inROI[i.getX()][i.getY()];
	//convert to rg -> r = \frac{R}{R+G+B}  g = \frac{G}{R+G+B}  b = \frac{B}{R+G+B}
	//we only need the r and g values since r+g+b=1 so we can calculate b value when needed
	ofColor outCol;
	outCol.r = temp.r/(temp.r + temp.g + temp.b);
	outCol.g = temp.g/(temp.r + temp.g + temp.b);

	//return the new rg color
	return outCol;
}
