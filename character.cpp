#include"character.h"
#include<iostream>
#include<cstdlib>

using namespace std;

Character::Character() :strength(6), magic(3), ability(5), composure(5), wisdom(5) {
	baseHealth = 100;
	baseDamageMin = 10;
	baseDamageMax = 15;

	critRate = 0.03 * composure;
	critDamage = 1.5 + (0.1 * ability);

	currentHealth = baseHealth + (strength * 20);
}

void Character::showStats() {
	cout << "Character Stats:" << endl;
	cout << "Health: " << currentHealth << "/" << (baseHealth + (strength * 20)) << endl;
	cout << "Damage: " << (baseDamageMin + strength) << "-" << (baseDamageMax + strength) << endl;
	cout << "Critical Rate: " << critRate * 100 << "%" <<endl;
	cout << "Critical Damage: " << critDamage * 100 << "%" << endl;
	cout << "Strength: " << strength << endl;
	cout << "Magic: " << magic << endl;
	cout << "Ability: " << ability << endl;
	cout << "Composure: " << composure << endl;
	cout << "Wisdom: " << wisdom << endl;
}

void Character::modifyStat(const string & attribute, int value) {
	if (attribute == "strength") {
		strength += value;
	}
	else if (attribute == "magic") {
		magic += value;
	}
	else if (attribute == "ability") {
		ability += value;
	}
	else if (attribute == "composure") {
		composure += value;
	}
	else if (attribute == "wisdom") {
		wisdom += value;
	}

	strength = max(0, min(10, strength));
	magic = max(0, min(10, magic));
	ability = max(0, min(10, ability));
	composure = max(0, min(10, composure));
	wisdom = max(0, min(10, wisdom));
}
void Character::modifyDamage(int value) {
	baseDamageMin += value; //Increase min damage.
	baseDamageMax += value; //Increase max damage.

	//Current damage.
	cout << "Your current damage: " << baseDamageMin + strength << "-" << baseDamageMax + strength << endl;
}
int Character::calculateDamage() const {
	int damage = baseDamageMin + strength + (rand() % (baseDamageMax - baseDamageMin + 1));
	if (isCriticalHit()) {
		cout << "Critical hit!\n";
		damage *= critDamage; //Apply the crit damage.
	}
	return damage;
}
void Character::takeDamage(int damage) {
	currentHealth -= damage;
}

bool Character::isCriticalHit() const {
	double randomValue = (rand() % 100) / 100.0; //Random value between 0.0 and 1.0
	return randomValue < critRate; //If the random value less then critRate,  apply crit hit.
}

//Replenish your HP after winning a battle.
void Character::replenishHealth() {
	currentHealth = baseHealth + (strength * 20);
	cout << "Health replenished to " << currentHealth << "!" << endl;
}