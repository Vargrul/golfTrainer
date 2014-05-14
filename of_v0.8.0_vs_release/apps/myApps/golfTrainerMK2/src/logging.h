#pragma once

#include "testApp.h"
#include <string>

//Log the given data to a file in "../logFiles/"+fileName
void logData(string fileName, vector<string> loggingData, char delimitor, bool writeLegend = false, string Legend = "");
//Output the loggingData to the console in the same maner as logData();
void logToConsole(vector<string> loggingData, char delimitor, bool writeLegend = false, string Legend = "");
//Returns a string with the time since last time in milliseconds and resets the input clock_t
string captureTime(clock_t &lastTime);