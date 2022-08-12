#include<string>

#pragma once
#define GAMEMANAGER_H
#ifdef GAMEMANAGER_H

class GameManager {
public:
	std::string maps[3][15][15];
	std::string mapNames[3];
	std::string mapDescriptions[3];
	int mapID;
	GameManager();
};

#endif GAMEMANAGER_H
