#pragma once

#include "testApp.h"

enum colorImg2integral{ RED , GREEN , BLUE , MEAN };

void img2integralImg(ofImage inputImage, colorImg2integral computedColor, vector<vector<int>>& outputLookuptable);