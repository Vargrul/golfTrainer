#include "testApp.h"
	
vector<guiObj> vecGuiObj;
ofImage currentFrameOfImage;
vector<vector<int>> integralImage;
vector <ofImage> pastFrames;
ofImage avarageBackground;

//--------------------------------------------------------------
void testApp::setup(){
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,0,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,0,0),"../../videos/th1_55w.mov",VIDEO));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(0,480,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(640,480,0),"../../images/testSquare.png",IMAGE));
	//vecGuiObj[1].play();
	vecGuiObj[1].setFrame(100);
	vecGuiObj[0].setImgFromPixels(vecGuiObj[1].getPixelsRef());
	vecGuiObj[1].setFrame(75);
}

//--------------------------------------------------------------
void testApp::update(){
	vecGuiObj[1].vidUpdate();
	vecGuiObj[1].nextFrame();

	//The flow of the program
	//Input
	currentFrameOfImage.setFromPixels(vecGuiObj[1].getPixelsRef());

	//Segmentation: Foreground
	//1: needing a vector with the frames used to make an avarageBackground.
	
	if(pastFrames.size() >= 5){
		pastFrames.pop_back();
		pastFrames.insert(pastFrames.begin(),currentFrameOfImage);
	}else{
		pastFrames.insert(pastFrames.begin(),currentFrameOfImage);
	}

	if(pastFrames.size() > 1) avarageBackground = gt_averageBackground(pastFrames);
	vecGuiObj[3].setImage(avarageBackground);

	vecGuiObj[2].setImage(gt_backgroundSubtraction(avarageBackground,currentFrameOfImage));
	
	//Integral Image

	//Roi Limiter

	//Normalize ROIs

	//Probability Map

	//Segmentation: Binary Image

	//BLOB analasys

	
}

//--------------------------------------------------------------
void testApp::draw(){
	//Draws all guiObjects in vecGuiObj
	for(int i = 0 ; i < vecGuiObj.size() ; i++)
	{ 
		vecGuiObj[i].draw();
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
	if(button == 0){



		for(int i = 0 ; i < vecGuiObj.size() ; i++)
		{ 
			if(vecGuiObj[i].mouseCheck(x,y) == true){
				//do something
			}
		}
	}
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