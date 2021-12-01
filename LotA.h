#ifndef LotA_H
#define LotA_H
#include <iostream>
#include <vector>
#include <ctime>
#include "ParkingLot.h"
#include "ParkingSpace.h"
using namespace std;

class LotA : public ParkingLot
{
	bool isLotFull;
	const string LotName = "A";
	const int TotalNoOfSpots = 50;
	static LotA* a_instance;
	vector<ParkingSpace*> pSpaceA;

	LotA()
	{
		isLotFull = false;

		for (int i = 0; i < TotalNoOfSpots; i++)
		{
			// Create parking space objects 
			pSpaceA.push_back(new ParkingSpace(100, 100, LotName,i));
		}
	}
public:
	string getLotName();

	int getTotalNoOfSpots();

	bool checkIsLotFull();

	static LotA* getInstance();

	bool reserve(time_t startTime, time_t endTime);

	int getAvaialbleSlots(time_t startTime);

};

#endif