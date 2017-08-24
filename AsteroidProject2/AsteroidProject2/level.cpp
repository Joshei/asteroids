#include "windows.h"
#include "level.h"


int levelObj::maxBullets = 10;

levelObj::levelObj()
{
	levelnumber = 0;
	numoflargeasteroids = 0;
	numofsmallasteroids = 0;
}


void levelObj::AdvanceLevelByOne()
{
	levelnumber++;

	switch (levelnumber) {

	case 1:
		numoflargeasteroids = 3;
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
	
		exit(-1);
		break;
	default:
		exit(-1);
		break;

	}

}

