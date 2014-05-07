#include "logging.h"

void logData(string fn, vector<string> ld, char dl, bool wlg, string lg){
	ofstream logFile;
	logFile.open("../logFiles/"+fn ,ios::out | ios::app);

	//writes the legend if needed
	if(wlg) logFile << lg << endl;

	for(int i = 0 ; i < ld.size() ; i++){
		logFile << ld[i];
		if(i != ld.size()-1) logFile << dl;
	}
	logFile << endl;

	logFile.close();
}

void logToConsole(vector<string> ld, char dl, bool wlg, string lg){
	//writes the legend if needed
	if(wlg) cout << lg << endl;

	for(int i = 0 ; i < ld.size() ; i++){
		cout << ld[i];
		if(i != ld.size()-1) cout << dl;
	}
	cout << endl;
}

string captureTime(clock_t lt){
	return to_string((clock() - lt) / (CLOCKS_PER_SEC / 1000));
}