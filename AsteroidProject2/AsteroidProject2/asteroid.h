#ifndef ASTEROID_H
#define ASTEROID_H



#include "moveable.h"

//these are the "states" of the asteroids created with the asteroid class
enum stateofasteroid { instantiated, destroyed, initialized, onscreen, offscreen };
enum asteroidType {smaller, larger};

enum class asteroidMovement
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

static const asteroidMovement directions[4][3] =
{

	{ asteroidMovement::DOWN, asteroidMovement::DOWN_LEFT, asteroidMovement::DOWN_RIGHT },
	{ asteroidMovement::UP_RIGHT, asteroidMovement::DOWN_RIGHT, asteroidMovement::RIGHT },
	{ asteroidMovement::UP, asteroidMovement::UP_LEFT, asteroidMovement::UP_RIGHT },
	{ asteroidMovement::UP_LEFT, asteroidMovement::DOWN_LEFT, asteroidMovement::LEFT }
};




const int G_SCREEN_WIDTH = 1000;
const int G_SCREEN_HEIGHT = 700;


class asteroid : public moveableObject 
{


public:

	//sfml object passed a texture uses a pointer
	sf::Sprite anAsteroid;

	
	asteroid( int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid, asteroidType type);
	
	void moveAsteroid();
	void setInitialAsteroid(int i);
	void setActivate(int activateFlag);
	void setWhichDirection(asteroidMovement direction);
	void setType(asteroidType theType);
	void setTexture(sf::Texture & theTexture);
	void setDeltaWithDirection(asteroidMovement & Direction);
	
	//inlines
	int getActivate()
	{ 
		return activated; 
	}

	

	int getFromThisBorder()
	{ 
		return(fromThisBorder); 
	}

	asteroidMovement getWhichDirection()
	{
		return(whichDirection);

	}

	asteroidType getAsteroidType()
	{
		return(type);
	}

	
	
private:

	

	asteroidMovement whichDirection;

	int activated;
	
	int fromThisBorder;

	asteroidType type;


};

#endif   /*  ASTEROID_H  */