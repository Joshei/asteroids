#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>


#include "moveable.h"



class ship : public moveableObject
{

public:

	
	
	

	ship(int positionx, int positiony, theDirection direction);
	
	void RotateShipClock();
	void RotateShipCClock();
	void SelectTexture(theDirection direction);
	void SetDirection(theDirection inDirection);
	theDirection GetDirection(){return direction;}
	sf::Sprite & GetShipImage(){return shipImage;}


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