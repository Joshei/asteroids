#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "windows.h"
#include <assert.h>






asteroid::asteroid(int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid, asteroidType theAsteroidType)
{

	activated = instantiated;
	height = theHeight;
	width = theWidth;
	anAsteroid.setTexture(largerTextureForAsteroid);
	//initialized, no -1 available, so set to down.  Smaller asteroids won't use this setting.
	whichDirection = asteroidMovement::DOWN;
	fromThisBorder = -1;
	type = theAsteroidType;
}

//creates a large or small asteroid that is at one of the four sides of the screens
//at a random position and a random (one of 12) direction.  The asteroid's
//x and y have been set so that the image is just off the screen (next pixel)
//The astroid is set to onscreen so that it can be drawn and moved.
//The function is used by all asteroids, but it is important to remember
//that a small asteroid is created when a large asteroid is destroyed and 
//appears on the screen than as an onscreen activation but it will use 
//this function when the asteroid goes off screen and it's activation is
//set to offscreen.
int asteroid::setInitialAsteroid(int fromThisBorder) {
	//technically these asteroids are behind the border by their width or height but they've been
	//set to onscreen so they are ready to be checked for collisions now.
	setActivate(onscreen);
	//uses enum class object declared in asteroid.h (on top of header file)
	whichDirection = directions[fromThisBorder][std::rand() % 3];
	//sets the deltax and deltay from this random direction
	setDeltaWithDirection(whichDirection);
	
	
	//sets the initial x and y for each asteroid according to what border the image is behind
	
	//from top border
	if (fromThisBorder == 0)
	{
		x = (rand() % (G_SCREEN_WIDTH + width));
		y = 0 - height;
	}
	//from right border
	else if (fromThisBorder == 1)
	{
		x = G_SCREEN_WIDTH;
		y = (rand() % (G_SCREEN_HEIGHT - height));
	}
	//from bottom border
	else if (fromThisBorder == 2)
	{
		x = (rand() % (G_SCREEN_WIDTH + width));
		y = G_SCREEN_HEIGHT;
	}
	//from left border
	else if (fromThisBorder == 3) 
	{
		//makes image just off the screen.
		x = 0 - width;
		y = std::rand() % (G_SCREEN_HEIGHT - height);
	}
	//sets the image at the coordinates
	anAsteroid.setPosition(sf::Vector2f(x, y));
	return(1);
}

//takes an enumeration of stateofassteroid
void asteroid::setActivate(int activateFlag) 
{

	activated = activateFlag;

}


void asteroid::setWhichDirection(asteroidMovement direction)
{
	
	whichDirection = direction;

}

int asteroid::moveAsteroid(void) 
{

	
	anAsteroid.move(sf::Vector2f(deltaX, deltaY));
	x = x + deltaX;
	y = y + deltaY;
	

	return(1);
}


void asteroid::setDeltaWithDirection(asteroidMovement & theDirection)
{

	//sets the change in x and the change in y (delta) for computing movement.  Of course x is horizonatl andh y
	//is vertical.
	switch (theDirection) {

	case asteroidMovement::UP:
	case asteroidMovement::DOWN:
		deltaX = 0;
		break;
	case asteroidMovement::LEFT:
	case asteroidMovement::UP_LEFT:
	case asteroidMovement::DOWN_LEFT:
		deltaX = -1;
		break;
	case asteroidMovement::RIGHT:
	case asteroidMovement::UP_RIGHT:
	case asteroidMovement::DOWN_RIGHT:
		deltaX = 1;
		break;
	default:
		break;
	}

	switch (whichDirection) {

	case asteroidMovement::LEFT:
	case asteroidMovement::RIGHT:
		deltaY = 0;
		break;
	case asteroidMovement::UP:
	case asteroidMovement::UP_LEFT:
	case asteroidMovement::UP_RIGHT:
		deltaY = -1;
		break;
	case asteroidMovement::DOWN:
	case asteroidMovement::DOWN_LEFT:
	case asteroidMovement::DOWN_RIGHT:
		deltaY = 1;
		break;
	default:
		break;

	}

}


void asteroid::setType(asteroidType theType)
{
	type = theType;

}

void::asteroid::setTexture(sf::Texture & texture)
{
	anAsteroid.setTexture(texture);
}