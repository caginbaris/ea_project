#include "menu_definitions.h"












void (*menu_functions[])(struct push_buttons pb)={

	voltagesPhase2Neutral,
	voltagesPhase2Phase,
	currents,
	
	apparentPower,
	activePower,
	reactivePower,
	totalPower,
	
	apparentEnergy,
	activeEnergy,
	reactiveEnergy,
	
};
