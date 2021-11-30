#ifndef LotC_H
#define LotC_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotC : public ParkingLot
{
	bool isLotFull;
	const string LotName = "C";
	const int TotalNoOfSpots = 100;
	static LotC* c_instance;
	vector<ParkingSpace*> pSpaceC;

	LotC()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceC.push_back(new ParkingSpace(100, 100));
		}
	}
public:
	string getLotName();
	
	int getTotalNoOfSpots();
	
	bool checkIsLotFull();
	
	static LotC* getInstance();
	
	bool reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

};

#endif