#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "windows.h"
#include <assert.h>






asteroid::asteroid(int theWidth, int theHeight, sf::Texture & largerTextureForAsteroid, asteroidType theasteroidtype)
{

	activated = instantiated;
	height = theHeight;
	width = theWidth;
	anAsteroid.setTexture(largerTextureForAsteroid);
	//initialized, no -1 available, so set to down.  Smaller asteroids won't use this setting.
	whichDirection = asteroidMovement::DOWN;
	fromThisborder = -1;
	type = theasteroidtype;
}

void asteroid::MoveAsteroid()
{


	//anAsteroid.move(sf::Vector2f(deltax, deltay));
	x = x + deltax;
	y = y + deltay;



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
void asteroid::SetInitialAsteroid(int fromthisborder) {

	
	//technically these asteroids are behind the border by their width or height but they've been
	//set to onscreen so they are ready to be checked for collisions now.
	SetActivate(onscreen);
	//uses enum class object declared in asteroid.h (on top of header file)
	whichDirection = directions[fromthisborder][std::rand() % 3];
	//sets the deltax and deltay from this random direction
	SetDeltaWithDirection(whichDirection);
	
	
	//sets the initial x and y for each asteroid according to what border the image is behind
	
	//the initial placement for x and y is totally off the screen.  that means for left and top
	//there must be subtraction of width of heigh from zero on the screen rectangle
	//from top border
	if (fromthisborder == 0)
	{
		
		//if x is the maximum amount plus one than object starts behind the edge by its width
		x = rand() % G_SCREEN_WIDTH;
		
		if (x > G_SCREEN_WIDTH - width)
		{
			x = G_SCREEN_WIDTH - width;
		}


		y = 0;
	}
	//from right border
	else if (fromthisborder == 1)
	{
		x = G_SCREEN_WIDTH - width;
		//if y is the maximum amount plus one start the object one height behind the top
		y = rand() % G_SCREEN_HEIGHT;
		if (y > (G_SCREEN_HEIGHT - height))
		{
			y = G_SCREEN_HEIGHT - height;
		}

	}
	//from bottom border
	else if (fromthisborder == 2)
	{
		//if x is the maximum amount plus one than object starts behind the edge by its width
		x = rand() % G_SCREEN_WIDTH;
		if (x > G_SCREEN_WIDTH - width )
		{
			x = G_SCREEN_WIDTH - width;
		}
		

		y = G_SCREEN_HEIGHT - height;
	}
	//from left border
	else if (fromthisborder == 3) 
	{
		//makes image just off the screen.
		x = 0;
		//if y is the maximum amount plus one start the object one height behind the top
		y = std::rand() % G_SCREEN_HEIGHT;
		if (y > (G_SCREEN_HEIGHT - height))
		{
			y = G_SCREEN_HEIGHT - height;
		}


	}
	//sets the image at the coordinates
	anAsteroid.setPosition(sf::Vector2f(x, y));
	
}

//takes an enumeration of stateofassteroid
void asteroid::SetActivate(int activateflag) 
{

	activated = activateflag;

}


void asteroid::SetWhichDirection(asteroidMovement direction)
{
	
	whichDirection = direction;

}

void asteroid::SetType(asteroidType theType)
{
	type = theType;

}

void::asteroid::SetTexture(sf::Texture & texture)
{
	anAsteroid.setTexture(texture);
}



//called twice, first higher than lower
void asteroid::SetDeltaWithDirection(asteroidMovement & thedirection)
{

	//sets the change in x and the change in y (delta) for computing movement.  Of course x is horizonatl andh y
	//is vertical.

	//upper 
	switch (thedirection) {

	case asteroidMovement::UP:
	case asteroidMovement::DOWN:
		deltax = 0;
		break;
	case asteroidMovement::LEFT:
	case asteroidMovement::UP_LEFT:
	case asteroidMovement::DOWN_LEFT:
		deltax = -1;
		break;
	case asteroidMovement::RIGHT:
	case asteroidMovement::UP_RIGHT:
	case asteroidMovement::DOWN_RIGHT:
		deltax = 1;
		break;
	default:
		exit(-1);
		break;
	}

	switch (thedirection) {

	case asteroidMovement::LEFT:
	case asteroidMovement::RIGHT:
		deltay = 0;
		break;
	case asteroidMovement::UP:
	case asteroidMovement::UP_LEFT:
	case asteroidMovement::UP_RIGHT:
		deltay = -1;
		break;
	case asteroidMovement::DOWN:
	case asteroidMovement::DOWN_LEFT:
	case asteroidMovement::DOWN_RIGHT:
		deltay = 1;
		break;
		
	default:
		exit(-1);

		break;

	}

}


