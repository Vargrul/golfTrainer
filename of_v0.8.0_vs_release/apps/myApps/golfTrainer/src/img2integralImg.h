#pragma once

#include "testApp.h"
#include <tuple>

enum colorImg2integral{ RED , GREEN , BLUE , MEAN };

void img2integralImg(ofImage inputImage, colorImg2integral computedColor, vector<vector<int>>& outputLookuptable);