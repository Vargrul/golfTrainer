#pragma once

#include "testApp.h"

ofImage gt_averageBackground(vector<ofImage> frames);

ofImage gt_backgroundSubtraction(ofImage backgroundImg, ofImage currentFrame);

ofImage gt_updateReference(ofImage backgroundImg, ofImage currentFrame, float gt_alpha = 0.95f);