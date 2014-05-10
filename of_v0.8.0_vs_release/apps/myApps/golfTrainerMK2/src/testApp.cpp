#include "testApp.h"
	
vector<guiObj> vecGuiObj;
ofImage currentFrameOfImage;
vector<vector<int>> integralImage;
ofImage avarageBackground;
vector<vector<pos>> roiPositions;
ofxCvContourFinder contourFinder;

ofxCvGrayscaleImage contourImage;
ofxCvColorImage contourImageColor;
	
int testIterator = 0;
int testSize = 24;
string logName [] = {  "TP1_1m_right_W_1.txt" , "TP1_1m_right_Y_1.txt" , "TP1_1m_right_D_1.txt" , "TP1_2m_right_W_1.txt" , "TP1_2m_right_Y_1.txt" , "TP1_2m_right_D_1.txt" , "TP1_3m_right_W_1.txt" , "TP1_3m_right_Y_1.txt" , "TP1_3m_right_D_1.txt" , "TP1_4m_right_W_1.txt" , "TP1_4m_right_Y_1.txt" , "TP1_4m_right_D_1.txt" , "TP1_5m_right_W_1.txt" , "TP1_5m_right_Y_1.txt" , "TP1_5m_right_D_1.txt" , "TP1_6m_right_W_1.txt" , "TP1_6m_right_Y_1.txt" , "TP1_6m_right_D_1.txt" , "TP1_7m_right_W_1.txt" , "TP1_7m_right_Y_1.txt" , "TP1_7m_right_D_1.txt" , "TP1_8m_right_W_1.txt" , "TP1_8m_right_Y_1.txt" , "TP1_8m_right_D_1.txt" };
string movPath [] = {  "../../videos/test1/TP1_1m_right.mov" , "../../videos/test1/TP1_1m_right.mov" , "../../videos/test1/TP1_1m_right.mov" , "../../videos/test1/TP1_2m_right.mov" , "../../videos/test1/TP1_2m_right.mov" , "../../videos/test1/TP1_2m_right.mov" , "../../videos/test1/TP1_3m_right.mov" , "../../videos/test1/TP1_3m_right.mov" , "../../videos/test1/TP1_3m_right.mov" , "../../videos/test1/TP1_4m_right.mov" , "../../videos/test1/TP1_4m_right.mov" , "../../videos/test1/TP1_4m_right.mov" , "../../videos/test1/TP1_5m_right.mov" , "../../videos/test1/TP1_5m_right.mov" , "../../videos/test1/TP1_5m_right.mov" , "../../videos/test1/TP1_6m_right.mov" , "../../videos/test1/TP1_6m_right.mov" , "../../videos/test1/TP1_6m_right.mov" , "../../videos/test1/TP1_7m_right.mov" , "../../videos/test1/TP1_7m_right.mov" , "../../videos/test1/TP1_7m_right.mov" , "../../videos/test1/TP1_8m_right.mov" , "../../videos/test1/TP1_8m_right.mov" , "../../videos/test1/TP1_8m_right.mov" };
int startFrame [] = {285,900,1050,250,850,1000,90,775,920,400,1010,1160,117,860,1040,430,820,990,115,750,935,140,415,500};
int endFrame []= {490,1050,1250,450,990,1200,260,920,1150,660,1160,1320,330,1040,1240,640,990,1200,305,935,1135,225,500,610};

bool printLegend = true;
string legend = "frameNumber initialPart backgroundSubtraction averageBackgroundUpdate thresholding blobdetection nrOfBlobs blobArea_1 centroidX_1 controidY_1 blobArea_2 centroidX_2 controidY_2 blobArea_3 centroidX_3 controidY_3";


//--------------------------------------------------------------
void testApp::setup(){
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,0,0),"../../images/testImage.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,0,0),"../../videos/test1/TP1_1m_right.mov",VIDEO));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,480,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,480,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj[1].play();
	vecGuiObj[1].setFrame(startFrame[testIterator]);

	roiPositions.push_back(vector<pos>());
	roiPositions[0].push_back(pos(0,0,0));
	roiPositions[0].push_back(pos(99,99,0));

	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
	avarageBackground = currentFrameOfImage;
	//test change for iteration 1
	contourImage.allocate(640,480);
	contourImageColor.allocate(640,480);
}

//--------------------------------------------------------------
void testApp::update(){
	vector<string> loggingData;
	clock_t lastTime = clock();
	string sTemp;
	ofImage normImg, bgSub, threshRGB;

	vecGuiObj[1].nextFrame();
	vecGuiObj[1].nextFrame();
	vecGuiObj[1].nextFrame();
	vecGuiObj[1].vidUpdate();

	if(vecGuiObj[1].getCurrentFrame() > endFrame[testIterator]){
		testIterator++;
		vecGuiObj[1].setVideo(movPath[testIterator]);
		vecGuiObj[1].setFrame(startFrame[testIterator]);
		vecGuiObj[1].play();
		currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());
		avarageBackground = currentFrameOfImage;
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

		loggingData.push_back(captureTime(lastTime));

		//segmentation Background
		 //Background Subtraction
		bgSub = gt_backgroundSubtraction(avarageBackground,currentFrameOfImage);
		loggingData.push_back(captureTime(lastTime));

		 //Updating the avarage background
		avarageBackground = gt_updateReference(avarageBackground, currentFrameOfImage, 0.8f);
		loggingData.push_back(captureTime(lastTime));

		//Segmentation: Binary Image
		threshRGB = thresholdRGB(bgSub,30,30,30);
		loggingData.push_back(captureTime(lastTime));

		//BLOB analasys
		//vector<BLOB> blobs = BLOBanalysis(threshRGB);
		contourImageColor.setFromPixels(threshRGB.getPixelsRef());
		contourImage = contourImageColor;
		contourFinder.findContours(contourImage,0,100,10,false,false);
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

		vecGuiObj[0].setImage(bgSub);
		vecGuiObj[2].setImage(threshRGB);
		vecGuiObj[3].setImage(currentFrameOfImage);

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
		ofCircle(contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y+480,1);
		ofCircle(contourFinder.blobs[i].centroid.x+640,contourFinder.blobs[i].centroid.y+480,1);
		ofSetColor(0,255,0);
		ofNoFill();

		ofRectangle r = contourFinder.blobs.at(i).boundingRect;
		r.y += 480;
		ofRect(r);
		r.x += 640;
		ofRect(r);

		ofSetColor(255,255,255);
	}

	//Draws the indentifier Text
	ofDrawBitmapStringHighlight("Video Feed",920,20);
	ofDrawBitmapStringHighlight("Segmentation: Foreground",200,20);
	ofDrawBitmapStringHighlight("Thresholded Image (with blobs)",160,500);
	ofDrawBitmapStringHighlight("Video feed with blobs",870,500);
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