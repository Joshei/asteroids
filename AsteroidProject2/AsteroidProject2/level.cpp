#include "windows.h"
#include "level.h"


int levelObj::maxBullets = 10;

levelObj::levelObj()
{
	levelNumber = 0;
	numOfLargeAsteroids = 0;
	numOfSmallAsteroids = 0;
}


void levelObj::advanceLevelByOne()
{
	levelNumber++;

	switch (levelNumber) {

	case 1:
		numOfLargeAsteroids = 3;
		numOfSmallAsteroids = numOfLargeAsteroids * 2;
		
		break;
	case 2:
		numOfLargeAsteroids = 2;
		numOfSmallAsteroids = numOfLargeAsteroids * 2;
		
		break;
	case 3:
		numOfLargeAsteroids = 3;
		numOfSmallAsteroids = numOfLargeAsteroids * 2;
		
		break;
	case 4:
		numOfLargeAsteroids = 4;
		numOfSmallAsteroids = numOfLargeAsteroids * 2;
		
		break;
	case 5:
	
		exit(-1);
		break;
	default:
		exit(-1);
		break;

	}

}

