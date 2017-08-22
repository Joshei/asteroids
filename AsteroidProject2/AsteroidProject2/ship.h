#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>


#include "moveable.h"
//#include "enumeration.h"


class ship : public moveableObject
{

public:

	//sfml objects
	sf::Texture textureShipNorth;
	sf::Texture textureShipEast;
	sf::Texture textureShipSouth;
	sf::Texture textureShipWest;
	sf::Sprite shipImage;

	ship(int positionx, int positiony, theDirection direction);
	sf::Sprite & getShipImage() { return shipImage; }

	void rotateShipClock();
	void rotateShipCClock();
	void selectTexture(theDirection direction);
};


#endif /* SHIP_H */