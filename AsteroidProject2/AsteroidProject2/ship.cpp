#include "ship.h"
#include <SFML/Graphics.hpp>
#include "enumeration.h"


extern void shutdown(int exitValue);




//this function is a bit different from : asteroid.cpp, bullet.cpp
//the loadFromFile  is in the constructor.  Ship.cpp uses the passed in Font as a reference.
//the other mentioned cpps have the texture passed in as a refernce
ship::ship(int positionx, int positiony) 
{
	x = positionx;
	y = positiony;
	//these are the dimensions for all of the images of ther ship in different facing directions
	height = 64;
	width = 64;
	direction = up;

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


	///sf::Sprite shipImage;
	shipImage.setTexture(textureShipNorth);


	//sets the position of the ship with x and y coordinates
	shipImage.setPosition(sf::Vector2f(positionx, positiony));

}


//press m - rotates ship clockwise.
int ship::rotateShipClock(void) 
{

	
	

	if (getDirection() == up) { setDirection(right); shipImage.setTexture(textureShipEast); }
	else if (getDirection() == down) { setDirection(left); shipImage.setTexture(textureShipWest); }
	else if (getDirection() == right) { setDirection(down); shipImage.setTexture(textureShipSouth); }
	else if (getDirection() == left) { setDirection(up);  shipImage.setTexture(textureShipNorth); }

	return(1);
}
//press n - rotates ship counter clockwise.
int ship::rotateShipCClock(void) 
{

	
	if (getDirection() == up) { setDirection(left); shipImage.setTexture(textureShipWest); }
	else if (getDirection() == down) { setDirection(right); shipImage.setTexture(textureShipEast); }
	else if (getDirection() == right) { setDirection(up); shipImage.setTexture(textureShipNorth); }
	else if (getDirection() == left) { setDirection(down);  shipImage.setTexture(textureShipSouth); }

	return(1);

}