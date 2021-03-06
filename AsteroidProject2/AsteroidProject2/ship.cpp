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

	//loads all the images for use by shipObject
	if (!Textureshipnorth.loadFromFile("shipNorth.png"))
	{
		shutdown(-6);
	}
	if (!Textureshipeast.loadFromFile("shipEast.png")) 
	{
		shutdown(-7);
	}
	if (!Textureshipsouth.loadFromFile("shipSouth.png")) 
	{
		shutdown(-8);
	}
	if (!Textureshipwest.loadFromFile("shipWest.png")) 
	{
		shutdown(-9);
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

//sets the image by the direction.
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


//direction of ship
void Ship::SetDirection(theDirection Indirection)
{
	Direction = Indirection;
}
