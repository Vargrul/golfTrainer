#include "testApp.h"
	
vector<guiObj> vecGuiObj;

//--------------------------------------------------------------
void testApp::setup(){
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(10,10,0),"../../images/testSquare.png",IMAGE));
	vecGuiObj.insert(vecGuiObj.end(),guiObj(pos(200,200,0),"../../videos/th1_55w.mov",VIDEO));
	vecGuiObj[1].play();
}

//--------------------------------------------------------------
void testApp::update(){
	vecGuiObj[1].vidUpdate();
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