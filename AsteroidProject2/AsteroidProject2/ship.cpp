#include "ship.h"
#include <SFML/Graphics.hpp>


extern void shutdown(int exitValue);




//this function is a bit different from : asteroid.cpp, bullet.cpp
//the loadFromFile  is in the constructor.  Ship.cpp uses the passed in Font as a reference.
//the other mentioned cpps have the texture passed in as a refernce
ship::ship(int positionx, int positiony, theDirection  shipdirection) 
{
	vectorposition.x = positionx;
	vectorposition.y = positiony;
	//these are the dimensions for all of the images of ther ship in different facing directions
	height = 64;
	width = 64;
	direction = shipdirection;

	if (!textureShipNorth.loadFromFile("shipNorth.png"))
	{
		shutdown(-10);
	}
	if (!textureShipEast.loadFromFile("shipEast.png")) 
	{
		shutdown(-11);
	}
	if (!textureShipSouth.loadFromFile("shipSouth.png")) 
	{
		shutdown(-12);
	}
	if (!textureShipWest.loadFromFile("shipWest.png")) 
	{
		shutdown(-13);
	}
	SelectTexture(shipdirection);
	
	//sets the position of the ship with x and y coordinates
	shipImage.setPosition(sf::Vector2f(shipImage.getPosition()));

}


//press m - rotates ship clockwise.
void ship::RotateShipClock() 
{

	//add one to the direction to rotate clockwise
	theDirection NewDirection = static_cast<theDirection>((1 + GetDirection()) % 4);
	SetDirection(NewDirection);
	SelectTexture(NewDirection);
	
}
//press n - rotates ship counter clockwise.
void ship::RotateShipCClock() 
{
	//add a full rotation (4) before subtracting one to avoid negative numbers and use modulus
	theDirection NewDirection = static_cast<theDirection>((3 + GetDirection()) % 4);
	SetDirection(NewDirection);
	SelectTexture(NewDirection);


}

void ship::SelectTexture(theDirection direction)
{
	if (direction == up)
	{
		shipImage.setTexture(textureShipNorth);
	}
	if (direction == right)
	{
		shipImage.setTexture(textureShipEast);
	}
	if (direction == down)
	{
		shipImage.setTexture(textureShipSouth);
	}
	if (direction == left)
	{
		shipImage.setTexture(textureShipWest);
	}


	
}


//direction is used to determine the deltax and deltay of the asteroids to use when
//two asteroids are created upon destruction of larger.
//also could be used later if a "wrapping effect" is needed for the asteroids from
//border to border
void ship::SetDirection(theDirection inDirection)
{
	direction = inDirection;
}
