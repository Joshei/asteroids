#ifndef ASTEROID_H
#define ASTEROID_H



#include "moveable.h"

//these are the "states" of the asteroids created with the asteroid class
enum stateofasteroid { instantiated, destroyed, initialized, onscreen, offscreen };
enum asteroidType {smaller, larger};

const int gScreenWidth = 1000;
const int gScreenHeight = 700;


class asteroid : public moveableObject 
{


public:

	//sfml object passed a texture uses a pointer
	sf::Sprite anAsteroid;

	
	asteroid( int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid, asteroidType type);
	
	int moveAsteroid(void);
	void setActivate(int activateFlag);
	void setWhichDirection(int direction);
	
	
	//inlines
	int getActivate(void)
	{ 
		return activated; 
	}

	

	int getFromThisBorder(void)
	{ 
		return(fromThisBorder); 
	}

	int getWhichDirection(void)
	{
		return(whichDirection);

	}

	int getAsteroidType(void)
	{
		return(type);
	}

	
	int setInitialAsteroid(int i);


protected:

	

	int whichDirection;

	int activated;
	
	int fromThisBorder;

	int type;


};

#endif   /*  ASTEROID_H  */