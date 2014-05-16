#include "motionPrediction.h"

//Kalman resources on the internet:
	//http://bilgin.esme.org/BitsBytes/KalmanFilterforDummies.aspx
	//http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf

kfValues kfInitValues(){
	kfValues outValues;

	outValues.XkProj = 0;
	outValues.A = ofMatrix4x4(
		1.0f ,		0.0f ,		0.0f ,		0.0f ,
		0.0f ,		1.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.0f ,		1.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.0f ,		1.0f);
	outValues.Xkm1 = 0;

	outValues.PkProj = 0;
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
	outValues.Xkm1 = 0;
	outValues.Q = ofMatrix4x4(
		0.000001f , 0.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.000001f , 0.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.000001f , 0.0f ,
		0.0f ,		0.0f ,		0.0f ,		0.000001f);
	outValues.Kk = 0;
	outValues.R = ofMatrix4x4(
		0.2f ,		0.0f ,		0.0f ,		0.0f ,
		0.0f ,		0.2f ,		0.0f ,		0.0f ,
		0.0f ,		0.0f ,		0.2f ,		0.0f ,
		0.0f ,		0.0f ,		0.0f ,		0.2f);

	return outValues;
};

kfValues kfTimeUpdate(kfValues inValues){
	kfValues outValues = inValues;
	//Project the state ahead
	outValues.XkProj = inValues.Xkm1;// + inValues.Wk;

	//Project the error covariance ahed
	outValues.PkProj = kfMatrixAddition(inValues.Pkm1, inValues.Q);

	return outValues;
};


kfValues kfMeasurementUpdate(kfValues inValues){
	kfValues outValues = inValues;
	//Compute the Kalman Gain
	outValues.Kk =  inValues.PkProj * kfMatrixAddition(inValues.PkProj, inValues.R).getInverse();

	//Update the estimate via Zk
	outValues.Xk = kfMatrixAddition(inValues.XkProj, inValues.Kk) * kfMatrixSubtraction(inValues.Zk, inValues.XkProj);

	//Update the error covariance
	outValues.Pk = kfMatrixSubtraction(1.0f, inValues.Kk) * inValues.PkProj;

	return outValues;
};

ofMatrix4x4 kfMatrixAddition(ofMatrix4x4 a, ofMatrix4x4 b){
	ofMatrix4x4 c;
	for(int i = 0 ; i < 4 ; i++){
		for (int ii = 0; ii < 4; ii++){
			c(i,ii) = a(i,ii) + b(i,ii);
		}
	}
	return c;
}

ofMatrix4x4 kfMatrixSubtraction(ofMatrix4x4 a, ofMatrix4x4 b){
	ofMatrix4x4 c;
	for(int i = 0 ; i < 4 ; i++){
		for (int ii = 0; ii < 4; ii++){
			c(i,ii) = a(i,ii) - b(i,ii);
		}
	}
	return c;
}
ofMatrix4x4 kfMatrixSubtraction(float a, ofMatrix4x4 b){
	ofMatrix4x4 c;
	for(int i = 0 ; i < 4 ; i++){
		for (int ii = 0; ii < 4; ii++){
			c(i,ii) = a - b(i,ii);
		}
	}
	return c;
}