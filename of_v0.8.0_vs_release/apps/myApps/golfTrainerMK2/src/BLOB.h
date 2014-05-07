#pragma once

#include "testApp.h"
#include "pos.h"

class BLOB{
	vector<pos> pixellist;
public:
	BLOB();

	void addPixel(pos i);
	pos getPixel(int i);

};