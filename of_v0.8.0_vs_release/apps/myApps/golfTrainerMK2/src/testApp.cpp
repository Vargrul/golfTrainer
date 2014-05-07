#include "testApp.h"
	
vector<guiObj> vecGuiObj;
ofImage currentFrameOfImage;
vector<vector<int>> integralImage;
vector <ofImage> pastFrames;
ofImage avarageBackground;
vector<vector<pos>> roiPositions;
ofxCvContourFinder contourFinder;

string timing;
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
}

//--------------------------------------------------------------
void testApp::update(){
	clock_t start = clock();
	unsigned int msElapsed;
	clock_t timeElapsed;
	string sTemp;
	ofImage normImg, bgSub, threshRGB;

	vecGuiObj[1].vidUpdate();
	vecGuiObj[1].nextFrame();

	//The flow of the program
	//Input
	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());

	//Segmentation: Foreground
	//1: needing a vector with the frames used to make an avarageBackground.
	
	if(pastFrames.size() >= 3){
		pastFrames.pop_back();
		pastFrames.insert(pastFrames.begin(),currentFrameOfImage);
	}else{
		pastFrames.insert(pastFrames.begin(),currentFrameOfImage);
	}

	//Timing from the start of the update loop to this part
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();

	if(pastFrames.size() > 1) avarageBackground = gt_averageBackground(pastFrames);

	//Delta time from last timing
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();

	bgSub = gt_backgroundSubtraction(avarageBackground,currentFrameOfImage);

	//Delta time from last timing
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();
	
	//Segmentation: Binary Image
	threshRGB = thresholdRGB(bgSub,40,40,40);

	//Delta time from last timing
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();

	
	//Integral Image
	integralImage.clear();
	img2integralImg(threshRGB, MEAN, integralImage);

	//Delta time from last timing
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();

	//Roi Limiter
	//TO-DO: Change the way the roiLimiter makes a decition of how interesting the ROI is
	roiPositions.clear();
	if(pastFrames.size() > 2) roiLimiter(integralImage, roiPositions);

	for(int i = 0 ; i < roiPositions.size() ; i++){
		cout << roiPositions[i][0].getX() << "x" << roiPositions[i][0].getY() << "	";
	}
	cout << endl;

	//Delta time from last timing
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();

	//Normalize ROIs
	//Is it needed? or is it only time consuming?
	//if(pastFrames.size() > 1)normImg = normalizeROI(roiPositions,bgSub);
	
	//Delta time from last timing
	timeElapsed = clock() - start;
	msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
	sTemp = to_string(timeElapsed);
	timing.append(sTemp + " | ");
	start = clock();
	
	//Probability Map



	//BLOB analasys
	//vector<BLOB> blobs = BLOBanalysis(threshRGB);
	ofxCvGrayscaleImage contourImage;
	ofxCvColorImage contourImageColor;
	contourImageColor.setFromPixels(threshRGB.getPixelsRef());
	contourImage = contourImageColor;
	contourFinder.findContours(contourImage,0,100,10,false,false);



	cout << contourFinder.nBlobs << endl;

	vecGuiObj[0].setImage(bgSub);
	vecGuiObj[2].setImage(threshRGB);
	//vecGuiObj[3].setImage(normImg);

	cout << legend << endl;
	cout << timing  << endl;
	timing.clear();
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

		ofCircle(contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y+480,3);
		
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