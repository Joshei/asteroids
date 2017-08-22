#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>


#include "moveable.h"
//#include "enumeration.h"


class ship : public moveableObject
{

public:

	
	
	

	ship(int positionx, int positiony, theDirection direction);
	
	void rotateShipClock();
	void rotateShipCClock();
	void selectTexture(theDirection direction);
	void setDirection(theDirection inDirection);
	theDirection getDirection(){return direction;}
	sf::Sprite & getShipImage(){return shipImage;}


private:

	
	theDirection direction;
	//sfml objects
	sf::Sprite shipImage;
	sf::Texture textureShipNorth;
	sf::Texture textureShipEast;
	sf::Texture textureShipSouth;
	sf::Texture textureShipWest;

};


#endif /* SHIP_H */