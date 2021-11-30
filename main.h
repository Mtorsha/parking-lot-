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
#include "User.h"
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
	Panel* ratingPanel = StaticPanelFactory::makePanel("rating");
// parking lot frame & widgets
public:
	wxFrame* lot_frame = nullptr;
	wxFrame* rating_frame = new wxFrame(this, wxID_ANY, "Rating Menu", wxDefaultPosition, wxSize(300, 200), NULL, "ratingMenu");
	future<void> value;
	future<void> notifParked;
	future<void> notifyleft;
	TimerFunctions timer;
	WidgetEditor editor;
	Panel* LotPanel = StaticPanelFactory::makePanel("lot");
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
	void OnLoginSubmit(wxCommandEvent& evt);
	void OnReserveClick(wxCommandEvent& evt);
	void OnLotClick(wxCommandEvent& evt);
	void notifyParked(int timer);
	void notifyLeft(int timer);
	void onClickX(wxCommandEvent& evt)
	{
		lot_frame->Destroy();
	}
	void onClickNotifX(wxCommandEvent& evt)
	{
		rating_frame->Hide();
	}
	void onClickRating(wxCommandEvent& evt)
	{
		switch (evt.GetId())
		{
			case 7:
				printToOutputStream("1 star");
				break;
			case 8:
				printToOutputStream("2 star");
				break;
			case 9:
				printToOutputStream("3 star");
				break;
			case 10:
				printToOutputStream("4 star");
				break;
			case 11:
				printToOutputStream("5 star");
				break;
			default:
				printToOutputStream("hit default");
		}

		rating_frame->Hide();
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
	void OnRegisterClick(wxCommandEvent& evt)
	{
		editor.hideNode(this, "Submit");
		editor.hideNode(this, "registerButton");
		editor.showNode(this, "completeRegistration");
		editor.showNode(this, "loginReturn");
		editor.changeLabel(this, "LogMsg", "Please enter a username/password to create account");
	}
	void OnRegisterConfirm(wxCommandEvent& evt)
	{
		if (canRegister(wxStringTostring(LoginPanel->getWidgetValue("username")), wxStringTostring(LoginPanel->getWidgetValue("password"))))
		{
			DBObject::instance()->createUser(wxStringTostring(LoginPanel->getWidgetValue("username")), wxStringTostring(LoginPanel->getWidgetValue("password")));
			editor.showNode(this, "Submit");
			editor.showNode(this, "registerButton");
			editor.hideNode(this, "completeRegistration");
			editor.hideNode(this, "loginReturn");
			editor.changeLabel(this, "LogMsg", "Please log in to start reserving your parking spot.");
			editor.changeLabel(this, "loginResponse", "Registration completed");
		}
	}
	void OnReturnClick(wxCommandEvent& evt)
	{
		editor.showNode(this, "Submit");
		editor.showNode(this, "registerButton");
		editor.hideNode(this, "completeRegistration");
		editor.hideNode(this, "loginReturn");
		editor.changeLabel(this, "LogMsg", "Please log in to start reserving your parking spot.");
		editor.changeLabel(this, "loginResponse", "");
	}
	virtual bool canRegister(string name, string pass)
	{
		if ((name.size() == 0) || (pass.size() == 0))
		{
			editor.changeLabel(this, "loginResponse", "Please fill out information before submitting");
			return false;
		}
		bool response = DBObject::instance()->checkUserExists(name);
		if (response)
		{
			editor.changeLabel(this, "loginResponse", "User account already exists");
			return false;
		}
		return true;
	}
	virtual bool checkLogin(string name, string pass)
	{
		string response = DBObject::instance()->checkLogin(name, pass);
		if (response == "success")
		{
			User::instance()->set_user(name);
			DBObject::instance()->isReserved(name);
			return true;
		}
		editor.changeLabel(this, "loginResponse", response);
		return false;
	}
	wxDECLARE_EVENT_TABLE();
};
#endif // !MAIN_H