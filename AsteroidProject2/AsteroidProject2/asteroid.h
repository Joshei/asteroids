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
	//top, right bottom left
	{ asteroidMovement::DOWN, asteroidMovement::DOWN_LEFT, asteroidMovement::DOWN_RIGHT },
	{ asteroidMovement::UP_LEFT, asteroidMovement::DOWN_LEFT, asteroidMovement::LEFT },
	{ asteroidMovement::UP, asteroidMovement::UP_LEFT, asteroidMovement::UP_RIGHT },
	{ asteroidMovement::UP_RIGHT, asteroidMovement::DOWN_RIGHT, asteroidMovement::RIGHT}

};




const int G_SCREEN_WIDTH = 1000;
const int G_SCREEN_HEIGHT = 700;


class asteroid : public moveableObject 
{


public:

	

	
	asteroid( int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid, asteroidType type);
	
	void MoveAsteroid();
	void SetInitialAsteroid(int i);
	void SetActivate(int activateFlag);
	void SetWhichDirection(asteroidMovement direction);
	void SetType(asteroidType thetype);
	void SetTexture(sf::Texture & theTexture);
	void SetDeltaWithDirection(asteroidMovement & direction);
	
	//inlines
	int GetActivate(){return activated;}

	int GetFromThisBorder(){return fromThisborder;}

	asteroidMovement GetWhichDirection(){return whichDirection;}

	asteroidType GetAsteroidType(){return type;}

	sf::Sprite &  GetSprite(){return anAsteroid;}
	
	
private:

	//sfml object passed a texture uses a pointer
	sf::Sprite anAsteroid;

	asteroidMovement whichDirection;

	int activated;
	
	int fromThisborder;

	asteroidType type;


};

#endif   /*  ASTEROID_H  */