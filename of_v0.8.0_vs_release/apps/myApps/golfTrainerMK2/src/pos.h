#pragma once

#include <iostream>

class pos{
	float x,y,z;
public:
	pos();
	pos(float,float,float);
	
	void setX(float);
	float getX();

	void setY(float);
	float getY();

	void setZ(float);
	float getZ();

	friend bool operator==(pos &lhs, pos &rhs);
	friend bool operator!=(pos &lhs, pos &rhs);
	friend std::ostream& operator<<(std::ostream& os, pos& dt);
};