#ifndef area_h
#define area_h

#include<string>
#include<map>
#include<vector>
#include"item.h"

using namespace std;

class Area {
public:
	string name;
	string description;
	map<string, pair<int, vector<string>>> connections;
	vector<Item> items; 
	bool visited;
	bool battleCompleted;
	bool itemsVisible;
	bool crowEventTriggered = false;
	bool crowEventCompleted = false;
	bool crowEventPostAction;


	Area(string areaName, string areaDescription);

	void describe();
	void triggerCrowEvent();
};

#endif
