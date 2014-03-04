#pragma once

#include "testApp.h"
#include <tuple>

ofImage threshhold(ofImage imgIn, float hueMinIn, float hueMaxIn, float satMinIn, float satMaxIn, float brigMinIn, float brigMaxIn);

tuple<float,float,float,float,float,float> adapThreshVal(ofImage imgIn);