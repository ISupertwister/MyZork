#include"inventory.h"
#include"item.h"
#include<iostream>

using namespace std;

Inventory::Inventory(Character* character) : character(character) {
    
}

void Inventory::addItem(const Item & item) {
	items.push_back(item);
	cout << item.name << " has been added to your inventory" << endl;
	//Taking an item.

    if (item.name == "Veteran Sword") {
        character->modifyDamage(5); //+5 damage
        cout << "Your damage has increased by 5 due to the Veteran Sword!" << endl;
    }
    if (item.name == "Silver Sword") {
        character->modifyDamage(10); //+10 damage
        cout << "Your damage has increased by 10 due to the Silver Sword! You are now a dual sword user!" << endl;
    }
    if (item.name == "Enhanced Necklace") {
        character->modifyStat("magic", 1); //+1 magic
        cout << "Your magic has increased by 1 due to the Enhanced Necklace!" << endl;
    }

}

void Inventory::dropItem(const string & itemName) { 
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == itemName) {
            cout << it->name << " has been removed from your inventory.\n";
            items.erase(it);
            return;
        }
    }
    cout << itemName << " not found in your inventory."<<endl;
    //droping an item
}

void Inventory::showInventory() const {
    cout << "Your inventory:" << endl;
    if (items.empty()) {
        cout << " - Empty - "<< endl;
        return;
    }
    for (const auto & item : items) {
        cout << "- " << item.name << ": " << item.description << endl;
    }
}
void Inventory::removeItem(const string& itemName) {
    auto it = find_if(items.begin(), items.end(), [&itemName](const Item& item) {
        return item.name == itemName;
        });

    if (it != items.end()) {
        items.erase(it);
        cout << itemName << " has been removed from your inventory." << endl;
    }
    else {
        cout << "Item not found in inventory." << endl;
    }
}
