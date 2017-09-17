#include <SFML/Graphics.hpp>
#include "asteroid.h"
#include "windows.h"
#include <assert.h>






Asteroid::Asteroid(int thewidth, int theheight, sf::Texture & Textureforasteroid, asteroidType Theasteroidtype)
{
	//hasn't been initialized yet.. happens upon creation with createsmall...
	activated = instantiated;
	height = theheight;
	width = thewidth;
	Anasteroid.setTexture(Textureforasteroid);
	//initialized, no -1 available, so set to down.  Smaller asteroids won't use this setting.
	Whichdirection = asteroidMovement::DOWN;
	
	//which border asteroid starts behind, remember small asteroids start on the screen after
	//a destroyed large asteroid
	fromthisborder = -1;
	
	Type = Theasteroidtype;

	
}

void Asteroid::MoveAsteroid()
{

	//sets asteroid for new move, but drawing takes place in main loop.
	
	Vectorposition.x = Vectorposition.x + deltax;
	Vectorposition.y = Vectorposition.y + deltay;
	Vectorprevposition.x = Vectorposition.x;
	Vectorprevposition.y = Vectorposition.y;


}

//creates a large or small asteroid that is at one of the four sides of the screens
//at a random position and a random (one of 12) direction.  The asteroid's
//x and y have been set so that the image is against the border to its top, bottom, 
//left, or right.
//The astroid is set to onscreen so that it can be drawn and moved.
//The function is used by all asteroids, but it is important to remember
//that a small asteroid is created when a large asteroid is destroyed and 
//appears on the screen than as an onscreen activation but it will use 
//this function when the asteroid goes off screen and it's activation is
//set to offscreen.
void Asteroid::SetInitialAsteroid(int fromthisborder) {

	
	
	//set to onscreen so they are ready to be checked for collisions now.
	SetActivate(onscreen);
	//uses enum class object declared in asteroid.h (on top of header file)
	Whichdirection = directions[fromthisborder][std::rand() % 3];
	//sets the deltax and deltay (change in x, change in y) from this random direction
	SetDeltaWithDirection(Whichdirection);
	
	
	//sets the initial x and y for each asteroid according to what border the image is behind
	
	
	
	//from top border
	if (fromthisborder == 0)
	{
		
		

		Vectorposition.x = rand() % G_SCREEN_WIDTH;
		

		//if x position greater than width away form screen width than just set it to width 
		//away from screen width, so there will be no partial displays of asteroid.  no partial displey.

		if (Vectorposition.x > G_SCREEN_WIDTH - width)
		{
			Vectorposition.x = G_SCREEN_WIDTH - width;
		}

		//no partial display
		Vectorposition.y = 0;


		//for interpolation main loop
		Vectorprevposition.y = Vectorposition.y;
		Vectorprevposition.x = Vectorposition.x;
		


	}
	//from right border
	else if (fromthisborder == 1)
	{
		//flush against border, no partial display
		Vectorposition.x = G_SCREEN_WIDTH - width;
		
		
		
		//if asteroid is passed it's heigt on bottom of screen than its just set 
		//to one height away.
		Vectorposition.y = rand() % G_SCREEN_HEIGHT;
		if (Vectorposition.y > (G_SCREEN_HEIGHT - height))
		{
			Vectorposition.y = G_SCREEN_HEIGHT - height;
		}

		//for interpolation main loop
		Vectorprevposition.y = Vectorposition.y;
		Vectorprevposition.x = Vectorposition.x;


	}
	//from bottom border
	else if (fromthisborder == 2)
	{
		
		Vectorposition.x = rand() % G_SCREEN_WIDTH;
		
		
		//if x position is less than one width away than just set the asteroid
		//to one width away (no partial display)
		if (Vectorposition.x > G_SCREEN_WIDTH - width )
		{
			Vectorposition.x = G_SCREEN_WIDTH - width;
		}
		
		//no partial display
		Vectorposition.y = G_SCREEN_HEIGHT - height;

		//set for interplation.
		Vectorprevposition.y = Vectorposition.y;
		Vectorprevposition.x = Vectorposition.x;



	}
	//from left border
	else if (fromthisborder == 3) 
	{
		//against left border (not partial display)
		Vectorposition.x = 0;
		
		//if y value is less than height away from border than just put it one height away from the 
		//bottom
		Vectorposition.y = std::rand() % G_SCREEN_HEIGHT;
		if (Vectorposition.y > (G_SCREEN_HEIGHT - height))
		{
			Vectorposition.y = G_SCREEN_HEIGHT - height;
		}


		//for interpolation
		Vectorprevposition.y = Vectorposition.y;
		Vectorprevposition.x = Vectorposition.x;

	}

	
	
}

//takes an enumeration of stateofasteroid
void Asteroid::SetActivate(int activateflag) 
{

	activated = activateflag;

}


void Asteroid::SetWhichDirection(asteroidMovement direction)
{
	
	Whichdirection = direction;

}

//Set to large or small
void Asteroid::SetType(asteroidType theType)
{
	Type = theType;

}

void::Asteroid::SetTexture(sf::Texture & Texture)
{
	Anasteroid.setTexture(Texture);
}



//called twice, first higher than lower
void Asteroid::SetDeltaWithDirection(asteroidMovement & thedirection)
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
		deltax = -3;
		break;
	case asteroidMovement::RIGHT:
	case asteroidMovement::UP_RIGHT:
	case asteroidMovement::DOWN_RIGHT:
		deltax = 3;
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
		deltay = -3;
		break;
	case asteroidMovement::DOWN:
	case asteroidMovement::DOWN_LEFT:
	case asteroidMovement::DOWN_RIGHT:
		deltay = 3;
		break;
		
	default:
		exit(-2);

		break;

	}

}


