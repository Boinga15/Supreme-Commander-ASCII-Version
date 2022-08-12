#include<string>
#include<vector>

#pragma once
#define UNIT_H
#ifdef UNIT_H

struct Action {
	std::string name;
	std::string attackID;
	int stat1;
	int stat2;
	int stat3;

	Action(std::string name_c, std::string attackID_c, int stat1_c, int stat2_c, int stat3_c) :name(name_c),attackID(attackID_c),stat1(stat1_c),stat2(stat2_c),stat3(stat3_c){}
};

class Unit {
public:
	int xpos;
	int ypos;
	int owningPlayer;
	int factionID;

	int health;
	int maxHealth;
	int antiAir;
	int radarRange;

	std::string name;
	std::string displayName; // Three-letter code displayed on the field.
	std::string description;

	bool isOverdrived;
	bool isShielded;
	bool isMarked;
	bool isAir;
	
	int auraHeal;
	int deathDamage;

	int movementRange;
	int movesLeft;
	bool canTakeAction;
	std::vector<Action> actions;

	Unit(int health_c, int radarRange_c, int moveSpeed_c, std::string name_c, std::string displayName_c, std::string description_c, std::vector<Action> actions_c, int auraHeal_c, int deathDamage_c, bool isAir_c, int antiAir_c, int xpos_c, int ypos_c, int factionID_c, int owningPlayer_c);
	void EndTurn(std::vector<std::vector<Unit>> units, std::vector<std::vector<std::string>> displayMap); // Function run at the end of a turn.
	std::vector<std::vector<int>> GetSpacesInRadar(std::vector<std::vector<std::string>> displayMap);
	std::string doAttack(Action Attack, std::vector<std::vector<Unit>> * units, int coordsx, int coordsy, std::vector<std::vector<std::string>> displayMap, int fowSettings);
	bool isSpaceInRange(int range, std::vector<std::vector<Unit>> units, std::string displayMap[15][15], int coordsx, int coordsy);

private:
	void doAuraHeal(std::vector<std::vector<Unit>> units); // Heals all nearby ally units.
	void doEnemyMark(std::vector<std::vector<Unit>> units, std::vector<std::vector<std::string>> displayMap); // Marks all enemies in radar.
	std::vector<std::vector<int>> GetSpacesInRange(std::vector<std::vector<std::string>> displayMap, int range);
};

#endif UNIT_H