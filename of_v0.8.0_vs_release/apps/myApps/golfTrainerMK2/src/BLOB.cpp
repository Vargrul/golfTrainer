#include "BLOB.h"

BLOB::BLOB(){
};

void BLOB::addPixel(pos i){
	pixellist.push_back(i);
};

pos BLOB::getPixel(int i){
	return pixellist[i];
};