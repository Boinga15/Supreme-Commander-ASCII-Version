#include "Unit.h"
#include<vector>
#include<string>
#include<iostream>

Unit::Unit(int health_c, int radarRange_c, int moveSpeed_c, std::string name_c, std::string displayName_c, std::string description_c, std::vector<Action> actions_c, int auraHeal_c, int deathDamage_c, bool isAir_c, int antiAir_c, int xpos_c, int ypos_c, int factionID_c, int owningPlayer_c) {
	this->maxHealth = health_c;
	this->health = this->maxHealth;
	this->radarRange = radarRange_c;
	this->movementRange = moveSpeed_c;
	this->movesLeft = this->movementRange;
	this->name = name_c;
	this->displayName = displayName_c;
	this->description = description_c;
	this->actions = actions_c;
	this->auraHeal = auraHeal_c;
	this->antiAir = antiAir_c;
	this->deathDamage = deathDamage_c;
	this->isAir = isAir_c;
	this->xpos = xpos_c;
	this->ypos = ypos_c;
	this->owningPlayer = owningPlayer_c;
	this->factionID = factionID_c;
	this->isOverdrived = false;
	this->isShielded = false;
	this->isMarked = false;
	this->canTakeAction = true;
}
void Unit::EndTurn(std::vector<std::vector<Unit>> units, std::vector<std::vector<std::string>> displayMap) {
	doAuraHeal(units);
	this->isMarked = false;
	if (this->isOverdrived) {
		this->health -= 1;
		if (this->health <= 1) {
			this->isOverdrived = false;
		}
	}
}

void Unit::doAuraHeal(std::vector<std::vector<Unit>> units) {
	if (this->ypos - 1 >= 0) {
		if (units[this->ypos - 1][this->xpos].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->ypos - 1 >= 0 && this->xpos + 1 <= 14) {
		if (units[this->ypos - 1][this->xpos + 1].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->ypos + 1 <= 14) {
		if (units[this->ypos + 1][this->xpos].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->ypos + 1 <= 14 && this->xpos + 1 <= 14) {
		if (units[this->ypos + 1][this->xpos + 1].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->xpos + 1 <= 14) {
		if (units[this->ypos][this->xpos + 1].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->ypos + 1 <= 14 && this->xpos - 1 >= 0) {
		if (units[this->ypos + 1][this->xpos - 1].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->xpos - 1 >= 0) {
		if (units[this->ypos][this->xpos - 1].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
	if (this->ypos - 1 >= 0 && this->xpos - 1 >= 0) {
		if (units[this->ypos - 1][this->xpos - 1].owningPlayer == this->owningPlayer) {
			units[this->ypos - 1][this->xpos].health += this->auraHeal;
			if (units[this->ypos - 1][this->xpos].health > units[this->ypos - 1][this->xpos].maxHealth) {
				units[this->ypos - 1][this->xpos].health = units[this->ypos - 1][this->xpos].maxHealth;
			}
		}
	}
}

void Unit::doEnemyMark(std::vector<std::vector<Unit>> units, std::vector<std::vector<std::string>> displayMap) {

}

std::vector<std::vector<int>> Unit::GetSpacesInRadar(std::vector<std::vector<std::string>> displayMap) {
	std::vector<std::vector<int>> foundSpaces;
	bool allowedDirections[8] = { true, true, true, true, true, true, true ,true };

	for (int i = 1; i < this->radarRange+1; i++) {
		if (allowedDirections[0] && this->ypos+i < 15) {
			if (displayMap[this->ypos+i][this->xpos] == "|||||") allowedDirections[0] = false;
			else foundSpaces.push_back({this->ypos + i, this->xpos});
		}
		if (allowedDirections[1] && this->xpos + i < 15 && this->ypos + i < 15) {
			if (displayMap[this->ypos + i][this->xpos + i] == "|||||") allowedDirections[1] = false;
			else foundSpaces.push_back({this->ypos + i, this->xpos + i});
		}
		if (allowedDirections[2] && this->xpos + i < 15) {
			if (displayMap[this->ypos][this->xpos + i] == "|||||") allowedDirections[2] = false;
			else foundSpaces.push_back({ this->ypos, this->xpos + i });
		}
		if (allowedDirections[3] && this->xpos + i < 15 && this->ypos - i >= 0) {
			if (displayMap[this->ypos - i][this->xpos + i] == "|||||") allowedDirections[3] = false;
			else foundSpaces.push_back({ this->ypos - i, this->xpos + i });
		}
		if (allowedDirections[4] && this->ypos - i >= 0) {
			if (displayMap[this->ypos - i][this->xpos] == "|||||") allowedDirections[4] = false;
			else foundSpaces.push_back({ this->ypos - i, this->xpos });
		}
		if (allowedDirections[5] && this->xpos - i >= 0 && this->ypos - i >= 0) {
			if (displayMap[this->ypos - i][this->xpos - i] == "|||||") allowedDirections[5] = false;
			else foundSpaces.push_back({ this->ypos - i, this->xpos - i });
		}
		if (allowedDirections[6] && this->xpos - i >= 0) {
			if (displayMap[this->ypos][this->xpos - i] == "|||||") allowedDirections[6] = false;
			else foundSpaces.push_back({ this->ypos, this->xpos - i });
		}
		if (allowedDirections[7] && this->xpos - i >= 0 && this->ypos + i < 15) {
			if (displayMap[this->ypos + i][this->xpos - i] == "|||||") allowedDirections[7] = false;
			else foundSpaces.push_back({ this->ypos + i, this->xpos - i });
		}
	}

	return foundSpaces;
}

std::vector<std::vector<int>> Unit::GetSpacesInRange(std::vector<std::vector<std::string>> displayMap, int range) {
	std::vector<std::vector<int>> foundSpaces;
	bool allowedDirections[8] = { true, true, true, true, true, true, true ,true };

	for (int i = 1; i < range + 1; i++) {
		if (allowedDirections[0] && this->ypos + i < 15) {
			if (displayMap[this->ypos + i][this->xpos] == "|||||") allowedDirections[0] = false;
			else foundSpaces.push_back({ this->ypos + i, this->xpos });
		}
		if (allowedDirections[1] && this->xpos + i < 15 && this->ypos + i < 15) {
			if (displayMap[this->ypos + i][this->xpos + i] == "|||||") allowedDirections[1] = false;
			else foundSpaces.push_back({ this->ypos + i, this->xpos + i });
		}
		if (allowedDirections[2] && this->xpos + i < 15) {
			if (displayMap[this->ypos][this->xpos + i] == "|||||") allowedDirections[2] = false;
			else foundSpaces.push_back({ this->ypos, this->xpos + i });
		}
		if (allowedDirections[3] && this->xpos + i < 15 && this->ypos - i >= 0) {
			if (displayMap[this->ypos - i][this->xpos + i] == "|||||") allowedDirections[3] = false;
			else foundSpaces.push_back({ this->ypos - i, this->xpos + i });
		}
		if (allowedDirections[4] && this->ypos - i >= 0) {
			if (displayMap[this->ypos - i][this->xpos] == "|||||") allowedDirections[4] = false;
			else foundSpaces.push_back({ this->ypos - i, this->xpos });
		}
		if (allowedDirections[5] && this->xpos - i >= 0 && this->ypos - i >= 0) {
			if (displayMap[this->ypos - i][this->xpos - i] == "|||||") allowedDirections[5] = false;
			else foundSpaces.push_back({ this->ypos - i, this->xpos - i });
		}
		if (allowedDirections[6] && this->xpos - i >= 0) {
			if (displayMap[this->ypos][this->xpos - i] == "|||||") allowedDirections[6] = false;
			else foundSpaces.push_back({ this->ypos, this->xpos - i });
		}
		if (allowedDirections[7] && this->xpos - i >= 0 && this->ypos + i < 15) {
			if (displayMap[this->ypos + i][this->xpos - i] == "|||||") allowedDirections[7] = false;
			else foundSpaces.push_back({ this->ypos + i, this->xpos - i });
		}
	}

	return foundSpaces;
}

std::string Unit::doAttack(Action Attack, std::vector<std::vector<Unit>>* units, int coordsx, int coordsy, std::vector<std::vector<std::string>> displayMap, int fowSettings) {
	int opposingPlayer = 1;
	if (this->owningPlayer == 1) {
		opposingPlayer = 2;
	}

	if (Attack.attackID == "Attack") {
		if (units[0][coordsy][coordsx].owningPlayer == opposingPlayer) {
			std::vector<std::vector<int>> reachableSpots = GetSpacesInRange(displayMap, Attack.stat2);
			bool canTarget = false;
			std::vector<int> targetSpot = { coordsy, coordsx };
			for (int i = 0; i < reachableSpots.size(); i++) {
				if (reachableSpots[i] == targetSpot) {
					canTarget = true;
					break;
				}
			}
			if (canTarget) {
				int damage = Attack.stat1;
				if (this->isOverdrived) { damage += 2; };
				if (units[0][coordsy][coordsx].isMarked) { damage = damage * 2; };
				if (units[0][coordsy][coordsx].isShielded) { damage = damage / 2; };
				if (units[0][coordsy][coordsx].isAir) { damage = damage / 2; };
				units[0][coordsy][coordsx].health -= damage;
				this->canTakeAction = false;
				return this->name + " successfully hit " + units[0][coordsy][coordsx].name + " and dealt " + std::to_string(damage) + " damage!";
			}
			else {
				return "Target is out of range!";
			}
		}
		else if (units[0][coordsy][coordsx].owningPlayer == this->owningPlayer) {
			return "That's your own unit!";
		}
		else {
			return "There's no unit there!";
		}
	}
	else if (Attack.attackID == "Overdrive") {
		if (!this->isOverdrived) {
			if (this->health <= 5) {
				return this->name + " doesn't have enough health to sustain overdrive!";
			}
			else {
				this->isOverdrived = true;
				this->health -= 5;
				this->canTakeAction = false;
				return this->name + " is now overdrived!";
			}
		}
		else {
			this->isOverdrived = false;
			this->canTakeAction = false;
			return this->name + " is no longer overdrived.";
		}
	}
	else if (Attack.attackID == "Repair") {
		if (units[0][coordsy][coordsx].owningPlayer == this->owningPlayer) {
			std::vector<std::vector<int>> reachableSpots = GetSpacesInRange(displayMap, 1);
			bool canTarget = false;
			std::vector<int> targetSpot = { coordsy, coordsx };
			for (int i = 0; i < reachableSpots.size(); i++) {
				if (reachableSpots[i] == targetSpot) {
					canTarget = true;
					break;
				}
			}
			if (canTarget) {
				units[0][coordsy][coordsx].health += Attack.stat1;
				if (units[0][coordsy][coordsx].health > units[0][coordsy][coordsx].maxHealth) {
					units[0][coordsy][coordsx].health = units[0][coordsy][coordsx].maxHealth;
				}
				this->canTakeAction = false;
				return this->name + " successfully repaired " + units[0][coordsy][coordsx].name + " by " + std::to_string(Attack.stat1) + " points of health!";
			}
			else {
				return "Target is out of range!";
			}
		}
		else if (units[0][coordsy][coordsx].owningPlayer == opposingPlayer) {
			return "That enemy is your opponent's unit!";
		}
		else {
			return "There's no unit there!";
		}
	}
	else if (Attack.attackID == "Boost") {
		if (this->movesLeft == this->movementRange) {
			return "This unit hasn't moved yet!";
		}
		else {
			this->movesLeft = this->movementRange;
			this->canTakeAction = false;
			return "Unit's move spaces restored!";
		}
	}
	else if (Attack.attackID == "Mark") {
		if (units[0][coordsy][coordsx].owningPlayer == opposingPlayer) {
			std::vector<std::vector<int>> reachableSpots = GetSpacesInRange(displayMap, 1);
			bool canTarget = false;
			std::vector<int> targetSpot = { coordsy, coordsx };
			for (int i = 0; i < reachableSpots.size(); i++) {
				if (reachableSpots[i] == targetSpot) {
					canTarget = true;
					break;
				}
			}
			if (canTarget) {
				units[0][coordsy][coordsx].isMarked = true;
				this->canTakeAction = false;
				return this->name + " successfully marked " + units[0][coordsy][coordsx].name + " for death!";
			}
			else {
				return "Target is out of range!";
			}
		}
		else if (units[0][coordsy][coordsx].owningPlayer == this->owningPlayer) {
			return "That's your own unit!";
		}
		else {
			return "There's no unit there!";
		}
	}
	else if (Attack.attackID == "AOE Attack") {
		std::vector<std::vector<int>> reachableSpots = GetSpacesInRange(displayMap, Attack.stat2);
		bool canTarget = false;
		std::vector<int> targetSpot = { coordsy, coordsx };
		for (int i = 0; i < reachableSpots.size(); i++) {
			if (reachableSpots[i] == targetSpot) {
				canTarget = true;
				break;
			}
		}
		if (canTarget) {
			int damageDealt = 0;
			int damageTemporary = 0;
			if (units[0][coordsy][coordsx].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat1;
				if (units[0][coordsy][coordsx].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][coordsy][coordsx].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][coordsy][coordsx].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][coordsy][coordsx].health -= damageTemporary;
			}
			if (coordsy - 1 >= 0) {
				if (units[0][coordsy - 1][coordsx].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy - 1][coordsx].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy - 1][coordsx].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy - 1][coordsx].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy - 1][coordsx].health -= damageTemporary;
				}
			}
			if (coordsy - 1 >= 0 && coordsx + 1 <= 14) {
				if (units[0][coordsy - 1][coordsx + 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy - 1][coordsx + 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy - 1][coordsx + 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy - 1][coordsx + 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy - 1][coordsx + 1].health -= damageTemporary;
				}
			}
			if (coordsy + 1 <= 14) {
				if (units[0][coordsy + 1][coordsx].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy + 1][coordsx].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy + 1][coordsx].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy + 1][coordsx].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy + 1][coordsx].health -= damageTemporary;
				}
			}
			if (coordsy + 1 <= 14 && coordsx + 1 <= 14) {
				if (units[0][coordsy + 1][coordsx + 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy + 1][coordsx + 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy + 1][coordsx + 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy + 1][coordsx + 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy + 1][coordsx + 1].health -= damageTemporary;
				}
			}
			if (coordsx + 1 <= 14) {
				if (units[0][coordsy][coordsx + 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy][coordsx + 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy][coordsx + 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy][coordsx + 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy][coordsx + 1].health -= damageTemporary;
				}
			}
			if (coordsy + 1 <= 14 && coordsx - 1 >= 0) {
				if (units[0][coordsy + 1][coordsx - 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy + 1][coordsx - 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy + 1][coordsx - 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy + 1][coordsx - 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy + 1][coordsx - 1].health -= damageTemporary;
				}
			}
			if (coordsx - 1 >= 0) {
				if (units[0][coordsy][coordsx - 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy][coordsx - 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy][coordsx - 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy][coordsx - 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy][coordsx - 1].health -= damageTemporary;
				}
			}
			if (coordsy - 1 >= 0 && coordsx - 1 >= 0) {
				if (units[0][coordsy - 1][coordsx - 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][coordsy - 1][coordsx - 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][coordsy - 1][coordsx - 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][coordsy - 1][coordsx - 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][coordsy - 1][coordsx - 1].health -= damageTemporary;
				}
			}
			if (damageDealt <= 0) {
				return "No units were hit!";
			}
			else {
				this->canTakeAction = false;
				return "Dealt " + std::to_string(damageDealt) + " damage to multiple units!";
			}
		}
		else {
			return "That spot is out of range!";
		}
	}
	else if (Attack.attackID == "Surround Attack") {
		int damageDealt = 0;
		int damageTemporary = 0;
		if (coordsy - 1 >= 0) {
			if (units[0][this->ypos - 1][this->xpos].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos - 1][this->xpos].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos - 1][this->xpos].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos - 1][this->xpos].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos - 1][this->xpos].health -= damageTemporary;
			}
		}
		if (this->ypos - 1 >= 0 && this->xpos + 1 <= 14) {
			if (units[0][this->ypos - 1][this->xpos + 1].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos - 1][this->xpos + 1].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos - 1][this->xpos + 1].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos - 1][this->xpos + 1].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos - 1][this->xpos + 1].health -= damageTemporary;
			}
		}
		if (this->ypos + 1 <= 14) {
			if (units[0][this->ypos + 1][this->xpos].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos + 1][this->xpos].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos + 1][this->xpos].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos + 1][this->xpos].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos + 1][this->xpos].health -= damageTemporary;
			}
		}
		if (this->ypos + 1 <= 14 && this->xpos + 1 <= 14) {
			if (units[0][this->ypos + 1][this->xpos + 1].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos + 1][this->xpos + 1].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos + 1][this->xpos + 1].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos + 1][this->xpos + 1].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos + 1][this->xpos + 1].health -= damageTemporary;
			}
		}
		if (this->xpos + 1 <= 14) {
			if (units[0][this->ypos][this->xpos + 1].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos][this->xpos + 1].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos][this->xpos + 1].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos][this->xpos + 1].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos][this->xpos + 1].health -= damageTemporary;
			}
		}
			if (this->ypos + 1 <= 14 && this->xpos - 1 >= 0) {
				if (units[0][this->ypos + 1][this->xpos - 1].owningPlayer == opposingPlayer) {
					damageTemporary = Attack.stat3;
					if (units[0][this->ypos + 1][this->xpos - 1].isMarked) { damageTemporary = damageTemporary * 2; };
					if (units[0][this->ypos + 1][this->xpos - 1].isShielded) { damageTemporary = damageTemporary / 2; };
					if (units[0][this->ypos + 1][this->xpos - 1].isAir) { damageTemporary = damageTemporary / 2; };
					damageDealt += damageTemporary;
					units[0][this->ypos + 1][this->xpos - 1].health -= damageTemporary;
				}
			}
		if (this->xpos - 1 >= 0) {
			if (units[0][this->ypos][this->xpos - 1].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos][this->xpos - 1].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos][this->xpos - 1].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos][this->xpos - 1].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos][this->xpos - 1].health -= damageTemporary;
			}
		}
		if (this->ypos - 1 >= 0 && this->xpos - 1 >= 0) {
			if (units[0][this->ypos - 1][this->xpos - 1].owningPlayer == opposingPlayer) {
				damageTemporary = Attack.stat3;
				if (units[0][this->ypos - 1][this->xpos - 1].isMarked) { damageTemporary = damageTemporary * 2; };
				if (units[0][this->ypos - 1][this->xpos - 1].isShielded) { damageTemporary = damageTemporary / 2; };
				if (units[0][this->ypos - 1][this->xpos - 1].isAir) { damageTemporary = damageTemporary / 2; };
				damageDealt += damageTemporary;
				units[0][this->ypos - 1][this->xpos - 1].health -= damageTemporary;
			}
		}
		if (damageDealt <= 0) {
			return "No units were hit!";
		}
		else {
			this->canTakeAction = false;
			return "Dealt " + std::to_string(damageDealt) + " damage to multiple units!";
		}
	}
	else if (Attack.attackID == "Detonation") {
	int damageDealt = 0;
	int damageTemporary = 0;
	if (coordsy - 1 >= 0) {
		if (units[0][this->ypos - 1][this->xpos].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos - 1][this->xpos].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos - 1][this->xpos].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos - 1][this->xpos].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos - 1][this->xpos].health -= damageTemporary;
		}
	}
	if (this->ypos - 1 >= 0 && this->xpos + 1 <= 14) {
		if (units[0][this->ypos - 1][this->xpos + 1].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos - 1][this->xpos + 1].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos - 1][this->xpos + 1].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos - 1][this->xpos + 1].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos - 1][this->xpos + 1].health -= damageTemporary;
		}
	}
	if (this->ypos + 1 <= 14) {
		if (units[0][this->ypos + 1][this->xpos].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos + 1][this->xpos].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos + 1][this->xpos].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos + 1][this->xpos].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos + 1][this->xpos].health -= damageTemporary;
		}
	}
	if (this->ypos + 1 <= 14 && this->xpos + 1 <= 14) {
		if (units[0][this->ypos + 1][this->xpos + 1].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos + 1][this->xpos + 1].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos + 1][this->xpos + 1].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos + 1][this->xpos + 1].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos + 1][this->xpos + 1].health -= damageTemporary;
		}
	}
	if (this->xpos + 1 <= 14) {
		if (units[0][this->ypos][this->xpos + 1].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos][this->xpos + 1].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos][this->xpos + 1].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos][this->xpos + 1].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos][this->xpos + 1].health -= damageTemporary;
		}
	}
	if (this->ypos + 1 <= 14 && this->xpos - 1 >= 0) {
		if (units[0][this->ypos + 1][this->xpos - 1].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos + 1][this->xpos - 1].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos + 1][this->xpos - 1].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos + 1][this->xpos - 1].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos + 1][this->xpos - 1].health -= damageTemporary;
		}
	}
	if (this->xpos - 1 >= 0) {
		if (units[0][this->ypos][this->xpos - 1].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos][this->xpos - 1].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos][this->xpos - 1].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos][this->xpos - 1].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos][this->xpos - 1].health -= damageTemporary;
		}
	}
	if (this->ypos - 1 >= 0 && this->xpos - 1 >= 0) {
		if (units[0][this->ypos - 1][this->xpos - 1].owningPlayer == opposingPlayer) {
			damageTemporary = Attack.stat3;
			if (units[0][this->ypos - 1][this->xpos - 1].isMarked) { damageTemporary = damageTemporary * 2; };
			if (units[0][this->ypos - 1][this->xpos - 1].isShielded) { damageTemporary = damageTemporary / 2; };
			if (units[0][this->ypos - 1][this->xpos - 1].isAir) { damageTemporary = damageTemporary / 2; };
			damageDealt += damageTemporary;
			units[0][this->ypos - 1][this->xpos - 1].health -= damageTemporary;
		}
	}
	if (damageDealt <= 0) {
		return "No units were hit!";
	}
	else {
		this->canTakeAction = false;
		this->health = -99;
		return "Dealt " + std::to_string(damageDealt) + " damage to multiple units!";
	}
	}
	else if (Attack.attackID == "Direct Air Attack") {
	if (units[0][coordsy][coordsx].owningPlayer == opposingPlayer) {
		std::vector<std::vector<int>> reachableSpots = GetSpacesInRange(displayMap, Attack.stat2);
		bool canTarget = false;
		std::vector<int> targetSpot = { coordsy, coordsx };
		for (int i = 0; i < reachableSpots.size(); i++) {
			if (reachableSpots[i] == targetSpot) {
				canTarget = true;
				break;
			}
		}
		if (canTarget) {
			if (units[0][coordsy][coordsx].isAir == false) {
				return "That unit is on the ground!";
			}
			else {
				int damage = Attack.stat1;
				if (this->isOverdrived) { damage += 2; };
				if (units[0][coordsy][coordsx].isMarked) { damage = damage * 2; };
				if (units[0][coordsy][coordsx].isShielded) { damage = damage / 2; };
				units[0][coordsy][coordsx].health -= damage;
				this->canTakeAction = false;
				return this->name + " successfully hit " + units[0][coordsy][coordsx].name + " and dealt " + std::to_string(damage) + " damage!";
			}
		}
		else {
			return "Target is out of range!";
		}
	}
	else if (units[0][coordsy][coordsx].owningPlayer == this->owningPlayer) {
		return "That's your own unit!";
	}
	else {
		return "There's no unit there!";
	}
	}
	else if (Attack.attackID == "AOE Air Attack") {
		bool canDoAttack = true;
		if (fowSettings == 0) {
			if (displayMap[coordsy][coordsx] == "#####") {
				canDoAttack = false;
			}
		}
		if (displayMap[coordsy][coordsx] == "|||||") {
			canDoAttack = false;
		}
		if (canDoAttack) {
			if (units[0][coordsy][coordsx].owningPlayer != opposingPlayer || units[0][coordsy][coordsx].isAir) {
				if (fowSettings == 1) {
					this->canTakeAction = false;
					return "The attack was carried out, but nothing was hit!";
				}
				else {
					return "Invalid target! Either that isn't the enemy or that unit is in the air!";
				}
			}
			else {
				std::vector<std::vector<int>> spotsToCheck = GetSpacesInRange(displayMap, 15);
				int damageTaken = 0;
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						if (units[0][i][j].antiAir > 0) {
							std::vector<std::vector<int>> inRangeAntiAir = units[0][i][j].GetSpacesInRadar(displayMap);
							bool canTarget = false;
							std::vector<int> targetSpot = { coordsy, coordsx };
							for (int k = 0; k < inRangeAntiAir.size(); k++) {
								if (inRangeAntiAir[k] == targetSpot) {
									canTarget = true;
									break;
								}
							}
							if (canTarget) {
								damageTaken += units[0][i][j].antiAir;
							}
						}
					}
				}
				this->health -= damageTaken;
				if (this->health * -1 >= this->maxHealth * 0.5) {
					this->canTakeAction = false;
					return "The unit was shot down before it could hit its target!";
				}
				else {
					int damageDealt = 0;
					int damageTemporary = 0;
					if (units[0][coordsy][coordsx].owningPlayer == opposingPlayer) {
						damageTemporary = Attack.stat1;
						if (units[0][coordsy][coordsx].isMarked) { damageTemporary = damageTemporary * 2; };
						if (units[0][coordsy][coordsx].isShielded) { damageTemporary = damageTemporary / 2; };
						if (units[0][coordsy][coordsx].isAir) { damageTemporary = damageTemporary / 2; };
						damageDealt += damageTemporary;
						units[0][coordsy][coordsx].health -= damageTemporary;
					}
					if (coordsy - 1 >= 0) {
						if (units[0][coordsy - 1][coordsx].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy - 1][coordsx].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy - 1][coordsx].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy - 1][coordsx].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy - 1][coordsx].health -= damageTemporary;
						}
					}
					if (coordsy - 1 >= 0 && coordsx + 1 <= 14) {
						if (units[0][coordsy - 1][coordsx + 1].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy - 1][coordsx + 1].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy - 1][coordsx + 1].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy - 1][coordsx + 1].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy - 1][coordsx + 1].health -= damageTemporary;
						}
					}
					if (coordsy + 1 <= 14) {
						if (units[0][coordsy + 1][coordsx].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy + 1][coordsx].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy + 1][coordsx].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy + 1][coordsx].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy + 1][coordsx].health -= damageTemporary;
						}
					}
					if (coordsy + 1 <= 14 && coordsx + 1 <= 14) {
						if (units[0][coordsy + 1][coordsx + 1].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy + 1][coordsx + 1].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy + 1][coordsx + 1].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy + 1][coordsx + 1].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy + 1][coordsx + 1].health -= damageTemporary;
						}
					}
					if (coordsx + 1 <= 14) {
						if (units[0][coordsy][coordsx + 1].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy][coordsx + 1].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy][coordsx + 1].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy][coordsx + 1].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy][coordsx + 1].health -= damageTemporary;
						}
					}
					if (coordsy + 1 <= 14 && coordsx - 1 >= 0) {
						if (units[0][coordsy + 1][coordsx - 1].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy + 1][coordsx - 1].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy + 1][coordsx - 1].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy + 1][coordsx - 1].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy + 1][coordsx - 1].health -= damageTemporary;
						}
					}
					if (coordsx - 1 >= 0) {
						if (units[0][coordsy][coordsx - 1].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy][coordsx - 1].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy][coordsx - 1].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy][coordsx - 1].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy][coordsx - 1].health -= damageTemporary;
						}
					}
					if (coordsy - 1 >= 0 && coordsx - 1 >= 0) {
						if (units[0][coordsy - 1][coordsx - 1].owningPlayer == opposingPlayer) {
							damageTemporary = Attack.stat2;
							if (units[0][coordsy - 1][coordsx - 1].isMarked) { damageTemporary = damageTemporary * 2; };
							if (units[0][coordsy - 1][coordsx - 1].isShielded) { damageTemporary = damageTemporary / 2; };
							if (units[0][coordsy - 1][coordsx - 1].isAir) { damageTemporary = damageTemporary / 2; };
							damageDealt += damageTemporary;
							units[0][coordsy - 1][coordsx - 1].health -= damageTemporary;
						}
					}
					if (damageDealt <= 0) {
						return "No units were hit!";
					}
					else {
						this->canTakeAction = false;
						return "Dealt " + std::to_string(damageDealt) + " damage to multiple units!";
					}
				}
			}
		} else {
			return "Target is out of range!";
		}
	}
	else if (Attack.attackID == "Air Attack") {
	bool canDoAttack = true;
	if (fowSettings == 0) {
		if (displayMap[coordsy][coordsx] == "#####") {
			canDoAttack = false;
		}
	}
	if (displayMap[coordsy][coordsx] == "|||||") {
		canDoAttack = false;
	}
	if (canDoAttack) {
		if (units[0][coordsy][coordsx].owningPlayer != opposingPlayer || units[0][coordsy][coordsx].isAir) {
			if (fowSettings == 1) {
				this->canTakeAction = false;
				return "The attack was carried out, but nothing was hit!";
			}
			else {
				return "Invalid target! Either that isn't the enemy or that unit is in the air!";
			}
		}
		else {
			std::vector<std::vector<int>> spotsToCheck = GetSpacesInRange(displayMap, 15);
			int damageTaken = 0;
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					if (units[0][i][j].antiAir > 0) {
						std::vector<std::vector<int>> inRangeAntiAir = units[0][i][j].GetSpacesInRadar(displayMap);
						bool canTarget = false;
						std::vector<int> targetSpot = { coordsy, coordsx };
						for (int k = 0; k < inRangeAntiAir.size(); k++) {
							if (inRangeAntiAir[k] == targetSpot) {
								canTarget = true;
								break;
							}
						}
						if (canTarget) {
							damageTaken += units[0][i][j].antiAir;
						}
					}
				}
			}
			this->health -= damageTaken;
			if (this->health * -1 >= this->maxHealth * 0.5) {
				this->canTakeAction = false;
				return "The unit was shot down before it could hit its target!";
			}
			else {
				int damage = Attack.stat1;
				if (units[0][coordsy][coordsx].isMarked) { damage = damage * 2; };
				if (units[0][coordsy][coordsx].isShielded) { damage = damage / 2; };
				units[0][coordsy][coordsx].health -= damage;
				this->canTakeAction = false;
				return "Dealt " + std::to_string(damage) + " to the target!";
			}
		}
	}
	else {
		return "Target is out of range!";
	}
	}
	else {
		return "ATTACK NOT RECOGNISED.";
	}
}

bool Unit::isSpaceInRange(int range, std::vector<std::vector<Unit>> units, std::string displayMap[15][15], int coordsx, int coordsy) {
	std::vector<std::vector<std::string>> c_displayMap;
	for (int i = 0; i < 15; i++) {
		std::vector<std::string> c_displayRow;
		for (int j = 0; j < 15; j++) {
			c_displayRow.push_back(displayMap[i][j]);
		}
		c_displayMap.push_back(c_displayRow);
	}
	std::vector<std::vector<int>> reachableSpots = GetSpacesInRange(c_displayMap, range);
	bool canTarget = false;
	std::vector<int> targetSpot = { coordsy, coordsx };
	for (size_t i = 0; i < reachableSpots.size(); i++) {
		if (reachableSpots[i] == targetSpot) {
			canTarget = true;
			break;
		}
	}
	return canTarget;
}