#pragma once

#include "ofMain.h"
#include "guiObj.h"
#include "img2integralImg.h"
#include "backgroundSub.h"
#include "roiLimiter.h"
#include "normalization.h"
#include "gtThreshold.h"
#include "BLOB.h"
#include "BLOBanalysis.h"

#include <iostream>
#include <fstream>
#include <string>

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};

void guiUpdate();