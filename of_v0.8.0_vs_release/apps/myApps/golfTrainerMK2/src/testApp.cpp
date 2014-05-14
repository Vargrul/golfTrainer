#include "testApp.h"
	
//Variables used for in the update function
vector<guiObj> vecGuiObj;
vector<vector<int>> integralImage;
ofxCvContourFinder contourFinder;
ofxCvGrayscaleImage contourImage,threshImgCvGray;
ofxCvColorImage contourImageColor,bgSubCvCol;
ofImage currentFrameOfImage,normImg, bgSub,avarageBackground;

//Values for initial ROI
	//Test 2
/*
const int roiX = 120;
const int roiY = 110;
const int roiW = 375;
const int roiH = 285;
*/
	//Test 1
const int roiX = 50;
const int roiY = 140;
const int roiW = 500;
const int roiH = 340;

//BLOBclassefication values
	//Test 2
float bcRatio = 2.0f;
int bcMaxSize = 25;
int bcMinSize = 10;

	//Test 1
/*
float bcRatio = 2.0f;
int bcMaxSize = 25;
int bcMinSize = 10;
*/
	
//Variables used for mass testing
int testIterator = 0;
const int testSize = 1;
const string logName [] = { "test.txt" };
const string movPath [] = { "../../videos/test1/TP1_6m.mov" };
const int startFrame [] = {1};
const int endFrame []= {870};
bool printLegend = true;
const string legend = "frameNumber initialPart normalization backgroundSubtraction averageBackgroundUpdate thresholding BLOBdetection BLOBclassification nrOfBlobs blobArea_1 centroidX_1 controidY_1 blobArea_2 centroidX_2 controidY_2 blobArea_3 centroidX_3 controidY_3";


//--------------------------------------------------------------
void testApp::setup(){
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,0,0),"../../images/testImage.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,0,0),"../../videos/test1/TP1_1m_right.mov",VIDEO));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,480,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,480,0),"../../images/testSquare.png",IMAGE));
	
	vecGuiObj[1].setVideo(movPath[testIterator]);
	vecGuiObj[1].setFrame(startFrame[testIterator]);
	//vecGuiObj[1].play();

	//Allovate alle ofImages for speedup in the update loop
	//ofxCvImages
	contourImage.allocate(roiW,roiH);
	contourImageColor.allocate(roiW,roiH);
	bgSubCvCol.allocate(roiW,roiH);
	threshImgCvGray.allocate(roiW,roiH);
	//ofImages
	currentFrameOfImage.allocate(680,480,OF_IMAGE_COLOR);
	normImg.allocate(roiW,roiH,OF_IMAGE_COLOR);
	bgSub.allocate(roiW,roiH,OF_IMAGE_COLOR);
	avarageBackground.allocate(roiW,roiH,OF_IMAGE_COLOR);


	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
	currentFrameOfImage.crop(roiX,roiY,roiW,roiH);
	avarageBackground = normalizeImage(currentFrameOfImage);
}

//--------------------------------------------------------------
void testApp::update(){
	vector<string> loggingData;
	clock_t lastTime = clock();
	string sTemp;

	vecGuiObj[1].nextFrame();
	vecGuiObj[1].nextFrame();
	vecGuiObj[1].nextFrame();
	vecGuiObj[1].vidUpdate();

	if(vecGuiObj[1].getCurrentFrame() > endFrame[testIterator] || vecGuiObj[1].getCurrentFrame() < startFrame[testIterator]){
		testIterator++;
		vecGuiObj[1].setVideo(movPath[testIterator]);
		vecGuiObj[1].setFrame(startFrame[testIterator]);
		currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
		currentFrameOfImage.crop(roiX,roiY,roiW,roiH);
		avarageBackground = normalizeImage(currentFrameOfImage);
		printLegend = true;
		if(testIterator >= testSize){
			ofExit();
		}
	}

	if(vecGuiObj[1].isFrameNew()){
		cout << vecGuiObj[1].getCurrentFrame() << endl;
		loggingData.push_back(to_string(vecGuiObj[1].getCurrentFrame()));
	

		//The flow of the program
		//Input
		currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
		currentFrameOfImage.crop(roiX,roiY,roiW,roiH);
		loggingData.push_back(captureTime(lastTime));

		//normalization
		normImg = normalizeImage(currentFrameOfImage);
		loggingData.push_back(captureTime(lastTime));

		//segmentation Background
			//Background Subtraction
		bgSub = gt_backgroundSubtraction(avarageBackground,normImg);
		loggingData.push_back(captureTime(lastTime));

		//Updating the avarage background
		avarageBackground = gt_updateReference(avarageBackground, normImg, 0.8f);
		loggingData.push_back(captureTime(lastTime));

		//Segmentation: Binary Image
		bgSubCvCol.setFromPixels(bgSub.getPixelsRef());
		threshImgCvGray = bgSubCvCol;
		threshImgCvGray.threshold(30);
		loggingData.push_back(captureTime(lastTime));

		//BLOB analasys
		contourFinder.findContours(threshImgCvGray,0,100,10,false,false);
		loggingData.push_back(captureTime(lastTime));
			//BLOB Clasification
		BLOBclassification(contourFinder,bcRatio,bcMaxSize,bcMinSize);
		loggingData.push_back(captureTime(lastTime));

		loggingData.push_back(to_string(contourFinder.nBlobs));

		for (int i = 0 ; i < contourFinder.nBlobs ; i++){
			loggingData.push_back(to_string(contourFinder.blobs.at(0).nPts));
			loggingData.push_back(to_string(contourFinder.blobs.at(0).centroid.x));
			loggingData.push_back(to_string(contourFinder.blobs.at(0).centroid.y));
		}
		for (int i = 0; i < 3 - contourFinder.nBlobs; i++)
		{
			loggingData.push_back("0");
			loggingData.push_back("0");
			loggingData.push_back("0");
		}

		logData(logName[testIterator],loggingData,' ',printLegend,legend);

		vecGuiObj[0].setImage(normImg);
		vecGuiObj[2].setImgFromPixels(threshImgCvGray.getPixelsRef());
		vecGuiObj[3].setImgFromPixels(vecGuiObj[1].getPixelsRef());

		printLegend = false;
		//avarageBackground = currentFrameOfImage;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//Draws all guiObjects in vecGuiObj
	for(int i = 0 ; i < vecGuiObj.size() ; i++)
	{ 
		vecGuiObj[i].draw();
	}

	//Draws the centroid and bounding box of all blobs
	for(int i = 0 ; i < contourFinder.nBlobs ; i++){
		ofSetColor(255,0,0);
		ofFill();
		ofCircle(contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y + 480,1);
		ofCircle(contourFinder.blobs[i].centroid.x + 640 + roiX,contourFinder.blobs[i].centroid.y + 480 + roiY,1);
		ofSetColor(0,255,0);
		ofNoFill();

		ofRectangle r = contourFinder.blobs.at(i).boundingRect;
		r.y += 480;
		ofRect(r);
		r.y += roiY;
		r.x += 640 + roiX;
		ofRect(r);

		ofSetColor(255,255,255);
	}

	//Draws the indentifier Text
	ofDrawBitmapStringHighlight("Video Feed",920,20);
	ofDrawBitmapStringHighlight("Segmentation: Foreground",200,20);
	ofDrawBitmapStringHighlight("Thresholded Image (with blobs)",160,500);
	ofDrawBitmapStringHighlight("Video feed with blobs",870,500);

	//Draws initialROI
	ofSetColor(255,0,0);
	ofRect(640 + roiX, 480+roiY, 0, roiW, roiH);
	ofSetColor(255,255,255);
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