#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "windows.h"
#include "assert.h"

asteroid::asteroid(int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid)
{

	activated = instantiated;
	height = theHeight;
	width = theWidth;
	anAsteroid.setTexture(largerTextureForAsteroid);
	whichDirection = -1;
	fromThisBorder = -1;
}

//creates an asteroid that is at one of the four sides of the screens
//at a random position and a random (one of 12) direction.  The asteroid's
//x and y have been set so that the image is just off the screen (next pixel)
//The astroid is set to onscreen so that it can be drawn and moved.
//The function is used by all asteroids, but it is important to remember
//that a small asteroid is created when a large asteroid is destroyed and 
//appears on the screen than as an onscreen activation but it will use 
//this function when the asteroid goes off screen and it's activation is
//set to offscreen.

bool asteroid::setInitialAsteroid(int fromThisBorder) {

	//technically these asteroids are behind the border by their width or height but they've been
	//set to onscreen so they are ready to be checked for collisions now.
	setActivate(onscreen);
	
	AsteroidMovement direction = directions[fromThisBorder][std::rand() % 3];
	switch (direction) {

	case AsteroidMovement::UP:
	case AsteroidMovement::DOWN:
		deltaX = 0;
		break;
	case AsteroidMovement::LEFT:
	case AsteroidMovement::UP_LEFT:
	case AsteroidMovement::DOWN_LEFT:
		deltaX = -1;
		break;
	case AsteroidMovement::RIGHT:
	case AsteroidMovement::UP_RIGHT:
	case AsteroidMovement::DOWN_RIGHT:
		deltaX = 1;
		break;
	default:
		assert(false);
	}

	switch (direction) {
	
	case AsteroidMovement::LEFT:
	case AsteroidMovement::RIGHT:
		deltaY = 0;
		break;
	case AsteroidMovement::UP:
	case AsteroidMovement::UP_LEFT:
	case AsteroidMovement::UP_RIGHT:
		deltaY = -1;
		break;
	case AsteroidMovement::DOWN:
	case AsteroidMovement::DOWN_LEFT:
	case AsteroidMovement::DOWN_RIGHT:
		deltaY = 1;
		break;

	default:
	assert(false);
	

		}

	//seed called in fillAsteroidVector
	int i = 0;
	
	////////////////////////

	//from top border
	if (fromThisBorder == 0)
	{
		x = (rand() % (gScreenWidth - width));
		y = 0 - height;
	}


	//////////////

	//from right border
	else if (fromThisBorder == 1)
	{
		x = gScreenWidth;
		y = (rand() % (gScreenHeight - height));
		
	}


	////////////

	//from bottom border
	else if (fromThisBorder == 2)
	{
		x = (rand() % (gScreenWidth - width));
		y = gScreenHeight;

	}


	////////////

	//from left border
	else if (fromThisBorder == 3) 
	{

		//makes image just off the screen.
		x = 0 - width;
		y = std::rand() % (gScreenHeight - height);
		
	}

	anAsteroid.setPosition(sf::Vector2f(x, y));
	return(1);
}

//takes an enumeration of stateofassteroid
void asteroid::setActivate(stateOfAsteroid activateFlag) 
{

	activated = activateFlag;

}

//for createSmallerAsteroids(.. where two small asteroids are created with direction by
//the value of the direction from the larger shot asteroid.
//also could be used for a border-to-border wrapping of asteroids that leave the screen.
//(setActivate using offscreen)
void asteroid::setWhichDirection(int direction)
{
	
	whichDirection = direction;

}

int asteroid::moveAsteroid(void) 
{

	
	anAsteroid.move(sf::Vector2f(deltaX, deltaY));
	x = (x + deltaX);
	y = (y + deltaY);
	

	return(1);
}



