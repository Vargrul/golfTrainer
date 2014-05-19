#pragma once

#include "testApp.h"

struct kfValues4x4{
	//Varibale for projected state
	ofMatrix4x4 XkProj;		//Projected state
	ofMatrix4x4 A;
	ofMatrix4x4 Xkm1;			//Last estiamted state
	ofMatrix4x4 Wk;			//Standart Diviation
	//Variables for projected error covariance
	ofMatrix4x4 PkProj;		//Projected error covariance
	ofMatrix4x4 Pkm1;			//Last estimated error covariance
	ofMatrix4x4 Q;		//process noise covariance *NOTE* should be set as a const

	//Variables for Kalman Gain
	ofMatrix4x4 Kk;			//Kalman Gain
	ofMatrix4x4 R;		//Enviroment noise *NOTE* should be set as a const
	//Variables for updating etimation wiht new input
	ofMatrix4x4 Xk;			//Updated estimation
	ofMatrix4x4 Zk;			//New input reading
	ofMatrix4x4 H;
	//Variable used to update the error covariance
	ofMatrix4x4 Pk;			//Updated error covariance
};

struct kfValuesFloat{
	//Varibale for projected state
	float XkProj;		//Projected state
	float A;
	float Xkm1;			//Last estiamted state
	float Wk;			//Standart Diviation
	//Variables for projected error covariance
	float PkProj;		//Projected error covariance
	float Pkm1;			//Last estimated error covariance
	float Q;		//process noise covariance *NOTE* should be set as a const

	//Variables for Kalman Gain
	float Kk;			//Kalman Gain
	float R;		//Enviroment noise *NOTE* should be set as a const
	//Variables for updating etimation wiht new input
	float Xk;			//Updated estimation
	float Zk;			//New input reading
	float H;
	//Variable used to update the error covariance
	float Pk;			//Updated error covariance

};
//Simple prediction
pos posPredictionSimple(pos lastPos, pos newPos, pos& uncertaintyOut);

//Kalman filter
kfValues4x4 kfInitValues4x4();
kfValuesFloat kfInitValuesFloat();
kfValues4x4 kfTimeUpdate4x4(kfValues4x4 inValues);
kfValuesFloat kfTimeUpdateFloat(kfValuesFloat inValues, float velocity);
kfValues4x4 kfMeasurementUpdate4x4(kfValues4x4 inValues);
kfValuesFloat kfMeasurementUpdatFloat(kfValuesFloat inValues);
ofMatrix4x4 kfMatrixAddition4x4(ofMatrix4x4 a, ofMatrix4x4 b);
ofMatrix4x4 kfMatrixSubtraction4x4(ofMatrix4x4 a, ofMatrix4x4 b);
ofMatrix4x4 kfMatrixSubtraction4x4(float a, ofMatrix4x4 b);