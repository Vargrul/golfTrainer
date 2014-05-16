#pragma once

#include "testApp.h"

struct kfValues{
	//Varibale for projected state
	ofMatrix4x4 XkProj;		//Projected state
	ofMatrix4x4 A;
	ofMatrix4x4 Xkm1;			//Last estiamted state
	ofMatrix4x4 Wk;			//Standart Diviation
	//Variables for projected error covariance
	ofMatrix4x4 PkProj;		//Projected error covariance
	ofMatrix4x4 Pkm1;			//Last estimated error covariance
	ofMatrix4x4 Q ();		//process noise covariance *NOTE* should be set as a const

	//Variables for Kalman Gain
	ofMatrix4x4 Kk;			//Kalman Gain
	ofMatrix4x4 PkProj;		//Last projected error convariance
	ofMatrix4x4 R;		//Enviroment noise *NOTE* should be set as a const
	//Variables for updating etimation wiht new input
	ofMatrix4x4 Xk;			//Updated estimation
	ofMatrix4x4 XkProj;		//Last projected estimation
	ofMatrix4x4 Zk;			//New input reading
	ofMatrix4x4 H;
	//Variable used to update the error covariance
	ofMatrix4x4 Pk;			//Updated error covariance
};

kfValues kfTimeUpdate();
kfValues kfMeasurementUpdate();