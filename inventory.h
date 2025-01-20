#ifndef inventory_h
#define inventory_h

#include<vector>
#include"item.h"
#include"character.h"

class Inventory {
private:
	std::vector<Item> items;
	Character* character;

public:
	Inventory(Character* character);

	void addItem(const Item& item);//Taking an item.

	void dropItem(const string& itemName);//Droping an item.

	void removeItem(const string& itemName);

	void showInventory()const;//Player can see the items he/she owns.

	bool containsItem(const std::string& itemName) const;
};

#endif