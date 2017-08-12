#include "windows.h"
#include "level.h"


int levelObj::maxBullets = 10;

levelObj::levelObj(void)
{
	levelNumber = 1;
	numOfLargeAsteroids = 1;
	numOfSmallAsteroids = numOfLargeAsteroids * 2;


}
int levelObj::getNumLargeAsteroids()
{

	return(numOfLargeAsteroids);
}

int levelObj::getNumSmallAsteroids()
{

	return(numOfSmallAsteroids);
}


int levelObj::advanceLevelByOne()
{
	levelNumber++;

	switch (levelNumber) {

	case 1:


		numOfLargeAsteroids = 1;
		numOfSmallAsteroids = numOfLargeAsteroids * 2;


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

		//will break out of while loop in main and end program
		//g_Shutdownflag = 1;
		exit(-1);

		break;

	default:

		break;

	}


	return(1);


}

