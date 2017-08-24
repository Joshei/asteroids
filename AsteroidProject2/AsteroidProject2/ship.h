#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>


#include "moveable.h"
//#include "enumeration.h"


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
	sf::Texture textureshipnorth;
	sf::Texture textureshipeast;
	sf::Texture textureshipsouth;
	sf::Texture textureshipwest;

};


#endif /* SHIP_H */