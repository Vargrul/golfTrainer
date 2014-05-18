#include "motionPrediction.h"

//Kalman resources on the internet:
	//http://bilgin.esme.org/BitsBytes/KalmanFilterforDummies.aspx
	//http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf

kfValues4x4 kfInitValues4x4(){
	kfValues4x4 outValues;

	//outValues.XkProj = 0;
	outValues.A = ofMatrix4x4(
		1.0f ,		0.0f ,		0.0f ,		0.0f ,
		0.0f ,		1.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.0f ,		1.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.0f ,		1.0f);
	//outValues.Xkm1 = 0;

	//outValues.PkProj = 0;
	outValues.Pkm1 = ofMatrix4x4(
		1.0f ,		0.0f ,		0.0f ,		0.0f ,
		0.0f ,		1.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.0f ,		1.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.0f ,		1.0f);
	outValues.H = ofMatrix4x4(
		1.0f ,		0.0f ,		0.0f ,		0.0f ,
		0.0f ,		1.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.0f ,		1.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.0f ,		1.0f);
	//outValues.Xkm1 = 0;
	outValues.Q = ofMatrix4x4(
		0.000001f , 0.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.000001f , 0.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.000001f , 0.0f ,
		0.0f ,		0.0f ,		0.0f ,		0.000001f);
	//outValues.Kk =0;
	outValues.R = ofMatrix4x4(
		0.2f ,		0.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.2f ,		0.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.2f ,		0.0f ,
		0.0f ,		0.0f ,		0.0f ,		0.2f);

	return outValues;
};

kfValuesFloat kfInitValuesFloat(){
	kfValuesFloat outValues;

	outValues.XkProj = 0.0f;
	outValues.Xk = 0.0f;
	outValues.A = 1.0f;
	outValues.Xkm1 = 0.0f;

	outValues.PkProj = 1.0f;
	outValues.Pkm1 = 1.0f;
	outValues.Pk = 1.0f;
	outValues.H = 1.0f;
	outValues.Xkm1 = 0.0f;
	outValues.Q = 0.000001f;
	outValues.Kk = 1.0f;
	outValues.R = 0.0001f;

	return outValues;
};

kfValues4x4 kfTimeUpdate4x4(kfValues4x4 inValues){
	kfValues4x4 outValues = inValues;
	//Project the state ahead
	outValues.XkProj = inValues.Xk;// + inValues.Wk;

	//Project the error covariance ahed
	outValues.PkProj = kfMatrixAddition4x4(inValues.Pkm1, inValues.Q);

	return outValues;
};

kfValuesFloat kfTimeUpdateFloat(kfValuesFloat inValues, float velocity){
	kfValuesFloat outValues = inValues;
	//Project the state ahead
	outValues.XkProj = inValues.Xk + velocity;// + inValues.Wk;

	//Project the error covariance ahed
	outValues.PkProj = inValues.Pk + inValues.Q;

	return outValues;
};


kfValues4x4 kfMeasurementUpdate4x4(kfValues4x4 inValues){
	kfValues4x4 outValues = inValues;
	//Compute the Kalman Gain
	outValues.Kk =  inValues.PkProj * kfMatrixAddition4x4(inValues.PkProj, inValues.R).getInverse();

	//Update the estimate via Zk
	outValues.Xk = kfMatrixAddition4x4(inValues.XkProj, inValues.Kk) * kfMatrixSubtraction4x4(inValues.Zk, inValues.XkProj);

	//Update the error covariance
	outValues.Pk = kfMatrixSubtraction4x4(1.0f, inValues.Kk) * inValues.PkProj;

	return outValues;
};

kfValuesFloat kfMeasurementUpdatFloat(kfValuesFloat inValues){
	kfValuesFloat outValues = inValues;
	//Compute the Kalman Gain
	outValues.Kk =  inValues.PkProj / (inValues.PkProj + inValues.R);

	//Update the estimate via Zk
	outValues.Xk = inValues.XkProj + outValues.Kk * (inValues.Zk - inValues.XkProj);

	//Update the error covariance
	outValues.Pk = (1.0f - outValues.Kk) * inValues.PkProj;

	return outValues;
};

ofMatrix4x4 kfMatrixAddition4x4(ofMatrix4x4 a, ofMatrix4x4 b){
	ofMatrix4x4 c;
	for(int i = 0 ; i < 4 ; i++){
		for (int ii = 0; ii < 4; ii++){
			c(i,ii) = a(i,ii) + b(i,ii);
		}
	}
	return c;
}

ofMatrix4x4 kfMatrixSubtraction4x4(ofMatrix4x4 a, ofMatrix4x4 b){
	ofMatrix4x4 c;
	for(int i = 0 ; i < 4 ; i++){
		for (int ii = 0; ii < 4; ii++){
			c(i,ii) = a(i,ii) - b(i,ii);
		}
	}
	return c;
}
ofMatrix4x4 kfMatrixSubtraction4x4(float a, ofMatrix4x4 b){
	ofMatrix4x4 c;
	for(int i = 0 ; i < 4 ; i++){
		for (int ii = 0; ii < 4; ii++){
			c(i,ii) = a - b(i,ii);
		}
	}
	return c;
}