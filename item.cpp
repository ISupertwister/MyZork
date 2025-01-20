#include"item.h"
#include<iostream>

using namespace std;

Item::Item(string itemName, string itemDescription, int itemValue)
	: name(itemName), description(itemDescription), value(itemValue) {}

void Item::showDetails()const {
	cout << "Item: " << name << endl;
	cout << "Description: " << description << endl;
	cout << "Value: " << value << endl;
}