#pragma once

#include "testApp.h"
#include "pos.h"
//Normalizing an entire image
ofImage normalizeImage(ofImage inputImage);
//Normalizing inputROIs of the input image
ofImage normalizeROI(vector<vector<pos>> inputROIs, ofImage inputImage);
ofColor RGB2rgb(ofColor inputColor);