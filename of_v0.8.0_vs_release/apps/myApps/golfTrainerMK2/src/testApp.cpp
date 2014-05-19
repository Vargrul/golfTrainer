#include "testApp.h"
	
//Variables used for in the update function
vector<guiObj> vecGuiObj;
vector<vector<int>> integralImage;
ofxCvContourFinder contourFinder;
ofxCvGrayscaleImage contourImage,threshImgCvGray;
ofxCvColorImage contourImageColor,bgSubCvCol;
ofImage currentFrameOfImage,currentFrameOfImageRoi,normImg, bgSub,avarageBackground;

pos prediction;
pos uncertainty;
pos lastPos (0,0,0);

kfValuesFloat kfInput;

//Values for initial ROI
	//Test 2
const int initRoiX = 120;
const int initRoiY = 110;
const int initRoiW = 375;
const int initRoiH = 285;

/*	//Test 1
const int initRoiX = 50;
const int initRoiY = 140;
const int initRoiW = 500;
const int initRoiH = 340;
*/

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

int runningRoiX = 0;
int runningRoiY = 0;
int runningRoiW = 0;
int runningRoiH = 0;
	
//Variables used for mass testing
int testIterator = 0;	
const int testSize = 1;
const string logName [] = { "test.txt" };
const string movPath [] = { "../../videos/test2/ts1nochanges.mov" };
const int startFrame [] = {120};
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

	runningRoiX = initRoiX;
	runningRoiY = initRoiY;
	runningRoiW = initRoiW;
	runningRoiH = initRoiH;

	//Allovate alle ofImages for speedup in the update loop
	//ofxCvImages
	contourImage.allocate(initRoiW,initRoiH);
	contourImageColor.allocate(initRoiW,initRoiH);
	bgSubCvCol.allocate(initRoiW,initRoiH);
	threshImgCvGray.allocate(initRoiW,initRoiH);
	//ofImages
	currentFrameOfImage.allocate(680,480,OF_IMAGE_COLOR);
	currentFrameOfImageRoi.allocate(680,480,OF_IMAGE_COLOR);
	normImg.allocate(initRoiW,initRoiH,OF_IMAGE_COLOR_ALPHA);
	bgSub.allocate(initRoiW,initRoiH,OF_IMAGE_COLOR_ALPHA);
	avarageBackground.allocate(initRoiW,initRoiH,OF_IMAGE_COLOR_ALPHA);

	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
	currentFrameOfImage.crop(initRoiX,initRoiY,initRoiW,initRoiH);
	//avarageBackground = currentFrameOfImage;
	avarageBackground = normalizeImage(currentFrameOfImage);

	kfInput = kfInitValuesFloat();
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
		currentFrameOfImage.crop(initRoiX,initRoiY,initRoiW,initRoiH);
		avarageBackground = normalizeImage(currentFrameOfImage);
		printLegend = true;
		if(testIterator >= testSize){
			ofExit();
		}
	}

	if(vecGuiObj[1].isFrameNew()){
		cout << vecGuiObj[1].getCurrentFrame() << endl;
		loggingData.push_back(to_string(vecGuiObj[1].getCurrentFrame()));
		/*----------------------------------------------------------------------------------------------*/

		cout << kfInput.XkProj << "    " << kfInput.PkProj << "    " << kfInput.Kk << "    " << kfInput.Xk << "    " << kfInput.Pk << endl;
		//if(contourFinder.nBlobs > 0 && ballVelocity != 0)kfInput = kfTimeUpdateFloat(kfInput,ballVelocity);
		//The flow of the program
		//Input
		currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
		currentFrameOfImage.crop(initRoiX,initRoiY,initRoiW,initRoiH);
		currentFrameOfImageRoi = currentFrameOfImage;
		currentFrameOfImageRoi.crop(runningRoiX,runningRoiY,runningRoiW,runningRoiH);
		threshImgCvGray.resetROI();


		loggingData.push_back(captureTime(lastTime));
		/*----------------------------------------------------------------------------------------------*/
		//normalization
		normImg = normalizeImage(currentFrameOfImage);
		loggingData.push_back(captureTime(lastTime));
		/*----------------------------------------------------------------------------------------------*/
		//segmentation Background
			//Background Subtraction
		bgSub = gt_backgroundSubtraction(avarageBackground,normImg);
		loggingData.push_back(captureTime(lastTime));
		/*----------------------------------------------------------------------------------------------*/
		//Updating the avarage background
		avarageBackground = gt_updateReference(avarageBackground, normImg, 0.8f);
		loggingData.push_back(captureTime(lastTime));
		/*----------------------------------------------------------------------------------------------*/
		//Segmentation: Binary Image
		bgSub.setImageType(OF_IMAGE_COLOR);
		bgSubCvCol.setFromPixels(bgSub.getPixelsRef());
		threshImgCvGray = bgSubCvCol;

		threshImgCvGray.setROI(runningRoiX,runningRoiY,runningRoiW,runningRoiH);

		cout << runningRoiX << " " << runningRoiY << " "  << runningRoiW << " "  << runningRoiH << " "  << endl;

		threshImgCvGray.threshold(30);
		loggingData.push_back(captureTime(lastTime));
		/*----------------------------------------------------------------------------------------------*/
		//BLOB analasys
		contourFinder.findContours(threshImgCvGray,0,100,10,false,false);
		loggingData.push_back(captureTime(lastTime));
			//BLOB Clasification
		BLOBclassification(contourFinder,bcRatio,bcMaxSize,bcMinSize);
		loggingData.push_back(captureTime(lastTime));

		loggingData.push_back(to_string(contourFinder.nBlobs));
		/*----------------------------------------------------------------------------------------------*/
		for (int i = 0 ; i < contourFinder.nBlobs ; i++){
			loggingData.push_back(to_string(contourFinder.blobs.at(i).nPts));
			loggingData.push_back(to_string(contourFinder.blobs.at(i).centroid.x));
			loggingData.push_back(to_string(contourFinder.blobs.at(i).centroid.y));
		}
		for (int i = 0; i < 10 - contourFinder.nBlobs; i++)
		{
			loggingData.push_back("0");
			loggingData.push_back("0");
			loggingData.push_back("0");
		}
		logData(logName[testIterator],loggingData,' ',printLegend,legend);
		/*----------------------------------------------------------------------------------------------*/
		//Projection prediction
		if(contourFinder.nBlobs > 0){
			if(lastPos == pos(0,0,0))prediction = pos(contourFinder.blobs[0].centroid.x,contourFinder.blobs[0].centroid.y,0);
			if(lastPos != pos(0,0,0)){
				prediction = posPredictionSimple(lastPos,pos(contourFinder.blobs[0].centroid.x,contourFinder.blobs[0].centroid.y,0),uncertainty);
				cout << prediction << endl;

				/*runningRoiX = prediction.getX() - uncertainty.getX();
				runningRoiY = prediction.getY() - uncertainty.getY();
				runningRoiW = uncertainty.getX() * 2;
				runningRoiH = uncertainty.getY() * 2;*/
			}
			lastPos = pos(contourFinder.blobs[0].centroid.x,contourFinder.blobs[0].centroid.y,0);
		}else{
			runningRoiX = initRoiX;
			runningRoiY = initRoiY;
			runningRoiW = initRoiW;
			runningRoiH = initRoiH;
			lastPos = pos(0,0,0);
			prediction = pos(0,0,0);
		}
		/*if(lastPos.getX() != 0) ballVelocity = BLOBcalculateVelocity(lastPos,pos((int)contourFinder.blobs[0].centroid.x,0,0),1);
		else ballVelocity = 0;
		if(contourFinder.nBlobs > 0)lastPos = pos((int)contourFinder.blobs[0].centroid.x,0,0);

		if(contourFinder.nBlobs > 0)cout << contourFinder.blobs[0].centroid.x << " " << contourFinder.blobs[0].centroid.y << endl;

		if(contourFinder.nBlobs > 0){ 
			kfInput.Zk = contourFinder.blobs[0].centroid.x;
		}

		if(contourFinder.nBlobs > 0 && ballVelocity != 0)kfInput = kfMeasurementUpdatFloat(kfInput);
		*/
		/*----------------------------------------------------------------------------------------------*/
		vecGuiObj[0].setImage(normImg);
		vecGuiObj[2].setImgFromPixels(threshImgCvGray.getPixelsRef());
		//vecGuiObj[3].setImgFromPixels(vecGuiObj[1].getPixelsRef());
		ofImage segInten;
		segInten.allocate(initRoiW,initRoiH,OF_IMAGE_GRAYSCALE);
		for(int i = 0; i < bgSub.width ; i++){
			for(int ii = 0; ii < bgSub.height; ii++){
				segInten.setColor(i,ii,ofColor(normImg.getColor(i,ii).a));
			}
		}
		vecGuiObj[3].setImgFromPixels(segInten);

		printLegend = false;
		/*----------------------------------------------------------------------------------------------*/
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//Draws all guiObjects in vecGuiObj
	for(int i = 0 ; i < vecGuiObj.size() ; i++)
	{ 
		vecGuiObj[i].draw();
	}

	//threshImgCvGray.draw(0,480);
	//Draws the centroid and bounding box of all blobs
	for(int i = 0 ; i < contourFinder.nBlobs ; i++){
		ofSetColor(255,0,0);
		ofFill();
		ofCircle(contourFinder.blobs[i].centroid.x + runningRoiX,contourFinder.blobs[i].centroid.y + 480 + runningRoiY,1);
		ofCircle(contourFinder.blobs[i].centroid.x + 640 + runningRoiX,contourFinder.blobs[i].centroid.y + 480 + runningRoiY,1);
		ofSetColor(0,255,0);
		ofNoFill();

		ofRectangle r = contourFinder.blobs.at(i).boundingRect;
		r.y += 480 + runningRoiY;
		r.x += runningRoiX;
		ofRect(r);
		r.x += 640;
		ofRect(r);

		ofSetColor(255,255,255);
	}
	ofSetColor(0,255,0);
	ofNoFill();
	ofRect(prediction.getX() - uncertainty.getX(),prediction.getY() - uncertainty.getY(),uncertainty.getX() * 2,uncertainty.getY() * 2);

	ofSetColor(0,0,255);
	ofFill();
	if(contourFinder.nBlobs > 0)ofCircle(prediction.getX()+640+initRoiX,prediction.getY()+initRoiY,5);
	ofSetColor(0,255,0);
	ofNoFill();

	//Draws the indentifier Text
	ofDrawBitmapStringHighlight("Video Feed",920,20);
	ofDrawBitmapStringHighlight("Segmentation: Foreground",200,20);
	ofDrawBitmapStringHighlight("Thresholded Image (with blobs)",160,500);
	ofDrawBitmapStringHighlight("Video feed with blobs",870,500);

	//Draws initialROI
	ofSetColor(255,0,0);
	ofNoFill();
	//ofRect(640 + initRoiX, 480+initRoiY, 0, initRoiW, initRoiH);
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