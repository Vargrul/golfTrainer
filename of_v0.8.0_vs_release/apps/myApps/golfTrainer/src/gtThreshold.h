#pragma once

#include "testApp.h"
#include <tuple>

ofImage threshold(ofImage imgIn, float hueMinIn, float hueMaxIn, float satMinIn, float satMaxIn, float brigMinIn, float brigMaxIn);

tuple<float,float,float,float,float,float> adapThresVal(ofImage imgIn);