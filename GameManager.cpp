#include "GameManager.h"
#include<string>

GameManager::GameManager() {
	// Map names.
	this->mapNames[0] = "Tarus Straight";
	this->mapNames[1] = "Cybranic Fortress";
	this->mapNames[2] = "Field of Tranquility";

	this->mapDescriptions[0] = "A stronghold held by the UEF that was built to resist an assault from either Cybrans or Seriphram units. Aeon units who side with the UEF have some control over the area as well, and as a result it is a common place for UEF units to train against rebel Aeon units. The secondary base presented by the small area at the lower area of the base is a common favourite for trainee commanders.";
	this->mapDescriptions[1] = "A fortress in space held by the Cybrans. The fortress's only docking station leaves any UEF, Aeon, or Seriphram units vulnerable to air attacks from a Cybran commander on the other side. Cybran commanders often praise the structure of this place as it provides an effective defence while the offside area gives the oppertunity for an assault later when the enemy is weak.";
	this->mapDescriptions[2] = "The Field of Tranquility is a hostile environment with little structures to provide defence, hot airs that kill thousands every year, and more. Many attempt to avoid it, however everyone began to fight over the area when the Cybrans were found by the UEF holding this area. It's high mass deposit count has become an encticing proposition for commanders who want to help out their faction. Bases have been built to provide both an area for heavy offence in the open field in the middle as well as a safety bunker in case emergency evacuation is needed.";

	std::string tempMaps[3][15][15] = { // Temporary array that holds all of the maps.
		{
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "     ", "     ", "0-MAS", "|||||", "0-MAS", "     ", "     ", "0-MAS", "     ", "0-MAS", "|||||"},
			{"|||||", "|SP1|", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|SP2|", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "0-MAS", "     ", "0-MAS", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "|||||", "|||||", "|||||", "|||||", "|||||", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "0-MAS", "|||||", "0-MAS", "     ", "0-MAS", "|||||", "0-MAS", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||"}
		},
		{
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "     ", "     ", "     ", "     ", "     ", "     ", "0-MAS", "|||||", "     ", "0-MAS", "|||||"},
			{"|||||", "|SP1|", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "0-MAS", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "     ", "|||||", "     ", "0-MAS", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "     ", "|||||", "     ", "0-MAS", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "0-MAS", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "|SP2|", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "     ", "     ", "     ", "     ", "     ", "     ", "0-MAS", "|||||", "     ", "0-MAS", "|||||"},
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||"}
		},
		{
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "|||||", "0-MAS", "     ", "     ", "     ", "0-MAS", "|||||", "0-MAS", "     ", "     ", "|||||"},
			{"|||||", "|SP1|", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "|||||"},
			{"|||||", "0-MAS", "     ", "0-MAS", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "|||||", "|||||", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "0-MAS", "     ", "0-MAS", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "0-MAS", "     ", "0-MAS", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "|||||", "|||||", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "0-MAS", "     ", "0-MAS", "|||||"},
			{"|||||", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "|||||"},
			{"|||||", "     ", "     ", "     ", "|||||", "     ", "     ", "     ", "     ", "     ", "|||||", "     ", "     ", "|SP2|", "|||||"},
			{"|||||", "     ", "     ", "0-MAS", "|||||", "0-MAS", "     ", "     ", "     ", "0-MAS", "|||||", "0-MAS", "     ", "0-MAS", "|||||"},
			{"|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||", "|||||"}
		}
	};
	// Manually assigns each variable from the temporary arrays to the actual map arrays.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				this->maps[i][j][k] = tempMaps[i][j][k];
			}
		}
	}
}