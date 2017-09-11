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

	

	
	asteroid( int thewidth, int theheight, sf::Texture & Largertextureforasteroid, asteroidType Type);
	
	void MoveAsteroid();
	void SetInitialAsteroid(int i);
	void SetActivate(int activateflag);
	void SetWhichDirection(asteroidMovement Direction);
	void SetType(asteroidType Thetype);
	void SetTexture(sf::Texture & Thetexture);
	void SetDeltaWithDirection(asteroidMovement & Direction);
	
	//inlines
	int GetActivate(){return activated;}

	int GetFromThisBorder(){return fromthisborder;}

	asteroidMovement GetWhichDirection(){return Whichdirection;}

	asteroidType GetAsteroidType(){return Type;}

	sf::Sprite &  GetSprite(){return Anasteroid;}
	
	
private:

	//sfml object passed a texture uses a pointer
	sf::Sprite Anasteroid;

	asteroidMovement Whichdirection;

	int activated;
	
	int fromthisborder;

	asteroidType Type;


};

#endif   /*  ASTEROID_H  */