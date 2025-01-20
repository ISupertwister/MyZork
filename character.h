#ifndef character_h
#define character_h

#include <string>

using namespace std;

class Character {

private:
	int baseHealth;     //Health
	int baseDamageMin;  //Min Damage
	int baseDamageMax;  //Max Damage
	double critRate;    //Crit Rate
	double critDamage;  //Crit Damage
public:
	int strength;//increase your health and damage.
	//for example: str = 5, health is 100 and base damage is 10-15. str = 10, health is 200 and base damage is 20-30.
	//After winning a battle, your health will be replenished.
	int magic;//necessary for some actions.
	//if you have at least 5 magic, you will have a buff at final boss fight.
	int ability;//crit damage +%10 for each point.
	//for example: ability = 5, crit damage is %200. ability = 10, crit damage is %250.
	int composure;//crit rate +%3 for each point.
	//for example: composure = 5, crit rate is %15. composure = 10, crit rate is %30.
	int wisdom;//necessary for some actions.

	int currentHealth;

	Character();

	void showStats();
	int calculateDamage() const;
	void takeDamage();
	bool isCriticalHit() const; 
	void replenishHealth();
	void modifyStat(const string & attribute, int value);
	void modifyDamage(int value);
	void takeDamage(int damage);
};

#endif