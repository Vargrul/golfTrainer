#include "testApp.h"
	
vector<guiObj> vecGuiObj;
ofImage currentFrameOfImage;
vector<vector<int>> integralImage;
ofImage avarageBackground;
vector<vector<pos>> roiPositions;
ofxCvContourFinder contourFinder;

bool printLegend = true;
string legend = "initial_part | avarageBackground | gt_backgroundSubtraction | thresholdRGB | img2integralImg | roiLimiter | normalizeROI | ";

//--------------------------------------------------------------
void testApp::setup(){
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,0,0),"../../images/testImage.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,0,0),"../../videos/th1_55w.mov",VIDEO));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,480,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,480,0),"../../images/testSquare.png",IMAGE));
	//vecGuiObj[1].play();
	vecGuiObj[1].setFrame(100);
	//vecGuiObj[0].setImgFromPixels(vecGuiObj[1].getPixelsRef());
	vecGuiObj[1].setFrame(80);

	roiPositions.push_back(vector<pos>());
	roiPositions[0].push_back(pos(0,0,0));
	roiPositions[0].push_back(pos(99,99,0));

	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
	avarageBackground = currentFrameOfImage;
}

//--------------------------------------------------------------
void testApp::update(){
	vector<string> loggingData;
	clock_t lastTime = clock();
	string sTemp;
	ofImage normImg, bgSub, threshRGB;

	vecGuiObj[1].vidUpdate();
	vecGuiObj[1].nextFrame();

	loggingData.push_back(captureTime(lastTime));

	//The flow of the program
	//Input
	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());

	loggingData.push_back(captureTime(lastTime));

	//segmentation Background
	bgSub = gt_backgroundSubtraction(avarageBackground,currentFrameOfImage);
	loggingData.push_back(captureTime(lastTime));

	avarageBackground = gt_updateReference(avarageBackground, currentFrameOfImage, 0.8f);
	loggingData.push_back(captureTime(lastTime));

	//Segmentation: Binary Image
	threshRGB = thresholdRGB(bgSub,40,40,40);
	loggingData.push_back(captureTime(lastTime));

	/*
	//Integral Image
	integralImage.clear();
	img2integralImg(threshRGB, MEAN, integralImage);
	loggingData.push_back(captureTime(lastTime));

	//Roi Limiter
	//TO-DO: Change the way the roiLimiter makes a decition of how interesting the ROI is
	/*
	roiPositions.clear();
	roiLimiter(integralImage, roiPositions);
	loggingData.push_back(captureTime(lastTime));
	*/

	/*
	//Normalize ROIs
	//Is it needed? or is it only time consuming?
	if(pastFrames.size() > 1)normImg = normalizeROI(roiPositions,bgSub);
	loggingData.push_back(captureTime(lastTime));
	*/

	//Probability Map



	//BLOB analasys
	//vector<BLOB> blobs = BLOBanalysis(threshRGB);
	ofxCvGrayscaleImage contourImage;
	ofxCvColorImage contourImageColor;
	contourImageColor.setFromPixels(threshRGB.getPixelsRef());
	contourImage = contourImageColor;
	contourFinder.findContours(contourImage,0,100,10,false,false);
	loggingData.push_back(captureTime(lastTime));

	logData("testLog1.txt",loggingData,' ',printLegend,legend);

	vecGuiObj[0].setImage(bgSub);
	vecGuiObj[2].setImage(threshRGB);
	//vecGuiObj[3].setImage(normImg);

	printLegend = false;
}

//--------------------------------------------------------------
void testApp::draw(){
	//Draws all guiObjects in vecGuiObj
	for(int i = 0 ; i < vecGuiObj.size() ; i++)
	{ 
		vecGuiObj[i].draw();
	}
	for(int i = 0 ; i < roiPositions.size() ; i++){
		ofSetColor(255,0,0);
		ofFill();
		ofCircle(roiPositions[i][0].getX()+640,roiPositions[i][0].getY()+480,1);
		ofCircle(roiPositions[i][0].getX()+640,roiPositions[i][1].getY()+480,1);
		ofCircle(roiPositions[i][1].getX()+640,roiPositions[i][0].getY()+480,1);
		ofCircle(roiPositions[i][1].getX()+640,roiPositions[i][1].getY()+480,1);
		ofSetColor(255,255,255);
		ofNoFill();
	}
	for(int i = 0 ; i < contourFinder.nBlobs ; i++){
		ofSetColor(255,0,0);
		ofFill();

		ofCircle(contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y+480,2);
		
		ofSetColor(255,255,255);
		ofNoFill();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	/*if(button == 0){



		for(int i = 0 ; i < vecGuiObj.size() ; i++)
		{ 
			if(vecGuiObj[i].mouseCheck(x,y) == true){
				//do something
			}
		}
	}*/
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}