#pragma once
#ifndef TIMERFUNCTIONS_H
#define TIMERFUNCTIONS_H
#include "wx/wx.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>   

using namespace std;

class TimerFunctions
{
public:
	TimerFunctions()
	{

	}
	~TimerFunctions()
	{

	}
	void setCurrentTime();
	int returnHour();
	int returnMin();
	int returnTimeLeft(string timeEnd);
	vector<wxString> returnComboOptions(vector<wxString> vectorStringToadd, int Hours, int Minutes);
	vector<wxString> returnComboOptionsForEndTime(vector<wxString> vectorStringToadd, int Hours, int Minutes, int count_blocks);
	time_t convertChoiceTime(string choice);
protected:
	int Hour = 0;
	int Min = 0;
};

#endif // !TIMERFUNCTIONS_H