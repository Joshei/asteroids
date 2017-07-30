#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>

#include "moveable.h"

class ship : public moveableObject
{

public:

	//sfml objects
	sf::Texture textureShipNorth;
	sf::Texture textureShipEast;
	sf::Texture textureShipSouth;
	sf::Texture textureShipWest;
	sf::Sprite shipImage;

	ship(int positionx, int positiony);

	int rotateShipClock(void);
	int rotateShipCClock(void);
};


#endif /* SHIP_H */