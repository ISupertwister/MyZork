#ifndef item_h
#define item_h

#include<string>
#include <map>
#include <vector>
#include "item.h"

using namespace std;

class Item {
public:
	string name;
	string description;
	map<string, pair<int, vector<string>>> connections;
	int value;

	Item(string itemName, string itemDescription, int itemValue);

	void showDetails() const;
};

#endif
