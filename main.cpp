#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>
#include<vector>
#include<algorithm>

#include "GameManager.h"
#include "Unit.h"
#include "UnitList.h"

GameManager gm;

// Unit build menu
struct BuildOp {
	std::string unitName;
	std::string description;
	int mass;
	int energy;
	int unitID;

	BuildOp(std::string unitName_c, std::string description_c, int mass_c, int energy_c, int unitID_c) :unitName(unitName_c), description(description_c), mass(mass_c), energy(energy_c), unitID(unitID_c) {}
};

// Unit build menu for ACUs and Engineers.
std::vector<BuildOp> mainBuild = {
	BuildOp("Energy Generator", "A power generator that uses plasma reactions to provide your army with a steady supply of energy, one of the most important resources.", 1, 2, 2),
	BuildOp("Mass Storage", "A solid container that can store unused mass for later, such as for emergencies or for a massive push.", 3, 3, 3),
	BuildOp("Energy Storage", "A structure container several capacitators to store excess energy for later.", 2, 5, 4),
	BuildOp("Point Defence Turret", "A static turret defence that can hold off incoming enemies and deal some damage to smaller armies. Becomes useless against experimentals other than being chump blockers.", 3, 5, 5),
	BuildOp("Anti-Air Turret", "A stationary defence turret that is best used in bases. It automatically attacks incoming bombers and can deal heavy damage to air units.", 2, 6, 6),
	BuildOp("Land Factory", "A factory that can create land units that can fight for you.", 4, 6, 7),
	BuildOp("Air Factory", "A factory that can create air units that can fight for you.", 6, 8, 8),
	BuildOp("Experimental Factory", "A massive factory that is capable of assembling experimental-class units.", 15, 20, 9)
};

// Unit build menu for UEF land factories.
std::vector<BuildOp> UEFLandBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Rockhead", "A defensive mobile unit that can hold choke points and can also act as the main force of an army.", 1, 3, 11),
	BuildOp("Mongoose", "An artillery unit that stands behind your other units to rain fire on enemy units. Comes equipped with anti-air as well.", 2, 3, 12),
	BuildOp("Pillar", "A heavy roadblock in the enemy's advance. High endurance, attacks that hit multiple units, it is the perfect defence.", 3, 6, 13),
	BuildOp("Parashield", "Provides your units with a shield to reduce damage. Not good alone, best used in defensive formations or for assaults.", 3, 3, 14)
};

std::vector<BuildOp> AeonLandBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Aurora", "A weak infantry unit that can make the front lines of an early offense or defence. Ineffective against bases or experimentals.", 1, 2, 22),
	BuildOp("Serenity", "A heavy yet slow movement that deals heavy damage to nearby units. Has the ability to teleport, allowing it to move faster.", 2, 4, 23),
	BuildOp("Evensong", "A weak supporting unit that can deal a bit of damage as well as heal nearby allies. Great for defence as well as short offensive strikes.", 3, 3, 24),
	BuildOp("Sprint", "A fast scouting unit that can mark enemy units for death, making all allies deal more damage to that enemy.", 1, 2, 25)
};

std::vector<BuildOp> CybranLandBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Loyalist", "A fast but weak infantry unit that makes the main portion of a cybran land force. Capable of launching hit-and-run attacks as well.", 1, 2, 33),
	BuildOp("Cobra", "A missle launcher that rains several weak missiles among a crowd of units. Useful in the back of an army where they can pester the enemy army.", 2, 5, 34),
	BuildOp("Adaptor", "A near-defenceless unit that provides a shield to nearby units, heals nearby units, and has automated anti-air.", 4, 7, 35),
	BuildOp("Revenant", "A fast unit that can detonate whenever needed, killing itself along with dealing immense damage to any nearby enemies.", 3, 6, 36)
};

std::vector<BuildOp> SeraphimLandBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Thaam", "A mediocre infantry unit that can teleport to move further in one turn. Equipped with a weak cannon for defence and offence.", 2, 5, 44),
	BuildOp("Usha-Ah", "A sniper unit that acts best in defensive positions or while aiming down corridors. Can mark enemies for death to increase its allies' effectiveness.", 3, 6, 45),
	BuildOp("Othuum", "A powerful tank unit that mainly acts as a defensive wall against incoming enemies. Can overdrive itself to temporarily boost its damage.", 5, 7, 46),
	BuildOp("Suthanus", "A missile launcher that is most effective behind its allies as it both fires a rain of missiles across enemies as well as providing shields for its allies.", 3, 4, 47)
};

std::vector<BuildOp> UEFAirBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Wasp", "A fighter plane capable of chasing down other air units and dealing with them swiftly and effectively.", 3, 5, 15),
	BuildOp("Eagle", "A bomber plane that flies over revealed targets to drop a payload of bombs across a wide area.", 2, 5, 16),
	BuildOp("Broadsword", "A flying gunship that provides effective area denial. Most effective in groups.", 4, 6, 17),
	BuildOp("Blackbird", "A feeble flying unit that is mainly used for scouting out the enemy base or to provide a short-lived distraction. Is completely unarmed.", 1, 3, 18)
};

std::vector<BuildOp> AeonAirBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Weedoboth", "A combination between a fighter plane and a bombing plane. Makes the backbone of the Aeon's air force.", 4, 6, 26),
	BuildOp("HeeHola", "A flying repair unit that can act as both a defensive blocker as well as a mobile repair station.", 5, 7, 27),
	BuildOp("Vulthoo", "A fast gunship that can provide quick support to a land raid. Mostly effective against unprepared land forces.", 3, 5, 28),
	BuildOp("Mercy", "A flying protector that provides all nearby units with a shield, reducing the amount of damage they take from the enemy units.", 4, 6, 29)
};

std::vector<BuildOp> CybranAirBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Gemini", "A combination between a fighter plane and a bombing plane. Fast, but weak against the other faction's units.", 3, 5, 37),
	BuildOp("Prowler", "A high-armoured interceptor unit that deals with air units and provides support to land units by marking enemies for death.", 6, 7, 38),
	BuildOp("Renegade", "A heavy gunship that can easily shread an unprepared army when used. Most effective in groups of four or five.", 4, 6, 39),
	BuildOp("Intellitron", "An incredibly fast but weak unit that has no attacks. Mainly used for reconnisance, distractions, or for scouting.", 2, 3, 40)
};

std::vector<BuildOp> SeraphimAirBuild = {
	BuildOp("Engineer", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", 2, 4, 10),
	BuildOp("Iaselem", "A slow but powerful interceptor that is capable of easily dealing with enemy air threats.", 4, 7, 48),
	BuildOp("Notha", "A plasma bomber that drops AOE bombs across areas, dealing high damage to multiple enemies. Most effective against bases.", 4, 5, 49),
	BuildOp("Sinnve", "A cross between a gunship and an interceptor. Can both handle itself against air units and can deal damage to ground units with directed weapons. Most effective when paired with land units.", 5, 7, 50),
	BuildOp("Vish", "A strong but slow flying factory that can produce other Seraphim air units to fight for you. Has no other weapons to protect itself with.", 5, 8, 51)
};

std::vector<BuildOp> UEFExperimentalBuild = {
	BuildOp("Fatboy", "A massive land unit who's bulk makes it a tough challenge to pass. It has effective weaponry at most ranges and heals nearby units using mounted factory modules. The best defence as well as the backbone of an offensive push.", 20, 35, 19),
	BuildOp("King Kriptor", "A gigantic titan-like unit with weapons capable of shredding any assault. Can prove difficult to deal with when put on the offensive. The UEF's most powerful weapon.", 30, 45, 20),
	BuildOp("Star King", "A gigantic flying unit that doubles as a mobile factory, capable of summoning air units wherever it is.", 20, 40, 21)
};

std::vector<BuildOp> AeonExperimentalBuild = {
	BuildOp("Urchinow", "A power and relatively cheap land experimental that can easily be rushed to provide an extra amount of power to a land attack.", 20, 25, 30),
	BuildOp("Universal Colossus", "A slow, powerful experimental that can wreck havoc on an army. Can easily rush an entire army or base alone, and is even more powerful when paired with other units or experimentals.", 40, 55, 31),
	BuildOp("CZAR", "A flying UFO-like unit that can easily tear any base or experimental to shread. It is relatively fragile however, so protect it with your other air units.", 30, 35, 32)
};

std::vector<BuildOp> CybranExperimentalBuild = {
	BuildOp("Megalith", "A weak experimental that can tear enemies to shreads when backed up by an army. It's relative cheap cost makes it easy to rush out early.", 15, 20, 41),
	BuildOp("Monkey Lord", "A spider-like experimental that can fire a massive laser that obliterates enemies and is most effective against other experimentals. It can also create other land units to aid it.", 35, 50, 42),
	BuildOp("Soul Ripper", "A massive flying gunship that can absolutely shread any base rapidly or perform targetted damage to a single strong unit. A terror of the skies, but easily countered with air units.", 25, 40, 43)
};

std::vector<BuildOp> SeraphimExperimentalBuild = {
	BuildOp("Iya", "A defensive land experimental that provides nearby allies with a shield and consistant healing. It also can provide area denial through pulse wave attacks.", 25, 30, 52),
	BuildOp("Ythotha", "A powerful land experimental with a wide variety of land-based attacks for both dealing with groups of units close-by or for dealing with far away units. Drops a massive field of energy when killed, severly harming nearby enemies.", 40, 50, 53),
	BuildOp("Ahwassa", "An experimental bomber plane that is loaded with charged plasma bombs that can easily wipe out any group of enemy units in an instant. Most effective against bases.", 25, 60, 54)
};



// Colour Management
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
WORD ResetKey;

// Game Statistics
std::string map[15][15];
std::vector<std::vector<Unit>> fieldUnits;
int p1Faction = 0;
int p2Faction = 0;
int fowSettings = 0;

std::vector<std::vector<std::string>> getVectorMap(std::string displayMap[15][15]) {
	std::vector<std::vector<std::string>> c_displayMap;
	for (int i = 0; i < 15; i++) {
		std::vector<std::string> c_displayRow;
		for (int j = 0; j < 15; j++) {
			c_displayRow.push_back(displayMap[i][j]);
		}
		c_displayMap.push_back(c_displayRow);
	}

	return c_displayMap;
}

int getFactionColour(int factionID) {
	switch (factionID) {
	case 0:
		return 9;
		break;
	case 1:
		return 2;
		break;
	case 2:
		return 4;
		break;
	case 3:
		return 14;
		break;
	}
}

void game() {
	int p1Mass = 10;
	int p1Energy = 10;
	int p2Mass = 10;
	int p2Energy = 10;
	int p1MassIncome = 1;
	int p1EnergyIncome = 2;
	int p2MassIncome = 1;
	int p2EnergyIncome = 2;
	int p1MaxMass = 10;
	int p1MaxEnergy = 20;
	int p2MaxMass = 10;
	int p2MaxEnergy = 20;

	bool isDone2 = false;
	bool isDone4 = false;
	int op1 = 0;
	int op2 = 0;
	int wordCount = 0;

	bool isDone3 = false;
	bool doRedraw2 = true;
	bool redoUnitLogic = true;

	int ogCursorCoordsX = 0;
	int ogCursorCoordsY = 0;

	bool isDone = false;
	bool doRedraw = true;
	int playerTurn = 1;
	int cursorCoords[2] = { 0, 0 };
	std::vector<std::vector<int>> massSpots;
	std::vector<std::vector<int>> noTouchSpots;
	std::string displayMap[15][15];

	std::vector<BuildOp> buildList;

	// Fog of war + Setting up display map
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			displayMap[i][j] = map[i][j];
			if (displayMap[i][j] == "|SP1|") {
				fieldUnits[i][j] = retrieveUnit(0);
				fieldUnits[i][j].owningPlayer = 1;
				fieldUnits[i][j].xpos = j;
				fieldUnits[i][j].ypos = i;
				fieldUnits[i][j].factionID = p1Faction;
				displayMap[i][j] = "1-ACU";
			}
			else if (displayMap[i][j] == "|SP2|") {
				fieldUnits[i][j] = retrieveUnit(0);
				fieldUnits[i][j].owningPlayer = 2;
				fieldUnits[i][j].xpos = j;
				fieldUnits[i][j].ypos = i;
				fieldUnits[i][j].factionID = p2Faction;
				displayMap[i][j] = "2-ACU";
			}
			else if (displayMap[i][j].find("-MAS") != std::string::npos) {
				massSpots.push_back({i, j});
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (fieldUnits[i][j].owningPlayer == playerTurn) {
				std::vector<std::vector<std::string>> c_displayMap;
				for (int k = 0; k < 15; k++) {
					std::vector<std::string> c_tempDisplayRow;
					for (int l = 0; l < 15; l++) {
						c_tempDisplayRow.push_back(displayMap[k][l]);
					}
					c_displayMap.push_back(c_tempDisplayRow);
				}
				std::vector<std::vector<int>> spacesAcquired = fieldUnits[i][j].GetSpacesInRadar(c_displayMap);
				for (int k = 0; k < spacesAcquired.size(); k++) {
					noTouchSpots.push_back(spacesAcquired[k]);
				}
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			std::vector<int> key = { i, j };
			if (std::find(noTouchSpots.begin(), noTouchSpots.end(), key) == noTouchSpots.end() && fowSettings < 2 && fieldUnits[i][j].owningPlayer != playerTurn && displayMap[i][j] != "|||||") {
				if (std::find(massSpots.begin(), massSpots.end(), key) == massSpots.end()) {
					displayMap[i][j] = "#####";
				}
				else {
					displayMap[i][j] = "?-MAS";
				}
			}
		}
	}
	while (!isDone) {
		if (doRedraw) {
			if (redoUnitLogic) {
				noTouchSpots.clear();
				massSpots.clear();
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						displayMap[i][j] = map[i][j];
						if (fieldUnits[i][j].owningPlayer > 0) {
							displayMap[i][j] = std::to_string(fieldUnits[i][j].owningPlayer) + "-" + fieldUnits[i][j].displayName;
						}
						else {
							if (displayMap[i][j] == "|SP1|" || displayMap[i][j] == "|SP2|") {
								displayMap[i][j] = "     ";
							}
						}
						if (displayMap[i][j].find("-MAS") != std::string::npos) {
							massSpots.push_back({ i, j });
						}
					}
				}
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						if (fieldUnits[i][j].owningPlayer == playerTurn) {
							std::vector<std::vector<std::string>> c_displayMap;
							for (int k = 0; k < 15; k++) {
								std::vector<std::string> c_tempDisplayRow;
								for (int l = 0; l < 15; l++) {
									c_tempDisplayRow.push_back(displayMap[k][l]);
								}
								c_displayMap.push_back(c_tempDisplayRow);
							}
							std::vector<std::vector<int>> spacesAcquired = fieldUnits[i][j].GetSpacesInRadar(c_displayMap);
							for (int k = 0; k < spacesAcquired.size(); k++) {
								noTouchSpots.push_back(spacesAcquired[k]);
							}
						}
					}
				}
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						std::vector<int> key = { i, j };
						if (std::find(noTouchSpots.begin(), noTouchSpots.end(), key) == noTouchSpots.end() && fowSettings < 2 && fieldUnits[i][j].owningPlayer != playerTurn && displayMap[i][j] != "|||||") {
							if (std::find(massSpots.begin(), massSpots.end(), key) == massSpots.end()) {
								displayMap[i][j] = "#####";
							}
							else {
								displayMap[i][j] = "?-MAS";
							}
						}
					}
				}
				redoUnitLogic = false;
			}

			system("cls");
			if (playerTurn == 1) {
				SetConsoleTextAttribute(h, getFactionColour(p1Faction));
			}
			else {
				SetConsoleTextAttribute(h, getFactionColour(p2Faction));
			}
			std::cout << "-- Player " << playerTurn << "'s turn --" << std::endl;
			std::cout << "(Use W, A, S, and D to move the cursor. Use X to select a space and P to end your turn.)" << std::endl;
			SetConsoleTextAttribute(h, ResetKey);
			for (int i = 0; i < 15; i++) {
				std::cout << " ";
				for (int j = 0; j < 15; j++) {
					if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
						if (fieldUnits[i][j].owningPlayer == 1) {
							SetConsoleTextAttribute(h, getFactionColour(p1Faction));
						}
						else {
							SetConsoleTextAttribute(h, getFactionColour(p2Faction));
						}
					}
					std::cout << displayMap[i][j];
					SetConsoleTextAttribute(h, ResetKey);
					if (cursorCoords[0] == j && cursorCoords[1] == i) {
						std::cout << "\b\b\b\b\b\b>";
						if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
							if (fieldUnits[i][j].owningPlayer == 1) {
								SetConsoleTextAttribute(h, getFactionColour(p1Faction));
							}
							else {
								SetConsoleTextAttribute(h, getFactionColour(p2Faction));
							}
						}
						std::cout << displayMap[i][j];
						SetConsoleTextAttribute(h, ResetKey);
						std::cout << "<";
					}
					else {
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;

			if (playerTurn == 1) {
				SetConsoleTextAttribute(h, getFactionColour(p1Faction));
			}
			else {
				SetConsoleTextAttribute(h, getFactionColour(p2Faction));
			}
			if (playerTurn == 1) {
				std::cout << "Mass: " << p1Mass << "/" << p1MaxMass << " (+" << p1MassIncome << ")" << std::endl;
				std::cout << "Energy: " << p1Energy << "/" << p1MaxEnergy << " (+" << p1EnergyIncome << ")" << std::endl;
			}
			else {
				std::cout << "Mass: " << p2Mass << "/" << p2MaxMass << " (+" << p2MassIncome << ")" << std::endl;
				std::cout << "Energy: " << p2Energy << "/" << p2MaxEnergy << " (+" << p2EnergyIncome << ")" << std::endl;
			}
			
			doRedraw = false;
		}

		char c = _getch();
		switch (c) {
		case 'a':
			if (cursorCoords[0] > 0) {
				cursorCoords[0]--;
				doRedraw = true;
			}
			break;
		case 'd':
			if (cursorCoords[0] < 14) {
				cursorCoords[0]++;
				doRedraw = true;
			}
			break;
		case 'w':
			if (cursorCoords[1] > 0) {
				cursorCoords[1]--;
				doRedraw = true;
			}
			break;
		case 's':
			if (cursorCoords[1] < 14) {
				cursorCoords[1]++;
				doRedraw = true;
			}
			break;
		case 'x':
			system("cls");
			doRedraw = true;
			isDone2 = false;
			if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer > 0 && displayMap[cursorCoords[1]][cursorCoords[0]] != "#####") {
				while (!isDone2) {
					if (doRedraw) {
						if (redoUnitLogic) {
							noTouchSpots.clear();
							massSpots.clear();
							for (int i = 0; i < 15; i++) {
								for (int j = 0; j < 15; j++) {
									displayMap[i][j] = map[i][j];
									if (fieldUnits[i][j].owningPlayer > 0) {
										displayMap[i][j] = std::to_string(fieldUnits[i][j].owningPlayer) + "-" + fieldUnits[i][j].displayName;
									}
									else {
										if (displayMap[i][j] == "|SP1|" || displayMap[i][j] == "|SP2|") {
											displayMap[i][j] = "     ";
										}
									}
									if (displayMap[i][j].find("-MAS") != std::string::npos) {
										massSpots.push_back({ i, j });
									}
								}
							}
							for (int i = 0; i < 15; i++) {
								for (int j = 0; j < 15; j++) {
									if (fieldUnits[i][j].owningPlayer == playerTurn) {
										std::vector<std::vector<std::string>> c_displayMap;
										for (int k = 0; k < 15; k++) {
											std::vector<std::string> c_tempDisplayRow;
											for (int l = 0; l < 15; l++) {
												c_tempDisplayRow.push_back(displayMap[k][l]);
											}
											c_displayMap.push_back(c_tempDisplayRow);
										}
										std::vector<std::vector<int>> spacesAcquired = fieldUnits[i][j].GetSpacesInRadar(c_displayMap);
										for (int k = 0; k < spacesAcquired.size(); k++) {
											noTouchSpots.push_back(spacesAcquired[k]);
										}
									}
								}
							}
							for (int i = 0; i < 15; i++) {
								for (int j = 0; j < 15; j++) {
									std::vector<int> key = { i, j };
									if (std::find(noTouchSpots.begin(), noTouchSpots.end(), key) == noTouchSpots.end() && fowSettings < 2 && fieldUnits[i][j].owningPlayer != playerTurn && displayMap[i][j] != "|||||") {
										if (std::find(massSpots.begin(), massSpots.end(), key) == massSpots.end()) {
											displayMap[i][j] = "#####";
										}
										else {
											displayMap[i][j] = "?-MAS";
										}
									}
								}
							}
							redoUnitLogic = false;
						}
						system("cls");
						if (playerTurn == 1) {
							SetConsoleTextAttribute(h, getFactionColour(p1Faction));
						}
						else {
							SetConsoleTextAttribute(h, getFactionColour(p2Faction));
						}
						std::cout << "-- Player " << playerTurn << "'s turn --" << std::endl;
						std::cout << "(Use W and S to change options, use X to select an option. Z to go back. )" << std::endl;
						SetConsoleTextAttribute(h, ResetKey);
						for (int i = 0; i < 15; i++) {
							std::cout << " ";
							for (int j = 0; j < 15; j++) {
								if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
									if (fieldUnits[i][j].owningPlayer == 1 && displayMap[i][j] != "#####") {
										SetConsoleTextAttribute(h, getFactionColour(p1Faction));
									}
									else {
										SetConsoleTextAttribute(h, getFactionColour(p2Faction));
									}
								}
								std::cout << displayMap[i][j];
								SetConsoleTextAttribute(h, ResetKey);
								if (cursorCoords[0] == j && cursorCoords[1] == i) {
									std::cout << "\b\b\b\b\b\b>";
									if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
										if (fieldUnits[i][j].owningPlayer == 1) {
											SetConsoleTextAttribute(h, getFactionColour(p1Faction));
										}
										else {
											SetConsoleTextAttribute(h, getFactionColour(p2Faction));
										}
									}
									std::cout << displayMap[i][j];
									SetConsoleTextAttribute(h, ResetKey);
									std::cout << "<";
								}
								else {
									std::cout << " ";
								}
							}
							std::cout << std::endl;
						}
						std::cout << std::endl;

						if (playerTurn == 1) {
							SetConsoleTextAttribute(h, getFactionColour(p1Faction));
						}
						else {
							SetConsoleTextAttribute(h, getFactionColour(p2Faction));
						}
						if (playerTurn == 1) {
							std::cout << "Mass: " << p1Mass << "/" << p1MaxMass << " (+" << p1MassIncome << ")" << std::endl;
							std::cout << "Energy: " << p1Energy << "/" << p1MaxEnergy << " (+" << p1EnergyIncome << ")" << std::endl;
						}
						else {
							std::cout << "Mass: " << p2Mass << "/" << p2MaxMass << " (+" << p2MassIncome << ")" << std::endl;
							std::cout << "Energy: " << p2Energy << "/" << p2MaxEnergy << " (+" << p2EnergyIncome << ")" << std::endl;
						}
						SetConsoleTextAttribute(h, ResetKey);

						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 1) {
							SetConsoleTextAttribute(h, getFactionColour(p1Faction));
						}
						else {
							SetConsoleTextAttribute(h, getFactionColour(p2Faction));
						}
						std::cout << "\n" << fieldUnits[cursorCoords[1]][cursorCoords[0]].name << ":" << std::endl;
						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == playerTurn) {
							std::cout << "Move";
							if (op1 == 0) std::cout << " <--\n";
							else std::cout << std::endl;
							std::cout << "Action";
							if (op1 == 1) std::cout << " <--\n";
							else std::cout << std::endl;
							std::cout << "Inspect";
							if (op1 == 2) std::cout << " <--\n";
							else std::cout << std::endl;
						}
						else {
							std::cout << "Inspect <--\n";
						}

						doRedraw = false;
					}

					char c = _getch();
					switch (c) {
					case 'w':
						if (op1 > 0) {
							op1--;
							doRedraw = true;
						}
						break;
					case 's':
						if (op1 < 2) {
							op1++;
							doRedraw = true;
						}
						break;
					case 'x':
						system("cls");
						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == playerTurn) {
							switch (op1) {
							case 0: // Move
								redoUnitLogic = true;
								isDone3 = false;
								doRedraw2 = true;
								while (!isDone3) {
									if (doRedraw2) {
										noTouchSpots.clear();
										massSpots.clear();
										for (int i = 0; i < 15; i++) {
											for (int j = 0; j < 15; j++) {
												displayMap[i][j] = map[i][j];
												if (fieldUnits[i][j].owningPlayer > 0) {
													displayMap[i][j] = std::to_string(fieldUnits[i][j].owningPlayer) + "-" + fieldUnits[i][j].displayName;
												}
												else {
													if (displayMap[i][j] == "|SP1|" || displayMap[i][j] == "|SP2|") {
														displayMap[i][j] = "     ";
													}
												}
												if (displayMap[i][j].find("-MAS") != std::string::npos) {
													massSpots.push_back({ i, j });
												}
											}
										}
										for (int i = 0; i < 15; i++) {
											for (int j = 0; j < 15; j++) {
												if (fieldUnits[i][j].owningPlayer == playerTurn) {
													std::vector<std::vector<std::string>> c_displayMap;
													for (int k = 0; k < 15; k++) {
														std::vector<std::string> c_tempDisplayRow;
														for (int l = 0; l < 15; l++) {
															c_tempDisplayRow.push_back(displayMap[k][l]);
														}
														c_displayMap.push_back(c_tempDisplayRow);
													}
													std::vector<std::vector<int>> spacesAcquired = fieldUnits[i][j].GetSpacesInRadar(c_displayMap);
													for (int k = 0; k < spacesAcquired.size(); k++) {
														noTouchSpots.push_back(spacesAcquired[k]);
													}
												}
											}
										}
										for (int i = 0; i < 15; i++) {
											for (int j = 0; j < 15; j++) {
												std::vector<int> key = { i, j };
												if (std::find(noTouchSpots.begin(), noTouchSpots.end(), key) == noTouchSpots.end() && fowSettings < 2 && fieldUnits[i][j].owningPlayer != playerTurn && displayMap[i][j] != "|||||") {
													if (std::find(massSpots.begin(), massSpots.end(), key) == massSpots.end()) {
														displayMap[i][j] = "#####";
													}
													else {
														displayMap[i][j] = "?-MAS";
													}
												}
											}
										}

										system("cls");
										if (playerTurn == 1) {
											SetConsoleTextAttribute(h, getFactionColour(p1Faction));
										}
										else {
											SetConsoleTextAttribute(h, getFactionColour(p2Faction));
										}
										std::cout << "-- Player " << playerTurn << "'s turn --" << std::endl;
										std::cout << "Unit moves left: " << fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft << std::endl;
										std::cout << "(Use W, A, S, and D to move the unit, X to finish)" << std::endl;
										SetConsoleTextAttribute(h, ResetKey);
										for (int i = 0; i < 15; i++) {
											std::cout << " ";
											for (int j = 0; j < 15; j++) {
												if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
													if (fieldUnits[i][j].owningPlayer == 1) {
														SetConsoleTextAttribute(h, getFactionColour(p1Faction));
													}
													else {
														SetConsoleTextAttribute(h, getFactionColour(p2Faction));
													}
												}
												std::cout << displayMap[i][j];
												SetConsoleTextAttribute(h, ResetKey);
												if (cursorCoords[0] == j && cursorCoords[1] == i) {
													std::cout << "\b\b\b\b\b\b>";
													if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
														if (fieldUnits[i][j].owningPlayer == 1) {
															SetConsoleTextAttribute(h, getFactionColour(p1Faction));
														}
														else {
															SetConsoleTextAttribute(h, getFactionColour(p2Faction));
														}
													}
													std::cout << displayMap[i][j];
													SetConsoleTextAttribute(h, ResetKey);
													std::cout << "<";
												}
												else {
													std::cout << " ";
												}
											}
											std::cout << std::endl;
										}
										std::cout << std::endl;

										if (playerTurn == 1) {
											SetConsoleTextAttribute(h, getFactionColour(p1Faction));
										}
										else {
											SetConsoleTextAttribute(h, getFactionColour(p2Faction));
										}
										if (playerTurn == 1) {
											std::cout << "Mass: " << p1Mass << "/" << p1MaxMass << " (+" << p1MassIncome << ")" << std::endl;
											std::cout << "Energy: " << p1Energy << "/" << p1MaxEnergy << " (+" << p1EnergyIncome << ")" << std::endl;
										}
										else {
											std::cout << "Mass: " << p2Mass << "/" << p2MaxMass << " (+" << p2MassIncome << ")" << std::endl;
											std::cout << "Energy: " << p2Energy << "/" << p2MaxEnergy << " (+" << p2EnergyIncome << ")" << std::endl;
										}

										doRedraw2 = false;
									}

									char c = _getch();
									switch (c) {
									case 'a':
										if (displayMap[cursorCoords[1]][cursorCoords[0] - 1] != "|||||" && fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft > 0 && fieldUnits[cursorCoords[1]][cursorCoords[0] - 1].owningPlayer == 0 && displayMap[cursorCoords[1]][cursorCoords[0] - 1] != "0-MAS") {
											Unit movedUnit = fieldUnits[cursorCoords[1]][cursorCoords[0]];
											cursorCoords[0]--;
											fieldUnits[cursorCoords[1]][cursorCoords[0]] = movedUnit;
											fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos--;
											fieldUnits[cursorCoords[1]][cursorCoords[0] + 1] = Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, cursorCoords[0], cursorCoords[1] - 1, 0, 0);
											fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft--;
											doRedraw2 = true;
										}
										break;
									case 'd':
										if (displayMap[cursorCoords[1]][cursorCoords[0] + 1] != "|||||" && fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft > 0 && fieldUnits[cursorCoords[1]][cursorCoords[0] + 1].owningPlayer == 0 && displayMap[cursorCoords[1]][cursorCoords[0] + 1] != "0-MAS") {
											Unit movedUnit = fieldUnits[cursorCoords[1]][cursorCoords[0]];
											cursorCoords[0]++;
											fieldUnits[cursorCoords[1]][cursorCoords[0]] = movedUnit;
											fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos++;
											fieldUnits[cursorCoords[1]][cursorCoords[0] - 1] = Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, cursorCoords[0], cursorCoords[1] - 1, 0, 0);
											fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft--;
											doRedraw2 = true;
										}
										break;
									case 'w':
										if (displayMap[cursorCoords[1] - 1][cursorCoords[0]] != "|||||" && fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft > 0 && fieldUnits[cursorCoords[1] - 1][cursorCoords[0]].owningPlayer == 0 && displayMap[cursorCoords[1] - 1][cursorCoords[0]] != "0-MAS") {
											Unit movedUnit = fieldUnits[cursorCoords[1]][cursorCoords[0]];
											cursorCoords[1]--;
											fieldUnits[cursorCoords[1]][cursorCoords[0]] = movedUnit;
											fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos--;
											fieldUnits[cursorCoords[1] + 1][cursorCoords[0]] = Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, cursorCoords[0], cursorCoords[1] - 1, 0, 0);
											fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft--;
											doRedraw2 = true;
										}
										break;
									case 's':
										if (displayMap[cursorCoords[1] + 1][cursorCoords[0]] != "|||||" && fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft > 0 && fieldUnits[cursorCoords[1] + 1][cursorCoords[0]].owningPlayer == 0 && displayMap[cursorCoords[1] + 1][cursorCoords[0]] != "0-MAS") {
											Unit movedUnit = fieldUnits[cursorCoords[1]][cursorCoords[0]];
											cursorCoords[1]++;
											fieldUnits[cursorCoords[1]][cursorCoords[0]] = movedUnit;
											fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos++;
											fieldUnits[cursorCoords[1] - 1][cursorCoords[0]] = Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, cursorCoords[0], cursorCoords[1] - 1, 0, 0);
											fieldUnits[cursorCoords[1]][cursorCoords[0]].movesLeft--;
											doRedraw2 = true;
										}
										break;
									case 'x':
										system("cls");
										isDone3 = true;
										break;
									}
								}

								doRedraw = true;
								break;
							case 1: // Taking actions
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].canTakeAction && fieldUnits[cursorCoords[1]][cursorCoords[0]].actions.size() > 0) {
									isDone3 = false;
									doRedraw2 = true;
									op2 = 0;
									redoUnitLogic = true;
									while (!isDone3) {
										if (doRedraw2) {
											system("cls");
											if (playerTurn == 1) {
												SetConsoleTextAttribute(h, getFactionColour(p1Faction));
											}
											else {
												SetConsoleTextAttribute(h, getFactionColour(p2Faction));
											}
											std::cout << "-- Player " << playerTurn << "'s turn --" << std::endl;
											std::cout << "(Use W and S to select an option, X to use selected action, Z to finish)" << std::endl;
											SetConsoleTextAttribute(h, ResetKey);
											for (int i = 0; i < 15; i++) {
												std::cout << " ";
												for (int j = 0; j < 15; j++) {
													if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
														if (fieldUnits[i][j].owningPlayer == 1) {
															SetConsoleTextAttribute(h, getFactionColour(p1Faction));
														}
														else {
															SetConsoleTextAttribute(h, getFactionColour(p2Faction));
														}
													}
													std::cout << displayMap[i][j];
													SetConsoleTextAttribute(h, ResetKey);
													if (cursorCoords[0] == j && cursorCoords[1] == i) {
														std::cout << "\b\b\b\b\b\b>";
														if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
															if (fieldUnits[i][j].owningPlayer == 1) {
																SetConsoleTextAttribute(h, getFactionColour(p1Faction));
															}
															else {
																SetConsoleTextAttribute(h, getFactionColour(p2Faction));
															}
														}
														std::cout << displayMap[i][j];
														SetConsoleTextAttribute(h, ResetKey);
														std::cout << "<";
													}
													else {
														std::cout << " ";
													}
												}
												std::cout << std::endl;
											}
											std::cout << std::endl;

											if (playerTurn == 1) {
												SetConsoleTextAttribute(h, getFactionColour(p1Faction));
											}
											else {
												SetConsoleTextAttribute(h, getFactionColour(p2Faction));
											}
											if (playerTurn == 1) {
												std::cout << "Mass: " << p1Mass << "/" << p1MaxMass << " (+" << p1MassIncome << ")" << std::endl;
												std::cout << "Energy: " << p1Energy << "/" << p1MaxEnergy << " (+" << p1EnergyIncome << ")" << std::endl;
											}
											else {
												std::cout << "Mass: " << p2Mass << "/" << p2MaxMass << " (+" << p2MassIncome << ")" << std::endl;
												std::cout << "Energy: " << p2Energy << "/" << p2MaxEnergy << " (+" << p2EnergyIncome << ")" << std::endl;
											}

											std::cout << "\nSelect an action:\n";
											for (int i = 0; i < fieldUnits[cursorCoords[1]][cursorCoords[0]].actions.size(); i++) {
												std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[i].name << " (" << fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[i].attackID << ")";
												if (op2 == i) { std::cout << " <--\n"; }
												else { std::cout << "\n"; }
											}

											doRedraw2 = false;
										}

										char c = _getch();
										switch (c) {
										case 'w':
											if (op2 > 0) {
												op2--;
												doRedraw2 = true;
											}
											break;
										case 's':
											if (op2 < fieldUnits[cursorCoords[1]][cursorCoords[0]].actions.size() - 1) {
												op2++;
												doRedraw2 = true;
											}
											break;
										case 'x':
											system("cls");
											// Targetted attack:
											if (!(fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[op2].attackID == "Overdrive" || fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[op2].attackID == "Detonation" || fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[op2].attackID == "Boost" || fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[op2].attackID == "Surround Attack")) {
												ogCursorCoordsX = cursorCoords[0];
												ogCursorCoordsY = cursorCoords[1];
												isDone4 = false;
												doRedraw2 = true;
												while (isDone4 == false) {
													if (doRedraw2) {
														noTouchSpots.clear();
														massSpots.clear();
														for (int i = 0; i < 15; i++) {
															for (int j = 0; j < 15; j++) {
																displayMap[i][j] = map[i][j];
																if (fieldUnits[i][j].owningPlayer > 0) {
																	displayMap[i][j] = std::to_string(fieldUnits[i][j].owningPlayer) + "-" + fieldUnits[i][j].displayName;
																}
																else {
																	if (displayMap[i][j] == "|SP1|" || displayMap[i][j] == "|SP2|") {
																		displayMap[i][j] = "     ";
																	}
																}
																if (displayMap[i][j].find("-MAS") != std::string::npos) {
																	massSpots.push_back({ i, j });
																}
															}
														}
														for (int i = 0; i < 15; i++) {
															for (int j = 0; j < 15; j++) {
																if (fieldUnits[i][j].owningPlayer == playerTurn) {
																	std::vector<std::vector<std::string>> c_displayMap;
																	for (int k = 0; k < 15; k++) {
																		std::vector<std::string> c_tempDisplayRow;
																		for (int l = 0; l < 15; l++) {
																			c_tempDisplayRow.push_back(displayMap[k][l]);
																		}
																		c_displayMap.push_back(c_tempDisplayRow);
																	}
																	std::vector<std::vector<int>> spacesAcquired = fieldUnits[i][j].GetSpacesInRadar(c_displayMap);
																	for (int k = 0; k < spacesAcquired.size(); k++) {
																		noTouchSpots.push_back(spacesAcquired[k]);
																	}
																}
															}
														}
														for (int i = 0; i < 15; i++) {
															for (int j = 0; j < 15; j++) {
																std::vector<int> key = { i, j };
																if (std::find(noTouchSpots.begin(), noTouchSpots.end(), key) == noTouchSpots.end() && fowSettings < 2 && fieldUnits[i][j].owningPlayer != playerTurn && displayMap[i][j] != "|||||") {
																	if (std::find(massSpots.begin(), massSpots.end(), key) == massSpots.end()) {
																		displayMap[i][j] = "#####";
																	}
																	else {
																		displayMap[i][j] = "?-MAS";
																	}
																}
															}
														}

														system("cls");
														if (playerTurn == 1) {
															SetConsoleTextAttribute(h, getFactionColour(p1Faction));
														}
														else {
															SetConsoleTextAttribute(h, getFactionColour(p2Faction));
														}
														std::cout << "-- Player " << playerTurn << "'s turn --" << std::endl;
														std::cout << "(Use W, A, S, and D to select the unit's target, X to launch attack)" << std::endl;
														SetConsoleTextAttribute(h, ResetKey);
														for (int i = 0; i < 15; i++) {
															std::cout << " ";
															for (int j = 0; j < 15; j++) {
																if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
																	if (fieldUnits[i][j].owningPlayer == 1) {
																		SetConsoleTextAttribute(h, getFactionColour(p1Faction));
																	}
																	else {
																		SetConsoleTextAttribute(h, getFactionColour(p2Faction));
																	}
																}
																std::cout << displayMap[i][j];
																SetConsoleTextAttribute(h, ResetKey);
																if (cursorCoords[0] == j && cursorCoords[1] == i) {
																	std::cout << "\b\b\b\b\b\b>";
																	if (fieldUnits[i][j].owningPlayer > 0 && displayMap[i][j] != "#####" && displayMap[i][j] != "?-MAS") {
																		if (fieldUnits[i][j].owningPlayer == 1) {
																			SetConsoleTextAttribute(h, getFactionColour(p1Faction));
																		}
																		else {
																			SetConsoleTextAttribute(h, getFactionColour(p2Faction));
																		}
																	}
																	std::cout << displayMap[i][j];
																	SetConsoleTextAttribute(h, ResetKey);
																	std::cout << "<";
																}
																else {
																	std::cout << " ";
																}
															}
															std::cout << std::endl;
														}
														std::cout << std::endl;

														if (playerTurn == 1) {
															SetConsoleTextAttribute(h, getFactionColour(p1Faction));
														}
														else {
															SetConsoleTextAttribute(h, getFactionColour(p2Faction));
														}
														if (playerTurn == 1) {
															std::cout << "Mass: " << p1Mass << "/" << p1MaxMass << " (+" << p1MassIncome << ")" << std::endl;
															std::cout << "Energy: " << p1Energy << "/" << p1MaxEnergy << " (+" << p1EnergyIncome << ")" << std::endl;
														}
														else {
															std::cout << "Mass: " << p2Mass << "/" << p2MaxMass << " (+" << p2MassIncome << ")" << std::endl;
															std::cout << "Energy: " << p2Energy << "/" << p2MaxEnergy << " (+" << p2EnergyIncome << ")" << std::endl;
														}

														doRedraw2 = false;
													}

													char c = _getch();
													switch (c) {
													case 'a':
														if (cursorCoords[0] - 1 > 0) {
															cursorCoords[0]--;
															doRedraw2 = true;
														}
														break;
													case 'd':
														if (cursorCoords[0] + 1 < 14) {
															cursorCoords[0]++;
															doRedraw2 = true;
														}
														break;
													case 'w':
														if (cursorCoords[1] - 1 > 0) {
															cursorCoords[1]--;
															doRedraw2 = true;
														}
														break;
													case 's':
														if (cursorCoords[1] + 1 < 14) {
															cursorCoords[1]++;
															doRedraw2 = true;
														}
														break;
													case 'x':
														system("cls");
														// Build Functionallity
														if (fieldUnits[ogCursorCoordsY][ogCursorCoordsX].actions[op2].attackID == "Build") {
															if (fieldUnits[ogCursorCoordsY][ogCursorCoordsX].isSpaceInRange(1, fieldUnits, displayMap, cursorCoords[0], cursorCoords[1]) && fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 0) {
																if (fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "ACU" || fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "ENG") {
																	if (displayMap[cursorCoords[1]][cursorCoords[0]] == "0-MAS" && fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 0) {
																		if (playerTurn == 1) {
																			if (p1Mass >= 1 && p1Energy >= 2) {
																				p1Mass -= 1;
																				p1Energy -= 2;
																				p1MassIncome += 1;
																				fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(1);
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p1Faction;
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 1;
																				std::cout << "Unit successfully built!" << std::endl;
																				redoUnitLogic = true;
																				doRedraw2 = true;
																				doRedraw = true;
																			}
																			else {
																				std::cout << "You don't have enough resources [1 mass, 2 energy]!" << std::endl;
																			}
																		}
																		else {
																			if (p2Mass >= 1 && p2Energy >= 2) {
																				p2Mass -= 1;
																				p2Energy -= 2;
																				p2MassIncome += 1;
																				fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(1);
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p2Faction;
																				fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 2;
																				std::cout << "Unit successfully built!" << std::endl;
																				redoUnitLogic = true;
																				doRedraw2 = true;
																				doRedraw = true;
																			}
																			else {
																				std::cout << "You don't have enough resources [1 mass, 2 energy]!" << std::endl;
																			}
																		}
																	}
																	else {
																		isDone4 = false;
																		doRedraw2 = true;
																		op2 = 0;
																		while (!isDone4) {
																			if (doRedraw2) {
																				system("cls");
																				std::cout << "Select a unit to build (W and S to navigate options, X to build that unit, Z to cancel):" << std::endl;
																				for (int i = 0; i < mainBuild.size(); i++) {
																					std::cout << mainBuild[i].unitName;
																					if (i == op2) {
																						std::cout << " <--";
																					}
																					std::cout << std::endl;
																				}
																				std::cout << std::endl;
																				wordCount = 0;
																				for (int i = 0; i < size(mainBuild[op2].description); i++) {
																					wordCount++;
																					std::cout << mainBuild[op2].description[i];
																					if (wordCount > 90 && mainBuild[op2].description[i] == ' ') {
																						std::cout << std::endl;
																						wordCount = 0;
																					}
																				}
																				std::cout << "\n[Mass: " << mainBuild[op2].mass << ", Energy: " << mainBuild[op2].energy << "]" << std::endl;
																				doRedraw2 = false;
																			}
																			char c = _getch();
																			switch (c) {
																			case 'w':
																				if (op2 > 0) {
																					op2--;
																				}
																				doRedraw2 = true;
																				break;
																			case 's':
																				if (op2 < mainBuild.size()-1) {
																					op2++;
																				}
																				doRedraw2 = true;
																				break;
																			case 'x':
																				system("cls");
																				if (playerTurn == 1) {
																					if (p1Mass >= mainBuild[op2].mass && p1Energy >= mainBuild[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p1Mass -= mainBuild[op2].mass;
																						p1Energy -= mainBuild[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(mainBuild[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 1;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p1Faction;
																						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "GEN") {
																							p1EnergyIncome += 2;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "MSC") {
																							p1MaxMass += 3;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "ENC") {
																							p1MaxEnergy += 5;
																						}
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																						system("pause");
																					}
																				}
																				else {
																					if (p2Mass >= mainBuild[op2].mass && p2Energy >= mainBuild[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p2Mass -= mainBuild[op2].mass;
																						p2Energy -= mainBuild[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(mainBuild[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 2;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p2Faction;
																						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "GEN") {
																							p2EnergyIncome += 2;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "MSC") {
																							p2MaxMass += 3;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "ENC") {
																							p2MaxEnergy += 5;
																						}
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																					}
																				}
																				isDone4 = true;
																				break;
																			case 'z':
																				system("cls");
																				isDone4 = true;
																				break;
																			}
																		}
																	}
																}
																else if(fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "LND" || fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "MON") {
																	if (displayMap[cursorCoords[1]][cursorCoords[0]] != "0-MAS" && fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 0) {
																		if ((playerTurn == 1 && p1Faction == 0) || (playerTurn == 2 && p2Faction == 0)) {
																			buildList = UEFLandBuild;
																		}
																		else if ((playerTurn == 1 && p1Faction == 1) || (playerTurn == 2 && p2Faction == 1)) {
																			buildList = AeonLandBuild;
																		}
																		else if ((playerTurn == 1 && p1Faction == 2) || (playerTurn == 2 && p2Faction == 2)) {
																			buildList = CybranLandBuild;
																		}
																		else {
																			buildList = SeraphimLandBuild;
																		}
																		isDone4 = false;
																		doRedraw2 = true;
																		op2 = 0;
																		while (!isDone4) {
																			if (doRedraw2) {
																				system("cls");
																				std::cout << "Select a unit to build (W and S to navigate options, X to build that unit, Z to cancel):" << std::endl;
																				for (int i = 0; i < buildList.size(); i++) {
																					std::cout << buildList[i].unitName;
																					if (i == op2) {
																						std::cout << " <--";
																					}
																					std::cout << std::endl;
																				}
																				std::cout << std::endl;
																				wordCount = 0;
																				for (int i = 0; i < size(buildList[op2].description); i++) {
																					wordCount++;
																					std::cout << buildList[op2].description[i];
																					if (wordCount > 90 && buildList[op2].description[i] == ' ') {
																						std::cout << std::endl;
																						wordCount = 0;
																					}
																				}
																				std::cout << "\n[Mass: " << buildList[op2].mass << ", Energy: " << buildList[op2].energy << "]" << std::endl;
																				doRedraw2 = false;
																			}
																			char c = _getch();
																			switch (c) {
																			case 'w':
																				if (op2 > 0) {
																					op2--;
																				}
																				doRedraw2 = true;
																				break;
																			case 's':
																				if (op2 < buildList.size() - 1) {
																					op2++;
																				}
																				doRedraw2 = true;
																				break;
																			case 'x':
																				system("cls");
																				if (playerTurn == 1) {
																					if (p1Mass >= buildList[op2].mass && p1Energy >= buildList[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p1Mass -= buildList[op2].mass;
																						p1Energy -= buildList[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(buildList[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 1;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p1Faction;
																						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "GEN") {
																							p1EnergyIncome += 2;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "MSC") {
																							p1MaxMass += 3;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "ENC") {
																							p1MaxEnergy += 5;
																						}
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																						system("pause");
																					}
																				}
																				else {
																					if (p2Mass >= buildList[op2].mass && p2Energy >= buildList[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p2Mass -= buildList[op2].mass;
																						p2Energy -= buildList[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(buildList[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 2;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p2Faction;
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																					}
																				}
																				isDone4 = true;
																				break;
																			case 'z':
																				system("cls");
																				isDone4 = true;
																				break;
																			}
																		}
																	}
																	else {
																		std::cout << "That space is already taken!" << std::endl;
																	}
																}
																else if (fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "AIR" || fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "STA" || fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "VIS") {
																	if (displayMap[cursorCoords[1]][cursorCoords[0]] != "0-MAS" && fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 0) {
																		if ((playerTurn == 1 && p1Faction == 0) || (playerTurn == 2 && p2Faction == 0)) {
																			buildList = UEFAirBuild;
																		}
																		else if ((playerTurn == 1 && p1Faction == 1) || (playerTurn == 2 && p2Faction == 1)) {
																			buildList = AeonAirBuild;
																		}
																		else if ((playerTurn == 1 && p1Faction == 2) || (playerTurn == 2 && p2Faction == 2)) {
																			buildList = CybranAirBuild;
																		}
																		else {
																			buildList = SeraphimAirBuild;
																		}
																		isDone4 = false;
																		doRedraw2 = true;
																		op2 = 0;
																		while (!isDone4) {
																			if (doRedraw2) {
																				system("cls");
																				std::cout << "Select a unit to build (W and S to navigate options, X to build that unit, Z to cancel):" << std::endl;
																				for (int i = 0; i < buildList.size(); i++) {
																					std::cout << buildList[i].unitName;
																					if (i == op2) {
																						std::cout << " <--";
																					}
																					std::cout << std::endl;
																				}
																				std::cout << std::endl;
																				wordCount = 0;
																				for (int i = 0; i < size(buildList[op2].description); i++) {
																					wordCount++;
																					std::cout << buildList[op2].description[i];
																					if (wordCount > 90 && buildList[op2].description[i] == ' ') {
																						std::cout << std::endl;
																						wordCount = 0;
																					}
																				}
																				std::cout << "\n[Mass: " << buildList[op2].mass << ", Energy: " << buildList[op2].energy << "]" << std::endl;
																				doRedraw2 = false;
																			}
																			char c = _getch();
																			switch (c) {
																			case 'w':
																				if (op2 > 0) {
																					op2--;
																				}
																				doRedraw2 = true;
																				break;
																			case 's':
																				if (op2 < buildList.size() - 1) {
																					op2++;
																				}
																				doRedraw2 = true;
																				break;
																			case 'x':
																				system("cls");
																				if (playerTurn == 1) {
																					if (p1Mass >= buildList[op2].mass && p1Energy >= buildList[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p1Mass -= buildList[op2].mass;
																						p1Energy -= buildList[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(buildList[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 1;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p1Faction;
																						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "GEN") {
																							p1EnergyIncome += 2;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "MSC") {
																							p1MaxMass += 3;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "ENC") {
																							p1MaxEnergy += 5;
																						}
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																						system("pause");
																					}
																				}
																				else {
																					if (p2Mass >= buildList[op2].mass && p2Energy >= buildList[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p2Mass -= buildList[op2].mass;
																						p2Energy -= buildList[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(buildList[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 2;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p2Faction;
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																					}
																				}
																				isDone4 = true;
																				break;
																			case 'z':
																				system("cls");
																				isDone4 = true;
																				break;
																			}
																		}
																	}
																	else {
																		std::cout << "That space is already taken!" << std::endl;
																	}
																}
																else if (fieldUnits[ogCursorCoordsY][ogCursorCoordsX].displayName == "EXF") {
																	if (displayMap[cursorCoords[1]][cursorCoords[0]] != "0-MAS" && fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 0) {
																		if ((playerTurn == 1 && p1Faction == 0) || (playerTurn == 2 && p2Faction == 0)) {
																			buildList = UEFExperimentalBuild;
																		}
																		else if ((playerTurn == 1 && p1Faction == 1) || (playerTurn == 2 && p2Faction == 1)) {
																			buildList = AeonExperimentalBuild;
																		}
																		else if ((playerTurn == 1 && p1Faction == 2) || (playerTurn == 2 && p2Faction == 2)) {
																			buildList = CybranExperimentalBuild;
																		}
																		else {
																			buildList = SeraphimExperimentalBuild;
																		}
																		isDone4 = false;
																		doRedraw2 = true;
																		op2 = 0;
																		while (!isDone4) {
																			if (doRedraw2) {
																				system("cls");
																				std::cout << "Select a unit to build (W and S to navigate options, X to build that unit, Z to cancel):" << std::endl;
																				for (int i = 0; i < buildList.size(); i++) {
																					std::cout << buildList[i].unitName;
																					if (i == op2) {
																						std::cout << " <--";
																					}
																					std::cout << std::endl;
																				}
																				std::cout << std::endl;
																				wordCount = 0;
																				for (int i = 0; i < size(buildList[op2].description); i++) {
																					wordCount++;
																					std::cout << buildList[op2].description[i];
																					if (wordCount > 90 && buildList[op2].description[i] == ' ') {
																						std::cout << std::endl;
																						wordCount = 0;
																					}
																				}
																				std::cout << "\n[Mass: " << buildList[op2].mass << ", Energy: " << buildList[op2].energy << "]" << std::endl;
																				doRedraw2 = false;
																			}
																			char c = _getch();
																			switch (c) {
																			case 'w':
																				if (op2 > 0) {
																					op2--;
																				}
																				doRedraw2 = true;
																				break;
																			case 's':
																				if (op2 < buildList.size() - 1) {
																					op2++;
																				}
																				doRedraw2 = true;
																				break;
																			case 'x':
																				system("cls");
																				if (playerTurn == 1) {
																					if (p1Mass >= buildList[op2].mass && p1Energy >= buildList[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p1Mass -= buildList[op2].mass;
																						p1Energy -= buildList[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(buildList[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 1;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p1Faction;
																						if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "GEN") {
																							p1EnergyIncome += 2;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "MSC") {
																							p1MaxMass += 3;
																						}
																						else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].displayName == "ENC") {
																							p1MaxEnergy += 5;
																						}
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																						system("pause");
																					}
																				}
																				else {
																					if (p2Mass >= buildList[op2].mass && p2Energy >= buildList[op2].energy) {
																						std::cout << "Unit sucessfully built!" << std::endl;
																						p2Mass -= buildList[op2].mass;
																						p2Energy -= buildList[op2].energy;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]] = retrieveUnit(buildList[op2].unitID);
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].xpos = cursorCoords[0];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].ypos = cursorCoords[1];
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer = 2;
																						fieldUnits[cursorCoords[1]][cursorCoords[0]].factionID = p2Faction;
																					}
																					else {
																						std::cout << "You don't have enough resources to build that!" << std::endl;
																					}
																				}
																				isDone4 = true;
																				break;
																			case 'z':
																				system("cls");
																				isDone4 = true;
																				break;
																			}
																		}
																	}
																	else {
																		std::cout << "That space is already taken!" << std::endl;
																	}
																}
															}
															else {
																std::cout << "That spot is out of range!" << std::endl;
															}
														}
														else {
															std::cout << fieldUnits[ogCursorCoordsY][ogCursorCoordsX].doAttack(fieldUnits[ogCursorCoordsY][ogCursorCoordsX].actions[op2], &fieldUnits, cursorCoords[0], cursorCoords[1], getVectorMap(displayMap), fowSettings) << std::endl;
															for (int i = 0; i < 15; i++) {
																for (int j = 0; j < 15; j++) {
																	if (fieldUnits[i][j].health <= 0) {
																		if (i == ogCursorCoordsY && j == ogCursorCoordsX) {
																			isDone2 = true;
																			isDone3 = true;
																			isDone4 = true;
																		}
																		if (fieldUnits[i][j].displayName == "ACU") {
																			SetConsoleTextAttribute(h, ResetKey);
																			for (int j = 0; j < 15; j++) {
																				SetConsoleTextAttribute(h, 119);
																				for (int i = 0; i < 100; i++) {
																					std::cout << "SKREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
																				}
																				Sleep(5);
																				SetConsoleTextAttribute(h, 0);
																				for (int i = 0; i < 100; i++) {
																					std::cout << "SKREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
																				}
																			}
																			system("cls");
																			SetConsoleTextAttribute(h, ResetKey);
																			Sleep(1);
																			if (playerTurn == 1) {
																				std::cout << "Player 1 wins!" << std::endl;
																				std::cout << "The ";
																				switch (p1Faction) {
																				case 0:
																					std::cout << "UEF ";
																					break;
																				case 1:
																					std::cout << "Aeon ";
																					break;
																				case 2:
																					std::cout << "Cybran ";
																					break;
																				case 3:
																					std::cout << "Seraphim ";
																					break;
																				}
																				std::cout << "reigns victorious!" << std::endl;
																				system("pause");
																				system("cls");
																				isDone = true;
																				isDone2 = true;
																				isDone3 = true;
																				isDone4 = true;
																			}
																			else {
																				std::cout << "Player 2 wins!" << std::endl;
																				std::cout << "The ";
																				switch (p2Faction) {
																				case 0:
																					std::cout << "UEF ";
																					break;
																				case 1:
																					std::cout << "Aeon ";
																					break;
																				case 2:
																					std::cout << "Cybran ";
																					break;
																				case 3:
																					std::cout << "Seraphim ";
																					break;
																				}
																				std::cout << "reigns victorious!" << std::endl;
																				system("pause");
																				system("cls");
																				isDone = true;
																				isDone2 = true;
																				isDone3 = true;
																				isDone4 = true;
																			}
																		}
																		else if (fieldUnits[i][j].displayName == "MAS") {
																			if (fieldUnits[i][j].owningPlayer == 1) {
																				p1MassIncome -= 1;
																			}
																			else {
																				p2MassIncome -= 1;
																			}
																		}
																		else if (fieldUnits[i][j].displayName == "GEN") {
																			if (fieldUnits[i][j].owningPlayer == 1) {
																				p1EnergyIncome -= 2;
																			}
																			else {
																				p2EnergyIncome -= 1;
																			}
																		}
																		else if (fieldUnits[i][j].displayName == "MSC") {
																			if (fieldUnits[i][j].owningPlayer == 1) {
																				p1MaxMass -= 3;
																				if (p1Mass > p1MaxMass) {
																					p1MaxMass = p1Mass;
																				}
																			}
																			else {
																				p2MaxMass -= 3;
																				if (p2Mass > p2MaxMass) {
																					p2MaxMass = p2Mass;
																				}
																			}
																		}
																		else if (fieldUnits[i][j].displayName == "ENC") {
																			if (fieldUnits[i][j].owningPlayer == 1) {
																				p1MaxEnergy -= 5;
																				if (p1Energy > p1MaxEnergy) {
																					p1MaxEnergy = p1Energy;
																				}
																			}
																			else {
																				p2MaxEnergy -= 5;
																				if (p2Energy > p2MaxEnergy) {
																					p2MaxEnergy = p2Energy;
																				}
																			}
																		}
																		fieldUnits[i][j] = Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, cursorCoords[0], cursorCoords[1], 0, 0);
																		redoUnitLogic = true;
																		doRedraw = true;
																		doRedraw2 = true;
																	}
																}
															}
														}
														system("pause");
														isDone4 = true;
														cursorCoords[0] = ogCursorCoordsX;
														cursorCoords[1] = ogCursorCoordsY;
														break;
													}
												}
											}
											else {
											std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].doAttack(fieldUnits[cursorCoords[1]][cursorCoords[0]].actions[op2], &fieldUnits, cursorCoords[0], cursorCoords[1], getVectorMap(displayMap), fowSettings) << std::endl;
											for (int i = 0; i < 15; i++) {
												for (int j = 0; j < 15; j++) {
													if (fieldUnits[i][j].health <= 0) {
														if (i == ogCursorCoordsY && j == ogCursorCoordsX) {
															isDone2 = true;
															isDone3 = true;
															isDone4 = true;
														}
														if (fieldUnits[i][j].displayName == "ACU") {
															SetConsoleTextAttribute(h, ResetKey);
															for (int j = 0; j < 15; j++) {
																SetConsoleTextAttribute(h, 119);
																for (int i = 0; i < 100; i++) {
																	std::cout << "SKREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
																}
																Sleep(5);
																SetConsoleTextAttribute(h, 0);
																for (int i = 0; i < 100; i++) {
																	std::cout << "SKREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
																}
															}
															system("cls");
															SetConsoleTextAttribute(h, ResetKey);
															Sleep(1);
															if (playerTurn == 1) {
																std::cout << "Player 1 wins!" << std::endl;
																std::cout << "The ";
																switch (p1Faction) {
																case 0:
																	std::cout << "UEF ";
																	break;
																case 1:
																	std::cout << "Aeon ";
																	break;
																case 2:
																	std::cout << "Cybran ";
																	break;
																case 3:
																	std::cout << "Seraphim ";
																	break;
																}
																std::cout << "reigns victorious!" << std::endl;
																system("pause");
																system("cls");
																isDone = true;
																isDone2 = true;
																isDone3 = true;
																isDone4 = true;
															}
															else {
																std::cout << "Player 2 wins!" << std::endl;
																std::cout << "The ";
																switch (p2Faction) {
																case 0:
																	std::cout << "UEF ";
																	break;
																case 1:
																	std::cout << "Aeon ";
																	break;
																case 2:
																	std::cout << "Cybran ";
																	break;
																case 3:
																	std::cout << "Seraphim ";
																	break;
																}
																std::cout << "reigns victorious!" << std::endl;
																system("pause");
																system("cls");
																isDone = true;
																isDone2 = true;
																isDone3 = true;
																isDone4 = true;
															}
														}
														else if (fieldUnits[i][j].displayName == "MAS") {
															if (fieldUnits[i][j].owningPlayer == 1) {
																p1MassIncome -= 1;
															}
															else {
																p2MassIncome -= 1;
															}
														}
														else if (fieldUnits[i][j].displayName == "GEN") {
															if (fieldUnits[i][j].owningPlayer == 1) {
																p1EnergyIncome -= 2;
															}
															else {
																p2EnergyIncome -= 1;
															}
														}
														else if (fieldUnits[i][j].displayName == "MSC") {
															if (fieldUnits[i][j].owningPlayer == 1) {
																p1MaxMass -= 3;
																if (p1Mass > p1MaxMass) {
																	p1MaxMass = p1Mass;
																}
															}
															else {
																p2MaxMass -= 3;
																if (p2Mass > p2MaxMass) {
																	p2MaxMass = p2Mass;
																}
															}
														}
														else if (fieldUnits[i][j].displayName == "ENC") {
															if (fieldUnits[i][j].owningPlayer == 1) {
																p1MaxEnergy -= 5;
																if (p1Energy > p1MaxEnergy) {
																	p1MaxEnergy = p1Energy;
																}
															}
															else {
																p2MaxEnergy -= 5;
																if (p2Energy > p2MaxEnergy) {
																	p2MaxEnergy = p2Energy;
																}
															}
														}
														fieldUnits[i][j] = Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, cursorCoords[0], cursorCoords[1], 0, 0);
														redoUnitLogic = true;
														doRedraw = true;
														doRedraw2 = true;
													}
												}
											}
											system("pause");
											}
											isDone3 = true;
											break;
										case 'z':
											system("cls");
											isDone3 = true;
											break;
										}
									}
								}
								else {
									if (fieldUnits[cursorCoords[1]][cursorCoords[0]].actions.size() <= 0) {
										std::cout << "This unit cannot take any action!" << std::endl;
									}
									else {
										std::cout << "This unit already took an action!" << std::endl;
									}
									
									system("pause");
								}
								break;
							case 2: // Unit inspection
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 1) {
									SetConsoleTextAttribute(h, getFactionColour(p1Faction));
								}
								else {
									SetConsoleTextAttribute(h, getFactionColour(p2Faction));
								}
								std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].name + ":" << std::endl;
								int wordCount = 0;
								for (int i = 0; i < size(fieldUnits[cursorCoords[1]][cursorCoords[0]].description); i++) {
									wordCount++;
									std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].description[i];
									if (wordCount > 90 && fieldUnits[cursorCoords[1]][cursorCoords[0]].description[i] == ' ') {
										std::cout << std::endl;
										wordCount = 0;
									}
								}
								std::cout << "\n\n";
								std::cout << "Health: " << fieldUnits[cursorCoords[1]][cursorCoords[0]].health << "/" << fieldUnits[cursorCoords[1]][cursorCoords[0]].maxHealth << std::endl;
								std::cout << "Type: ";
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].isAir) {
									std::cout << "Air\n" << std::endl;
								}
								else {
									std::cout << "Land\n" << std::endl;
								}
								
								system("pause");
								SetConsoleTextAttribute(h, ResetKey);
								break;
							}
						}
						else {
							if (fowSettings == 2) {
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 1) {
									SetConsoleTextAttribute(h, getFactionColour(p1Faction));
								}
								else {
									SetConsoleTextAttribute(h, getFactionColour(p2Faction));
								}
								std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].name + ":" << std::endl;
								int wordCount = 0;
								for (int i = 0; i < size(fieldUnits[cursorCoords[1]][cursorCoords[0]].description); i++) {
									wordCount++;
									std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].description[i];
									if (wordCount > 90 && fieldUnits[cursorCoords[1]][cursorCoords[0]].description[i] == ' ') {
										std::cout << std::endl;
										wordCount = 0;
									}
								}
								std::cout << "\n\n";
								std::cout << "Health: " << fieldUnits[cursorCoords[1]][cursorCoords[0]].health << "/" << fieldUnits[cursorCoords[1]][cursorCoords[0]].maxHealth << std::endl;
								std::cout << "Type: ";
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].isAir) {
									std::cout << "Air\n" << std::endl;
								}
								else {
									std::cout << "Land\n" << std::endl;
								}

								system("pause");
								SetConsoleTextAttribute(h, ResetKey);
							}
							else {
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].owningPlayer == 1) {
									SetConsoleTextAttribute(h, getFactionColour(p1Faction));
								}
								else {
									SetConsoleTextAttribute(h, getFactionColour(p2Faction));
								}
								std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].name + ":" << std::endl;
								int wordCount = 0;
								for (int i = 0; i < size(fieldUnits[cursorCoords[1]][cursorCoords[0]].description); i++) {
									wordCount++;
									std::cout << fieldUnits[cursorCoords[1]][cursorCoords[0]].description[i];
									if (wordCount > 90 && fieldUnits[cursorCoords[1]][cursorCoords[0]].description[i] == ' ') {
										std::cout << std::endl;
										wordCount = 0;
									}
								}
								std::cout << "\n\n";
								std::cout << "Status: ";
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].health > (fieldUnits[cursorCoords[1]][cursorCoords[0]].maxHealth * 0.8)) {std::cout << "Stable condition." << std::endl;}
								else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].health > (fieldUnits[cursorCoords[1]][cursorCoords[0]].maxHealth * 0.6)) { std::cout << "Partially damaged." << std::endl; }
								else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].health > (fieldUnits[cursorCoords[1]][cursorCoords[0]].maxHealth * 0.4)) { std::cout << "Damaged." << std::endl; }
								else if (fieldUnits[cursorCoords[1]][cursorCoords[0]].health > (fieldUnits[cursorCoords[1]][cursorCoords[0]].maxHealth * 0.2)) { std::cout << "Severly damaged." << std::endl; }
								else { std::cout << "Almost destroyed." << std::endl; }
								std::cout << "Type: ";
								if (fieldUnits[cursorCoords[1]][cursorCoords[0]].isAir) {
									std::cout << "Air\n" << std::endl;
								}
								else {
									std::cout << "Land\n" << std::endl;
								}

								system("pause");
								SetConsoleTextAttribute(h, ResetKey);
							}
						}
						doRedraw = true;
						break;
					case 'z':
						system("cls");
						isDone2 = true;
						op1 = 0;
						break;
					}
				}
			}

			doRedraw = true;
			break;
		case 'p':
			system("cls");
			doRedraw = true;
			redoUnitLogic = true;
			cursorCoords[0] = 0;
			cursorCoords[1] = 0;

			// Handle shiled functionality. First reset everyone's shields and re-apply them after.
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					fieldUnits[i][j].isShielded = false;
				}
			}
			
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					if (fieldUnits[i][j].owningPlayer > 0 && (fieldUnits[i][j].displayName == "PAR" || fieldUnits[i][j].displayName == "MER" || fieldUnits[i][j].displayName == "SUT" || fieldUnits[i][j].displayName == "ADP")) { // Display name of any units with a shield goes here
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i - 1][j].owningPlayer) {
							fieldUnits[i - 1][j].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i - 1][j + 1].owningPlayer) {
							fieldUnits[i - 1][j + 1].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i][j + 1].owningPlayer) {
							fieldUnits[i][j + 1].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i + 1][j + 1].owningPlayer) {
							fieldUnits[i + 1][j + 1].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i + 1][j].owningPlayer) {
							fieldUnits[i + 1][j].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i + 1][j - 1].owningPlayer) {
							fieldUnits[i + 1][j - 1].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i][j - 1].owningPlayer) {
							fieldUnits[i][j - 1].isShielded = true;
						}
						if (fieldUnits[i][j].owningPlayer == fieldUnits[i - 1][j - 1].owningPlayer) {
							fieldUnits[i - 1][j - 1].isShielded = true;
						}
					}
				}
			}

			if (playerTurn == 1) {
				playerTurn = 2;
				p2Mass += p2MassIncome;
				if (p2Mass > p2MaxMass) { p2Mass = p2MaxMass; };
				p2Energy += p2EnergyIncome;
				if (p2Energy > p2MaxEnergy) { p2Energy = p2MaxEnergy; };
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						if (fieldUnits[i][j].owningPlayer == 1) {
							fieldUnits[i][j].EndTurn(fieldUnits, getVectorMap(displayMap));
							fieldUnits[i][j].canTakeAction = true;
							fieldUnits[i][j].movesLeft = fieldUnits[i][j].movementRange;
						}
					}
				}

				SetConsoleTextAttribute(h, ResetKey);
				std::cout << "Pass the controls over to player 2 and press enter..." << std::endl;
				system("pause");
			}
			else {
				playerTurn = 1;
				p1Mass += p1MassIncome;
				if (p1Mass > p1MaxMass) { p1Mass = p1MaxMass; };
				p1Energy += p1EnergyIncome;
				if (p1Energy > p1MaxEnergy) { p1Energy = p1MaxEnergy; };
				for (int i = 0; i < 15; i++) {
					for (int j = 0; j < 15; j++) {
						if (fieldUnits[i][j].owningPlayer == 2) {
							fieldUnits[i][j].EndTurn(fieldUnits, getVectorMap(displayMap));
							fieldUnits[i][j].canTakeAction = true;
							fieldUnits[i][j].movesLeft = fieldUnits[i][j].movementRange;
						}
					}
				}

				SetConsoleTextAttribute(h, ResetKey);
				std::cout << "Pass the controls over to player 1 and press enter..." << std::endl;
				system("pause");
			}
			break;
		}
	}
}

void setup() {
	// Prepare blankslate units
	fieldUnits.clear();
	for (int i = 0; i < 15; i++) {
		std::vector<Unit> tempVec;
		for (int j = 0; j < 15; j++) {
			Unit emptyUnit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, j, i, 0, 0);
			tempVec.push_back(emptyUnit);
		}
		fieldUnits.push_back(tempVec);
	}

	bool isDone = false;
	bool doRedraw = true;
	int selectedOp = 0;
	while (!isDone) { // Map selection
		if (doRedraw) {
			system("cls");
			std::cout << "Select the map you want to play on:" << std::endl;
			std::cout << "(Use A and D to navigate the maps, X to select the map)\n" << std::endl;
			
			if (selectedOp > 0) { std::cout << "<-- "; }
			else { std::cout << "    "; }
			std::cout << gm.mapNames[selectedOp];
			if (selectedOp < 2) { std::cout << " -->"; }
			else { std::cout << "    "; }
			std::cout << std::endl;

			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					std::cout << gm.maps[selectedOp][i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			
			// Map description (this wraps the text)
			int wordCount = 0;
			for (int i = 0; i < size(gm.mapDescriptions[selectedOp]); i++) {
				wordCount++;
				std::cout << gm.mapDescriptions[selectedOp][i];
				if (wordCount > 90 && gm.mapDescriptions[selectedOp][i] == ' ') {
					std::cout << std::endl;
					wordCount = 0;
				}
			}

			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "|SP1| - Spawn point for player 1." << std::endl;
			std::cout << "|SP2| - Spawn point for player 2." << std::endl;
			std::cout << "0-MAS - Mass point." << std::endl;
			std::cout << "||||| - Impassible wall." << std::endl;

			doRedraw = false;
		}

		char c = _getch();
		switch (c) {
		case 'a':
			if (selectedOp > 0) {
				selectedOp--;
				doRedraw = true;
			}
			break;
		case 'd':
			if (selectedOp < 2) {
				selectedOp++;
				doRedraw = true;
			}
			break;
		case 'x':
			system("cls");
			isDone = true;
			for (int i = 0; i < 15; i++) { // Place the map into a temporary variable which can be freely edited.
				for (int j = 0; j < 15; j++) {
					map[i][j] = gm.maps[selectedOp][i][j];
				}
			}
			break;
		}
	}

	isDone = false;
	doRedraw = true;
	selectedOp = 0;
	while (!isDone) {
		if (doRedraw) {
			system("cls");
			std::cout << "Select player 1's faction:" << std::endl;
			std::cout << "(Use A and D to navigate the different factions, X to select the map)\n" << std::endl;

			if (selectedOp > 0) { std::cout << "<-- "; }
			else { std::cout << "    "; }
			
			switch (selectedOp) {
			case 0:
				SetConsoleTextAttribute(h, 9);
				std::cout << "UEF";
				break;
			case 1:
				SetConsoleTextAttribute(h, 2);
				std::cout << "Aeon";
				break;
			case 2:
				SetConsoleTextAttribute(h, 4);
				std::cout << "Cybran";
				break;
			case 3:
				SetConsoleTextAttribute(h, 14);
				std::cout << "Seraphrim";
				break;
			}
			SetConsoleTextAttribute(h, ResetKey);

			if (selectedOp < 3) { std::cout << " -->"; }
			else { std::cout << "    "; }
			std::cout << std::endl;

			std::string factionDescription;
			switch (selectedOp) {
			case 0:
				SetConsoleTextAttribute(h, 9);
				factionDescription = "The UEF stands for the United Earth Federation, and is a militiristic force seeking to unify the once great empire that is now splintered. They are at constant war with the Aeons and Cybrans, however despite the threat, they rely on conventional weaponry such as battle tanks and bullets. The UEF tends to be more defence-oriented, being slow moving during attacks and easily punishable for overextending. However, if a UEF commander sets up a defence, it will be a near-impenetrable one and can lead to a sudden assault later down the road.";
				break;
			case 1:
				SetConsoleTextAttribute(h, 2);
				factionDescription = "Aeons are comprised of humans who follow the way - Philosiphy of the Seraphim aliens found years ago on Seraphim II before they were wiped out by xenophobic humans. Due to a misunderstanding, Aeons are at constant war with the UEF and Cybrans, attempting to spread knowledge of the way using technology the Seraphim taught them. Aeon are generally weak and feeble early on in any mission, however over time, their army grows to become one of the most powerful, easily capable of wiping out any other commanders. If you face an Aeon, take them out as soon as possible.";
				break;
			case 2:
				SetConsoleTextAttribute(h, 4);
				factionDescription = "Cybrans were once enslaved by the Earth Forces, but eventually broke away from Earth and fougth for their freedom against the UEF, which is there main enemy. While Aeon units are not their primary target, they often get in the way of the Aeon's objective of spreading the way, and as a result are considered enemies as well. Cybrans are fast and agile, hitting hard and launching surprise attacks that boast power and agility. However, Cybrans lack defence, being easily overwhelmed or countered if a weakness is exploited. A cybran is fast and deadly early on, but if a battle drags out for too long, they may find themselves at the disadvantage.";
				break;
			case 3:
				SetConsoleTextAttribute(h, 14);
				factionDescription = "Seraphim are an alien species who taught members of the Aeon the way. Their command is comprised of those who follow the way and fight at the same time. Their ultimate goal is the total domination of the galaxy, which constantly puts them at odds against the UEF and Cybrans, however not the Aeons. Seraphim fighting styles are generally unorthadox, not relying on large pushes or stalwart defences. They do a bit of everything, before throwing a haymaker thanks to the variety of options their units present. If you face a Seraphim, be ready for anything.";
				break;
			}
			std::cout << std::endl;

			int wordCount = 0;
			for (int i = 0; i < size(factionDescription); i++) {
				wordCount++;
				std::cout << factionDescription[i];
				if (wordCount > 90 && factionDescription[i] == ' ') {
					std::cout << std::endl;
					wordCount = 0;
				}
			}

			SetConsoleTextAttribute(h, ResetKey);
			doRedraw = false;
		}

		char c = _getch();
		switch (c) {
		case 'a':
			if (selectedOp > 0) {
				selectedOp--;
				doRedraw = true;
			}
			break;
		case 'd':
			if (selectedOp < 3) {
				selectedOp++;
				doRedraw = true;
			}
			break;
		case 'x':
			system("cls");
			isDone = true;
			p1Faction = selectedOp;
			selectedOp = 0;
			break;
		}
	}

	isDone = false;
	doRedraw = true;
	selectedOp = 0;
	while (!isDone) {
		if (doRedraw) {
			system("cls");
			std::cout << "Select player 2's faction:" << std::endl;
			std::cout << "(Use A and D to navigate the different factions, X to select the map)\n" << std::endl;

			if (selectedOp > 0) { std::cout << "<-- "; }
			else { std::cout << "    "; }

			switch (selectedOp) {
			case 0:
				SetConsoleTextAttribute(h, 9);
				std::cout << "UEF";
				break;
			case 1:
				SetConsoleTextAttribute(h, 2);
				std::cout << "Aeon";
				break;
			case 2:
				SetConsoleTextAttribute(h, 4);
				std::cout << "Cybran";
				break;
			case 3:
				SetConsoleTextAttribute(h, 14);
				std::cout << "Seraphrim";
				break;
			}
			SetConsoleTextAttribute(h, ResetKey);

			if (selectedOp < 3) { std::cout << " -->"; }
			else { std::cout << "    "; }
			std::cout << std::endl;

			std::string factionDescription;
			switch (selectedOp) {
			case 0:
				SetConsoleTextAttribute(h, 9);
				factionDescription = "The UEF stands for the United Earth Federation, and is a militiristic force seeking to unify the once great empire that is now splintered. They are at constant war with the Aeons and Cybrans, however despite the threat, they rely on conventional weaponry such as battle tanks and bullets. The UEF tends to be more defence-oriented, being slow moving during attacks and easily punishable for overextending. However, if a UEF commander sets up a defence, it will be a near-impenetrable one and can lead to a sudden assault later down the road.";
				break;
			case 1:
				SetConsoleTextAttribute(h, 2);
				factionDescription = "Aeons are comprised of humans who follow the way - Philosiphy of the Seraphim aliens found years ago on Seraphim II before they were wiped out by xenophobic humans. Due to a misunderstanding, Aeons are at constant war with the UEF and Cybrans, attempting to spread knowledge of the way using technology the Seraphim taught them. Aeon are generally weak and feeble early on in any mission, however over time, their army grows to become one of the most powerful, easily capable of wiping out any other commanders. If you face an Aeon, take them out as soon as possible.";
				break;
			case 2:
				SetConsoleTextAttribute(h, 4);
				factionDescription = "Cybrans were once enslaved by the Earth Forces, but eventually broke away from Earth and fougth for their freedom against the UEF, which is there main enemy. While Aeon units are not their primary target, they often get in the way of the Aeon's objective of spreading the way, and as a result are considered enemies as well. Cybrans are fast and agile, hitting hard and launching surprise attacks that boast power and agility. However, Cybrans lack defence, being easily overwhelmed or countered if a weakness is exploited. A cybran is fast and deadly early on, but if a battle drags out for too long, they may find themselves at the disadvantage.";
				break;
			case 3:
				SetConsoleTextAttribute(h, 14);
				factionDescription = "Seraphim are an alien species who taught members of the Aeon the way. Their command is comprised of those who follow the way and fight at the same time. Their ultimate goal is the total domination of the galaxy, which constantly puts them at odds against the UEF and Cybrans, however not the Aeons. Seraphim fighting styles are generally unorthadox, not relying on large pushes or stalwart defences. They do a bit of everything, before throwing a haymaker thanks to the variety of options their units present. If you face a Seraphim, be ready for anything.";
				break;
			}
			std::cout << std::endl;

			int wordCount = 0;
			for (int i = 0; i < size(factionDescription); i++) {
				wordCount++;
				std::cout << factionDescription[i];
				if (wordCount > 90 && factionDescription[i] == ' ') {
					std::cout << std::endl;
					wordCount = 0;
				}
			}

			SetConsoleTextAttribute(h, ResetKey);
			doRedraw = false;
		}

		char c = _getch();
		switch (c) {
		case 'a':
			if (selectedOp > 0) {
				selectedOp--;
				doRedraw = true;
			}
			break;
		 case 'd':
			if (selectedOp < 3) {
				selectedOp++;
				doRedraw = true;
			}
			break;
		case 'x':
			system("cls");
			isDone = true;
			p2Faction = selectedOp;
			selectedOp = 0;
			break;
		}
	}

	isDone = false;
	doRedraw = true;
	selectedOp = 0;
	while (!isDone) {
		if (doRedraw) {
			system("cls");
			std::cout << "Select fog of war settings:" << std::endl;
			std::cout << "(Use A and D to navigate the different factions, X to select the amount of fog of war you want to play with)\n" << std::endl;

			if (selectedOp > 0) { std::cout << "<-- "; }
			else { std::cout << "    "; }

			switch (selectedOp) {
			case 0:
				SetConsoleTextAttribute(h, 2);
				std::cout << "Fog of War";
				break;
			case 1:
				SetConsoleTextAttribute(h, 14);
				std::cout << "Partial Fog of War";
				break;
			case 2:
				SetConsoleTextAttribute(h, 4);
				std::cout << "No Fog of War";
				break;
			}
			SetConsoleTextAttribute(h, ResetKey);

			if (selectedOp < 2) { std::cout << " -->"; }
			else { std::cout << "    "; }
			std::cout << std::endl;

			std::string factionDescription;
			switch (selectedOp) {
			case 0:
				SetConsoleTextAttribute(h, 2);
				factionDescription = "Fog of war means you will only be able to see spaces that are on your units' radar. All other spaces will be marked as ##### and all units there will be invisible. You will not be able to see the health of units, only seeing their state (undamaged, partially damaged, damaged, nearly destroyed) when you inspect them. Walls and mass deposits will still be visible even in unexplored areas, however you won't be able to see who controls which mass deposits if they aren't in your units' radars. Bomber planes will only be able to target spaces on your radar. Recommended for those who want to play fully strategical and who want to have a longer game.";
				break;
			case 1:
				SetConsoleTextAttribute(h, 14);
				factionDescription = "Similar to fog of war, however makes things slightly easier. You will be allowed to see the exact health value of enemy units when inspecting them and your bombers will now be allowed to launch bombing attacks on spaces that haven't been discovered or aren't on your radar yet. All other parts of regular fog of war stand. Recommended for those who stil want strategical play but also enjoys risk taking and feeling lucky.";
				break;
			case 2:
				SetConsoleTextAttribute(h, 4);
				factionDescription = "Fog of war is completely turned off and you can see everything even if it isn't on your radars. Bombing attacks can be launched anywhere and all units will be visible. This mode is suggested for those who are playing this game for the first time or if you want a faster battle.";
				break;
			}
			std::cout << std::endl;

			int wordCount = 0;
			for (int i = 0; i < size(factionDescription); i++) {
				wordCount++;
				std::cout << factionDescription[i];
				if (wordCount > 90 && factionDescription[i] == ' ') {
					std::cout << std::endl;
					wordCount = 0;
				}
			}

			SetConsoleTextAttribute(h, ResetKey);
			doRedraw = false;
		}

		char c = _getch();
		switch (c) {
		case 'a':
			if (selectedOp > 0) {
				selectedOp--;
				doRedraw = true;
			}
			break;
		case 'd':
			if (selectedOp < 2) {
				selectedOp++;
				doRedraw = true;
			}
			break;
		case 'x':
			system("cls");
			isDone = true;
			fowSettings = selectedOp;
			selectedOp = 0;
			break;
		}
	}

	game();
}

void help() { // Help page (credits page as well)
	std::cout << "Supreme Commander 0 - Bootleg Edition" << std::endl;
	std::cout << "This is a two-player game heavily based on Supreme Commander Forged Alliance." << std::endl;
	std::cout << "The game uses WASD and X. Both players will use the same keyboard (the game will tell you when to switch)." << std::endl;
	std::cout << "\nGame created by Boinga." << std::endl;
	std::cout << "Original game - Supreme Commander Forged Alliance by Square Enix.\n" << std::endl;
	system("pause");
}

void mainMenu() { // Main Menu
	bool isDone = false;
	bool doRedraw = true;
	int selectedOp = 0;
	while (!isDone) {
		if (doRedraw) {
			system("cls");
			std::cout << "Supreme Commander 0 - Bootleg Edition" << std::endl;
			std::cout << "(Use W and S to navigate menu, X to select an option)" << std::endl;
			std::cout << "Play";
			if (selectedOp == 0) { std::cout << " <--"; }
			std::cout << std::endl;
			std::cout << "Help + Credits";
			if (selectedOp == 1) { std::cout << " <--"; }
			std::cout << std::endl;
			std::cout << "Quit";
			if (selectedOp == 2) { std::cout << " <--"; }
			std::cout << std::endl;
			doRedraw = false;
		}
		// Gets key inputs
		char c = _getch();
		switch (c) {
		case 'w':
			if (selectedOp > 0) {
				selectedOp--;
				doRedraw = true;
			}
			break;
		case 's':
			if (selectedOp < 2) {
				selectedOp++;
				doRedraw = true;
			}
			break;
		case 'x':
			system("cls");
			doRedraw = true;
			switch (selectedOp) {
			case 0:
				setup();
				break;
			case 1:
				help();
				break;
			default:
				isDone = true;
				break;
			}
			break;
		}
	}
}

int main() {
	CONSOLE_SCREEN_BUFFER_INFO Info;
	GetConsoleScreenBufferInfo(h, &Info);
	ResetKey = Info.wAttributes;

	std::cout << "Loading..." << std::endl;
	defineUnits();

	mainMenu();
	return 0;
}