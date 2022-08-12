#include "Unit.h"
#include<string>
#include<vector>
#include<iterator>
#include<map>

std::vector<Unit> units;

void defineUnits() {
	// Armoured Control Unit:
	Unit tempUnit(30, 4, 3, "Armoured Control Unit", "ACU", "An armoured control unit pioleted by the leader of the army. Destroying this will instantly bring the entire army down.", {
		// Attacks are defined here:
		Action("Photon Blast [Range: 4]", "Attack", 3, 4, 0),
		Action("Build [Range: 1]", "Build", 0, 0, 0),
		Action("Repair [Range: 1]", "Repair", 4, 0, 0),
		Action("Overdrive Curcuits", "Overdrive", 0, 0, 0)
		}, 0, 200, 0, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Mass Extractor:
	tempUnit = Unit(5, 3, 0, "Mass Extractor", "MAS", "An extractor that digs and refines mass from the ground for you to use in your army", {}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Energy Generator:
	tempUnit = Unit(3, 1, 0, "Energy Generator", "GEN", "A power generator that uses plasma reactions to provide your army with a steady supply of energy, one of the most important resources.", {}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Mass Storage:
	tempUnit = Unit(4, 1, 0, "Mass Storage", "MSC", "A solid container that can store unused mass for later, such as for emergencies or for a massive push.", {}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Energy Storage:
	tempUnit = Unit(2, 1, 0, "Energy Storage", "ENC", "A structure container several capacitators to store excess energy for later.", {}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Point Defence Turret:
	tempUnit = Unit(6, 4, 0, "Point Defence Turret", "PDT", "A static turret defence that can hold off incoming enemies and deal some damage to smaller armies. Becomes useless against experimentals other than being chump blockers.", {
	Action("Blast [Range: 4]", "Attack", 3, 4, 0)
	}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Anti-Air Turret:
	tempUnit = Unit(4, 5, 0, "Anti-Air Turret", "ADT", "A stationary defence turret that is best used in bases. It automatically attacks incoming bombers and can deal heavy damage to air units.", {
	Action("Blast [Range: 5]", "Direct Air Attack", 3, 5, 0)
	}, 0, 0, false, 3, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Land Factory:
	tempUnit = Unit(8, 4, 0, "Land Factory", "LND", "A factory that can create land units that can fight for you.", {
	Action("Build [Range: 1]", "Build", 0, 0, 0)
	}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Air Factory:
	tempUnit = Unit(6, 4, 0, "Air Factory", "AIR", "A factory that can create air units that can fight for you.", {
	Action("Build [Range: 1]", "Build", 0, 0, 0)
	}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Experimental Factory:
	tempUnit = Unit(12, 3, 0, "Experimental Factory", "EXF", "A massive factory that is capable of assembling experimental-class units.", {
	Action("Build [Range: 1]", "Build", 0, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Engineer:
	tempUnit = Unit(4, 4, 3, "Engineer", "ENG", "A mobile unit that cannot fight back, but can build other structures to expand your base without risking destruction to your ACU.", {
		Action("Build [Range: 1]", "Build", 0, 0, 0),
		Action("Repair [Range: 1]", "Repair", 3, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Rockhead:
	tempUnit = Unit(5, 4, 3, "Rockhead", "RCK", "A defensive mobile unit that can hold choke points and can also act as the main force of an army.", {
		Action("Blast [Range: 3]", "Attack", 3, 3, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Mongoose:
	tempUnit = Unit(4, 6, 2, "Mongoose", "MON", "An artillery unit that stands behind your other units to rain fire on enemy units. Comes equipped with anti-air as well.", {
		Action("Artillery rain [Range: 6]", "Attack", 2, 6, 0)
		}, 0, 0, false, 2, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Pillar:
	tempUnit = Unit(8, 7, 1, "Pillar", "PIL", "A heavy roadblock in the enemy's advance. High endurance, attacks that hit multiple units, it is the perfect defence.", {
		Action("Blast [Range: 2]", "AOE Attack", 4, 2, 2),
		Action("Snipe [Range: 7]", "Attack", 2, 7, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Parashield
	tempUnit = Unit(5, 3, 3, "Parashield", "PAR", "Provides your units with a shield to reduce damage. Not good alone, best used in defensive formations or for assaults.", {
		Action("Pulse Wave", "Surround Attack", 2, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Wasp
	tempUnit = Unit(6, 4, 3, "Wasp", "WAS", "A fighter plane capable of chasing down other air units and dealing with them swiftly and effectively.", {
		Action("Front Guns [Range: 4]", "Direct Air Attack", 4, 4, 0)
		}, 0, 0, true, 3, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Eagle
	tempUnit = Unit(5, 3, 3, "Eagle", "EAG", "A bomber plane that flies over revealed targets to drop a payload of bombs across a wide area.", {
		Action("Bomb rain", "AOE Air Attack", 3, 2, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Broadsword
	tempUnit = Unit(6, 3, 2, "Broadsword", "BRO", "A flying gunship that provides effective area denial. Most effective in groups.", {
		Action("Rain fire [Range: 3]", "Attack", 4, 3, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Blackbird
	tempUnit = Unit(2, 5, 6, "Blackbird", "BLB", "A feeble flying unit that is mainly used for scouting out the enemy base or to provide a short-lived distraction. Is completely unarmed.", {}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Fatboy
	tempUnit = Unit(35, 6, 2, "Fatboy", "FAT", "A massive land unit who's bulk makes it a tough challenge to pass. It has effective weaponry at most ranges and heals nearby units using mounted factory modules. The best defence as well as the backbone of an offensive push.", {
		Action("Quad-cannon [Range: 6]", "Attack", 4, 6, 0),
		Action("Pulse cannon [Range: 4]", "AOE Attack", 5, 4, 3),
		Action("Pulse wave", "Surround Attack", 5, 0, 0),
		}, 2, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// King Kriptor
	tempUnit = Unit(50, 5, 2, "King Kriptor", "KIN", "A gigantic titan-like unit with weapons capable of shredding any assault. Can prove difficult to deal with when put on the offensive. The UEF's most powerful weapon.", {
		Action("Blast cannon [Range: 5]", "AOE Attack", 7, 5, 5),
		}, 0, 10, false, 5, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Star King
	tempUnit = Unit(25, 5, 2, "Star King", "STA", "A gigantic flying unit that doubles as a mobile factory, capable of summoning land and air units wherever it is.", {
		Action("Build [1 range]", "Build", 0, 0, 0),
		Action("Bombardment [3 range]", "AOE Attack", 4, 3, 1)
		}, 0, 5, true, 2, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Aurora
	tempUnit = Unit(4, 4, 3, "Aurora", "AUR", "A weak infantry unit that can make the front lines of an early offense or defence. Ineffective against bases or experimentals.", {
		Action("Blast [3 range]", "Attack", 2, 4, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Serenity
	tempUnit = Unit(5, 4, 1, "Serenity", "SER", "A heavy yet slow movement that deals heavy damage to nearby units. Has the ability to teleport, allowing it to move faster.", {
		Action("Pulse Wave", "Surround Attack", 4, 0, 0),
		Action("Teleport", "Boost", 0, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Evensong
	tempUnit = Unit(9, 3, 2, "Evensong", "EVN", "A weak supporting unit that can deal a bit of damage as well as heal nearby allies. Great for defence as well as short offensive strikes.", {
		Action("Blast [Range: 3]", "Attack", 2, 3, 0)
		}, 1, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Sprint
	tempUnit = Unit(2, 5, 6, "Sprint", "SPR", "A fast scouting unit that can mark enemy units for death, making all allies deal more damage to that enemy.", {
		Action("Mark For Death", "Mark", 5, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Weedoboth
	tempUnit = Unit(5, 4, 4, "Weedoboth", "WEE", "A combination between a fighter plane and a bombing plane. Makes the backbone of the Aeon's air force.", {
		Action("Front Guns [Range: 4]", "Direct Air Attack", 3, 4, 0),
		Action("Bombing Raid", "Air Attack", 3, 0, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// HeeHola
	tempUnit = Unit(10, 3, 2, "HeeHola", "HEE", "A flying repair unit that can act as both a defensive blocker as well as a mobile repair station.", {
		Action("Repair", "Repair", 3, 0, 0)
		}, 0 ,0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Vulthoo
	tempUnit = Unit(4, 4, 4, "Vulthoo", "VUL", "A fast gunship that can provide quick support to a land raid. Mostly effective against unprepared land forces.", {
		Action("Rain Fire [Range: 4]", "Attack", 3, 4, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Mercy
	tempUnit = Unit(2, 3, 4, "Mercy", "MER", "A flying protector that provides all nearby units with a shield, reducing the amount of damage they take from the enemy units.", {
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Urchinow
	tempUnit = Unit(30, 5, 2, "Urchinow", "URC", "A power and relatively cheap land experimental that can easily be rushed to provide an extra amount of power to a land attack.", {
		Action("Pulse Laser [Range: 3]", "AOE Attack", 4, 3, 2),
		Action("Ranged Strike [Range: 5]", "Attack", 3, 5, 0),
		Action("Air Defence [Range: 4]", "Direct Air Attack", 3, 4, 0)
		}, 0, 5, false, 3, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Universal Collossus
	tempUnit = Unit(70, 5, 1, "Universal Colossus", "UNC", "A slow, powerful experimental that can wreck havoc on an army. Can easily rush an entire army or base alone, and is even more powerful when paired with other units or experimentals.", {
		Action("Judgement Beam [Range: 5]", "Attack",7, 5, 0),
		Action("Titan Slam", "Surround Attack", 5, 0, 0)
		}, 0, 10, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// CZAR
	tempUnit = Unit(35, 7, 1, "CZAR", "CZA", "A flying UFO-like unit that can easily tear any base or experimental to shread. It is relatively fragile however, so protect it with your other air units.", {
		Action("Judgement Beam [Range: 1]", "Attack", 15, 1, 0),
		Action("Tracking Lasers [Range: 7]", "Attack", 4, 7, 0)
		}, 0, 15, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Loyalist
	tempUnit = Unit(3, 4, 4, "Loyalist", "LOY", "A fast but weak infantry unit that makes the main portion of a cybran land force. Capable of launching hit-and-run attacks as well.", {
		Action("Lasers [Range: 4]", "Attack", 2, 4, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Cobra
	tempUnit = Unit(5, 5, 3, "Cobra", "COB", "A missle launcher that rains several weak missiles among a crowd of units. Useful in the back of an army where they can pester the enemy army.", {
		Action("Air Wave [Range: 5]", "AOE Attack", 2, 5, 1)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Adaptor
	tempUnit = Unit(4, 6, 3, "Adaptor", "ADP", "A near-defenceless unit that provides a shield to nearby units, heals nearby units, and has automated anti-air.", {
		Action("Homing Missiles", "Direct Air Attack", 1, 6, 0),
		Action("Repair", "Repair", 2, 0, 0)
		}, 0, 0, false, 1, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Revenant
	tempUnit = Unit(1, 4, 6, "Revenant", "REV", "A fast unit that can detonate whenever needed, killing itself along with dealing immense damage to any nearby enemies.", {
		Action("Detonation", "Detonate", 5, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Gemeni
	tempUnit = Unit(3, 4, 5, "Gemeni", "GEM", "A combination between a fighter plane and a bombing plane. Fast, but weak against the other faction's units.", {
		Action("Front Guns [Range: 4]", "Direct Air Attack", 4, 4, 0),
		Action("Bombing Raid", "Air Attack", 2, 0, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Prowler
	tempUnit = Unit(7, 4, 3, "Prowler", "PRW", "A high-armoured interceptor unit that deals with air units and provides support to land units by marking enemies for death.", {
		Action("Front Guns [Range: 4]", "Direct Air Attack", 3, 4, 0),
		Action("Track", "Mark", 0, 0, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Renegade
	tempUnit = Unit(6, 3, 2, "Renegade", "REN", "A heavy gunship that can easily shread an unprepared army when used. Most effective in groups of four or five.", {
		Action("Rain Fire [Range: 3]", "Attack", 4, 3, 0)
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Intellitron
	tempUnit = Unit(1, 6, 7, "Intellitron", "INT", "An incredibly fast but weak unit that has no attacks. Mainly used for reconnisance, distractions, or for scouting.", {
		}, 0, 0, true, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Megalith
	tempUnit = Unit(35, 5, 2, "Megalith", "MEG", "A weak experimental that can tear enemies to shreads when backed up by an army. It's relative cheap cost makes it easy to rush out early.", {
		Action("Pulse Cannon [Range: 5]", "AOE Attack", 4, 5, 3)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Monkey Lord
	tempUnit = Unit(60, 5, 2, "Monkey Lord", "MON", "A spider-like experimental that can fire a massive laser that obliterates enemies and is most effective against other experimentals. It can also create other land units to aid it.", {
		Action("Direct Laser [Range: 5]", "Attack", 6, 5, 0),
		Action("Creation", "Build", 0, 0, 0),
		Action("Leg Slam", "Surround Attack", 5, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Soul Ripper
	tempUnit = Unit(40, 5, 2, "Soul Ripper", "RIP", "A massive flying gunship that can absolutely shread any base rapidly or perform targetted damage to a single strong unit. A terror of the skies, but easily countered with air units.", {
		Action("Laser Rain [Range: 5]", "AOE Attack", 5, 5, 3)
		}, 0, 0, true, 3, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Thaam
	tempUnit = Unit(4, 3, 3, "Thaam", "THA", "A mediocre infantry unit that can teleport to move further in one turn. Equipped with a weak cannon for defence and offence.", {
		Action("Pulse Cannon [Range: 3]", "Attack", 2, 3, 0),
		Action("Teleport", "Boost", 0, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Usha-Ah
	tempUnit = Unit(2, 6, 2, "Usha-Ah", "USH", "A sniper unit that acts best in defensive positions or while aiming down corridors. Can mark enemies for death to increase its allies' effectiveness.", {
		Action("Snipe [Range: 6]", "Attack", 1, 6, 0),
		Action("Mark", "Mark", 0, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Othuum
	tempUnit = Unit(10, 4, 1, "Othuum", "OTH", "A powerful tank unit that mainly acts as a defensive wall against incoming enemies. Can overdrive itself to temporarily boost its damage.", {
		Action("Pulse Cannon [Range: 4]", "Attack", 4, 4, 0),
		Action("Black Hole Laser [Range: 4]", "Direct Air Attack", 2, 4, 0),
		Action("Overdrive", "Overdrive", 0, 0, 0)
		}, 0, 0, false, 2, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Suthanus
	tempUnit = Unit(4, 4, 3, "Suthanus", "SUT", "A missile launcher that is most effective behind its allies as it both fires a rain of missiles across enemies as well as providing shields for its allies.", {
		Action("Artillary Cannon [Range: 4]", "AOE Attack", 2, 4, 1),
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Iaselem
	tempUnit = Unit(6, 4, 2, "Iaselem", "IAS", "A slow but powerful interceptor that is capable of easily dealing with enemy air threats.", {
		Action("Front Guns [Range: 4]", "Direct Air Attack", 3, 4, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Notha
	tempUnit = Unit(4, 3, 5, "Notha", "NOT", "A plasma bomber that drops AOE bombs across areas, dealing high damage to multiple enemies. Most effective against bases.", {
		Action("Bombing Raid", "AOE Air Attack", 4, 2, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Sinnve
	tempUnit = Unit(5, 3, 4, "Sinnve", "SIN", "A cross between a gunship and an interceptor. Can both handle itself against air units and can deal damage to ground units with directed weapons. Most effective when paired with land units.", {
		Action("Front Guns [Range: 3]", "Direct Air Attack", 2, 3, 0),
		Action("Rain Fire [Range: 3]", "Attack", 3, 3, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Vish
	tempUnit = Unit(6, 3, 1, "Vish", "VIS", "A strong but slow flying factory that can produce other Seraphim air units to fight for you. Has no other weapons to protect itself with.", {
		Action("Build", "Build", 0, 0, 0),
		Action("Crash", "Detonate", 5, 0, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Iya
	tempUnit = Unit(25, 5, 2, "Iya", "IYA", "A defensive land experimental that provides nearby allies with a shield and consistant healing. It also can provide area denial through pulse wave attacks.", {
		Action("Pulse Wave", "Surround Attack", 5, 0, 0)
		}, 3, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Ythotha
	tempUnit = Unit(70, 6, 1, "Ythotha", "YTH", "A powerful land experimental with a wide variety of land-based attacks for both dealing with groups of units close-by or for dealing with far away units. Drops a massive field of energy when killed, severly harming nearby enemies.", {
		Action("Black Hole Bomb [Range: 2]", "AOE Attack", 6, 2, 5),
		Action("Laser Rain [Range: 6]", "Attack", 3, 6, 0)
		}, 0, 15, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);

	// Ahwassa
	tempUnit = Unit(25, 3, 3, "Ahwassa", "AHW", "An experimental bomber plane that is loaded with charged plasma bombs that can easily wipe out any group of enemy units in an instant. Most effective against bases.", {
		Action("Tactical Nuke", "AOE Air Attack", 10, 6, 0)
		}, 0, 0, false, 0, 0, 0, 0, 0);
	units.push_back(tempUnit);
 }

Unit retrieveUnit(int unitID) {
	if (unitID + 1 > units.size()) {
		return Unit(0, 0, 0, "", "", "", {}, 0, 0, false, 0, 0, 0, 0, 0);
	}
	else {
		return units[unitID];
	}
}