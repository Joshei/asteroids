#include "windows.h"
#include "level.h"


int LevelObj::Maxbullets = 10;

LevelObj::LevelObj()
{
	levelnumber = 0;
	numoflargeasteroids = 0;
	numofsmallasteroids = 0;
}


//controls the level's new large and small amount of asteroids.
void LevelObj::AdvanceLevelByOne()
{

	
	levelnumber++;

	switch (levelnumber) {

	case 1:
		numoflargeasteroids = 1;
		numofsmallasteroids = numoflargeasteroids * 2;
		
		break;
	case 2:
		numoflargeasteroids = 2;
		numofsmallasteroids = numoflargeasteroids * 2;
		
		break;
	case 3:
		numoflargeasteroids = 3;
		numofsmallasteroids = numoflargeasteroids * 2;
		
		break;
	case 4:
		numoflargeasteroids = 4;
		numofsmallasteroids = numoflargeasteroids * 2;
		
		break;
	case 5:
	
		exit(-3);
		break;
	default:
		exit(-4);
		break;

	}

}

