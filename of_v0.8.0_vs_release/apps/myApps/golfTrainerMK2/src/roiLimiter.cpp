#include "roiLimiter.h"

void roiLimiter(vector<vector<int>> integralImageIn,vector<vector<pos>>& outPositions){
	int timesDivided = 0;
	int width = integralImageIn.size()-1;
	int height = integralImageIn[0].size()-1;

	vector<bool> storeToChange;
	
	outPositions.push_back( vector<pos>());
	outPositions[0].push_back(pos(0,0,0));
	outPositions[0].push_back(pos(width,height,0));

	do{
		timesDivided++;
		vector<vector<pos>> tempOutPositions;
		storeToChange.clear();
		//Calculats the need for further investigating a ROI
		for(int i = 0 ; i < outPositions.size() ; i++){

			int temp = intImgAreaSum(integralImageIn,outPositions[i][0],outPositions[i][1]);

			//calculation of checkVal should be revisited
			float checkVal = 25;// * ((outPositions[i][1].getX() - outPositions[i][0].getX()) * (outPositions[i][1].getY() - outPositions[i][0].getY()));
			
			//stores if the current ROI should be split or not
			if(temp > checkVal) storeToChange.push_back(true);
			else storeToChange.push_back(false);
		}

		//Creates the new ROIs if needed
		for(int i = 0 ; i < storeToChange.size() ; i++){
			if(storeToChange[i]){
				int tempWidth = (outPositions[i][1].getX() - outPositions[i][0].getX())/2;
				int tempHeight = (outPositions[i][1].getY() - outPositions[i][0].getY())/2;
				
				//Adding upper left ROI
				tempOutPositions.push_back(vector<pos>());
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][0]));
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][1].getX() - tempWidth,outPositions[i][1].getY() - tempHeight,0));
				//Addming upper right ROI
				tempOutPositions.push_back(vector<pos>());
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][0].getX() + tempWidth,outPositions[i][0].getY(),0));
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][1].getX(),outPositions[i][1].getY() - tempHeight,0));
				//Adding buttom left ROI
				tempOutPositions.push_back(vector<pos>());
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][0].getX(),outPositions[i][0].getY() + tempHeight,0));
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][1].getX() - tempWidth,outPositions[i][1].getY(),0));
				//Adding buttom right ROI
				tempOutPositions.push_back(vector<pos>());
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][0].getX() + tempWidth,outPositions[i][0].getY() + tempHeight,0));
				tempOutPositions[tempOutPositions.size()-1].push_back(pos(outPositions[i][1]));
			}
		}

		//Updates the outPosition matrix with new ROIs
		outPositions.clear();
		for(int i = 0 ; i < tempOutPositions.size() ; i++){
			outPositions.insert(outPositions.end(),tempOutPositions[i]);
		}
	}while(outPositions.size() != 0 && timesDivided < 5 );
}