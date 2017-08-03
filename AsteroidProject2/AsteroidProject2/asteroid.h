#ifndef ASTEROID_H
#define ASTEROID_H



#include "moveable.h"

//these are the "states" of the asteroids created with the asteroid class
enum stateOfAsteroid { instantiated, destroyed, initialized, onscreen, offscreen };

enum class AsteroidMovement
{
	UP,
	UP_LEFT,
	UP_RIGHT,
	DOWN,
	DOWN_LEFT,
	DOWN_RIGHT,
	LEFT,
	RIGHT

};

static const AsteroidMovement directions[4][3] =
{
	{ AsteroidMovement::DOWN,AsteroidMovement::DOWN_LEFT,AsteroidMovement::DOWN_RIGHT },
	{ AsteroidMovement::UP_RIGHT,AsteroidMovement::DOWN_RIGHT,AsteroidMovement::RIGHT },
	{ AsteroidMovement::UP, AsteroidMovement::UP_LEFT, AsteroidMovement::UP_RIGHT },
	{ AsteroidMovement::UP_LEFT, AsteroidMovement::DOWN_LEFT, AsteroidMovement::LEFT }
};

const int gScreenWidth = 1000;
const int gScreenHeight = 700;


class asteroid : public moveableObject 
{


public:

	//sfml object passed a texture uses a pointer
	sf::Sprite anAsteroid;

	
	asteroid( int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid);
	
	int moveAsteroid(void);
	void setActivate(stateOfAsteroid activateFlag);
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

	
	bool setInitialAsteroid(int i);


protected:

	

	int whichDirection;

	stateOfAsteroid activated;
	
	int fromThisBorder;

	


};

#endif   /*  ASTEROID_H  */