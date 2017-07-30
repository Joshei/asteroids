#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "windows.h"


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

int asteroid::setInitialAsteroid(int fromThisBorder) {

	//technically these asteroids are behind the border by their width or height but they've been
	//set to onscreen so they are ready to be checked for collisions now.
	setActivate(onscreen);
	
	//whichDirection key of values no clockwise changed : 8:52 PM 6/18/17

	
	//starting behind top border	   :  0
	//0.  asteroid moves down and right
	//1.  asteroid moves down
	//2.  asteroid moves down and left
	//starting behind right border     :  1
	//3.  asteroid moves left and down
	//4.  asteroid moves left
	//5.  asteroid moves left and up
	//starting behind bottom border     : 2
	//6.  asteroid moves up and left 
	//7.  asteroid moves up
	//8.  asteroid moves up and right
	//starting behind left border      :  3
	//9.  asteroid moves up and right
	//10.  asteroid moves right
	//11.  asteroid moves down and right



	//seed called in fillAsteroidVector
	int i = 0;
	
	
	////////////////////////

	//from top border
	if (fromThisBorder == 0)
	{


		x = (rand() % (gScreenWidth + width));
		whichDirection = std::rand() % 3;

		y = 0 - height;

		//asteroid moves form top border to right-down
		if (whichDirection == 0)
		{
			deltaY = 1;
			deltaX = 1;
		}
		//asteroid moves from top border to down
		if (whichDirection == 1)
		{
			deltaY = 1;
			deltaX = 0;
		}
		//asteroid moves from top border to left-down
		if (whichDirection == 2)
		{
			deltaY = 1;
			deltaX = -1;
		}


		anAsteroid.setPosition(sf::Vector2f(x, y));
	}


//////////////

//from right border
	else if (fromThisBorder == 1)
	{

		x = gScreenWidth;

		y = (rand() % (gScreenHeight - height));
		whichDirection = std::rand() % 3 + 3;

		//asteroid moves from right border to left-down
		if (whichDirection == 3)
		{
			deltaY = 1;
			deltaX = -1;
		}
		//asteroid moves from right border to left
		if (whichDirection == 4)
		{
			deltaY = 0;
			deltaX = -1;
		}
		//asteroid moves from right border to left-up
		if (whichDirection == 5)
		{
			deltaY = -1;
			deltaX = -1;
		}


		anAsteroid.setPosition(sf::Vector2f(x, y));
	}



////////////


//from bottom border
	else if (fromThisBorder == 2)
	{
		x = (rand() % (gScreenWidth + width));
		whichDirection = std::rand() % 3 + 6;

		y = gScreenHeight;

		//asteroid moves from bottom border to left-up
		if (whichDirection == 6)
		{
			deltaY = -1;
			deltaX = -1;
		}
		//asteroid moves from bottom border to up
		if (whichDirection == 7)
		{
			deltaY = -1;
			deltaX = 0;
		}
		//asteroid moves form bottom border to right-up
		if (whichDirection == 8)
		{
			deltaY = -1;
			deltaX = 1;
		}


		//sets the image at the coordin
		anAsteroid.setPosition(sf::Vector2f(x, y));
	}


////////////

	//from left border
	else if (fromThisBorder == 3) 
	{

		

		//makes image just off the screen.
		x = 0 - width;

		
		y = std::rand() % (gScreenHeight - height);
		whichDirection = std::rand() % 3 + 9;
		
		//asteroid moves from left border to right-up
		if (whichDirection == 9)
		{
			deltaY = -1;
			deltaX = 1;
		}
		//asteroid moves from left border to right
		if (whichDirection == 10)
		{
			deltaY = 0;
			deltaX = 1;
		}
		//asteroid moves form left border tp right-down
		if (whichDirection == 11)
		{
			deltaY = 1;
			deltaX = 1;
		}

		
		
		anAsteroid.setPosition(sf::Vector2f(x, y));

	}

	

	
	

	return(1);
}

//takes an enumeration of stateofassteroid
void asteroid::setActivate(int activateFlag) 
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



