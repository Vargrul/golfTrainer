#pragma once

#include "testApp.h"
#include "pos.h"

float BLOBcalculateVelocity(pos oldPos, pos newPos, int deltaTime);

/*
//The main function that takes in the binary input image and performs
// the connected componant analysis by calling other functions. Output is
// a vector of BLOBs.
vector<BLOB> BLOBanalysis(ofImage inputImg);

//Take in x and y along with the image and performs sequential analysis
// from the given position and returns a BLOB object.
BLOB connectedComponantAnalysis(int x, int y, ofImage& inputImg);
//Sets the colour of the pixel to 0.
void burnPixel(int x, int y, ofImage& inputImg, BLOB& blob);
//Checks the neighborhood for non-black pixels. Then stores then pixel and burns it
// Recursive
	void neighborCheck(int x, int y, ofImage& inputImg, BLOB& blob);
	*/