#include "pos.h"

pos::pos(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
};
pos::pos(float xi,float yi,float zi){
	x = xi;
	y = yi;
	z = zi;
};

void pos::setX(float in){x = in;};
float pos::getX(){return x;};

void pos::setY(float in){y = in;};
float pos::getY(){return y;};

void pos::setZ(float in){z = in;};
float pos::getZ(){return z;};