#include "ship.h"
#include <SFML/Graphics.hpp>


extern void shutdown(int exitValue);




//this function is a bit different from : asteroid.cpp, bullet.cpp
//the loadFromFile  is in the constructor.  Ship.cpp uses the passed in Font as a reference.
//the other mentioned cpps have the texture passed in as a refernce
Ship::Ship(int positionx, int positiony, theDirection  Shipdirection) 
{
	Vectorposition.x = positionx;
	Vectorposition.y = positiony;
	//these are the dimensions for all of the images of ther ship in different facing directions
	height = 64;
	width = 64;
	Direction = Shipdirection;

	if (!Textureshipnorth.loadFromFile("shipNorth.png"))
	{
		shutdown(-10);
	}
	if (!Textureshipeast.loadFromFile("shipEast.png")) 
	{
		shutdown(-11);
	}
	if (!Textureshipsouth.loadFromFile("shipSouth.png")) 
	{
		shutdown(-12);
	}
	if (!Textureshipwest.loadFromFile("shipWest.png")) 
	{
		shutdown(-13);
	}
	SelectTexture(Shipdirection);
	
	//sets the position of the ship with x and y coordinates
	Shipimage.setPosition(sf::Vector2f(Shipimage.getPosition()));

}


//press m - rotates ship clockwise.
void Ship::RotateShipClock() 
{

	//add one to the direction to rotate clockwise
	theDirection Newdirection = static_cast<theDirection>((1 + GetDirection()) % 4);
	SetDirection(Newdirection);
	SelectTexture(Newdirection);
	
}
//press n - rotates ship counter clockwise.
void Ship::RotateShipCClock() 
{
	//add a full rotation (4) before subtracting one to avoid negative numbers and use modulus
	theDirection Newdirection = static_cast<theDirection>((3 + GetDirection()) % 4);
	SetDirection(Newdirection);
	SelectTexture(Newdirection);


}

void Ship::SelectTexture(theDirection Direction)
{
	if (Direction == up)
	{
		Shipimage.setTexture(Textureshipnorth);
	}
	if (Direction == right)
	{
		Shipimage.setTexture(Textureshipeast);
	}
	if (Direction == down)
	{
		Shipimage.setTexture(Textureshipsouth);
	}
	if (Direction == left)
	{
		Shipimage.setTexture(Textureshipwest);
	}


	
}


//direction is used to determine the deltax and deltay of the asteroids to use when
//two asteroids are created upon destruction of larger.
//also could be used later if a "wrapping effect" is needed for the asteroids from
//border to border
void Ship::SetDirection(theDirection Indirection)
{
	Direction = Indirection;
}
