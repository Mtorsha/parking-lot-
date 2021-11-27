#pragma once
#ifndef MAIN_H
#define MAIN_H
#include "WidgetComposite.h"
#include "wx/wx.h"
#include "wx/event.h"
#include "wx/string.h"
#include "wx/thread.h"
#include <future>
#include "ParkingLotFactory.h"
#include "StaticPanelFactory.h"
#include "DBObject.h"
#include "WidgetEditor.h"
#include "WidgetBuilder.h"
#include "TimerFunctions.h"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class main : public wxFrame
{
public:
	main();
	~main();

private:
	// build the side panel on the map
	void buildSidePanel()
	{
		for (size_t i = 0; i < lotReferences.size(); i++)
		{
			// this displays all the lot info on teh side and a search later on
		}
	}

// building the popup lot frame based on the point of the button
	void buildParkingLotDisplay(wxPoint point, wxString wxName);
// Login screen widgets
public:
	Panel* LoginPanel = StaticPanelFactory::makePanel("login");
// notification frame widgets
public:
	wxFrame* notif_frame = nullptr;
// parking lot frame & widgets
public:
	DBObject db;
	future<void> value;
	TimerFunctions timer;
	WidgetEditor editor;
	Panel* LotPanel = StaticPanelFactory::makePanel("lot");
	wxFrame* lot_frame = nullptr;
	wxComboBox* timeStartOptions = nullptr;
	wxComboBox* timeEndOptions = nullptr;
	vector<wxString> timeStart;
	vector<wxString> timeEnd; 
	wxButton* xButton = nullptr;
	vector<wxString> lotReferences = { "A","B","C","D","E","F","G","H","I","J"};

//parking map widgets
public:
	Panel* MapPanel = StaticPanelFactory::makePanel("map");
	wxPNGHandler* HeaderHandlerPNG = nullptr;
	unordered_map<string, ParkingLot*> pLots;

	void buildEndTime(wxCommandEvent& evt);

	// Search for a time to start
	void getStartLotTime(vector<wxString> &timeStart)
	{
		timeStart.clear();
		timer.setCurrentTime();
		timeStart = timer.returnComboOptions(timeStart, timer.returnHour(), timer.returnMin());
	}

	string wxStringTostring(wxString msg)
	{
		// turns a wxString to a regular string
		return string(msg.mb_str(wxConvUTF8));
	}
	void printToOutputStream(string message) 
	{	
		//saving this for later to print to output
		std::wstring stemp = std::wstring(message.begin(), message.end());
		LPCWSTR sw = stemp.c_str();
		OutputDebugString(sw);
	}
	
	bool checkAvailableSpots(ParkingLot* Lot) //checkAvailableSpots(wxString availableSpots)
	{
		if (!Lot->checkIsLotFull())// (wxAtoi(availableSpots) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	void buildLoginPanel();
	void buildParkingMap();
	/*
	wxString buildAvailableSPots(wxString wxLotName)
	{
		//replace function here to get lot information
		reservedSpots = "30";
		availableSpots = "10";
		pspotText = "The detailed information for this available spot is: \n   Available spots: " + reservedSpots + wxString(" Reserved spots: ") + availableSpots;
		return pspotText;
	}
	*/

	void OnLoginSubmit(wxCommandEvent& evt);
	void OnReserveClick(wxCommandEvent& evt);
	void OnLotClick(wxCommandEvent& evt);
	void TestAsync();
	void onClickX(wxCommandEvent& evt)
	{
		if (evt.GetId() == 2)
		{
			lot_frame->Destroy();
			delete lot_frame;
		}
		else
		{
			notif_frame->Destroy();
		}
	}
	wxPoint getEventPointer(wxCommandEvent& evt)
	{
		wxBitmapButton* button = wxDynamicCast(evt.GetEventObject(), wxBitmapButton);
		return button->GetPosition();;
	}
	wxString getEventName(wxCommandEvent& evt)
	{
		if (evt.GetId() == 3)
		{
			wxBitmapButton* button = wxDynamicCast(evt.GetEventObject(), wxBitmapButton);
			return button->GetName();
		}
		else
		{
			wxButton* button = wxDynamicCast(evt.GetEventObject(), wxButton);
			return button->GetName();
		}
	}
	virtual bool checkLogin(string name, string pass)
	{
		string response = db.checkLogin(name, pass);
		// replace with real login check later
		if (response == "success")
		{
			return true;
		}
		return false;
	}
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H