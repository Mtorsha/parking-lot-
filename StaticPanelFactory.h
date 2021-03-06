#pragma once
#ifndef STATICPANELFACTORY_H
#define STATICPANELFACTORY_H
#include <string>
#include "LoginPanel.h"
#include "MapPanel.h"
#include "LotPanel.h"
#include "ratingPanel.h"
// static factory for creating the different UI panels
class StaticPanelFactory
{
	public:
		static Panel* makePanel(string name)
		{
			Panel* panel;
			if (name == "login")
			{
				panel = new LoginPanel();
			}
			else if (name == "map")
			{
				panel = new MapPanel();
			}
			else if (name == "lot")
			{
				panel = new LotPanel();
			}
			else if (name == "rating")
			{
				panel = new ratingPanel();
			}
			else
			{
				panel = NULL;
			}
			return panel;
		}
};

#endif // !STATICPANELFACTORY_H