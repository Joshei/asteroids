#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>


#include "moveable.h"



class ship : public moveableObject
{

public:

	
	
	

	ship(int positionx, int positiony, theDirection Direction);
	
	void RotateShipClock();
	void RotateShipCClock();
	void SelectTexture(theDirection Direction);
	void SetDirection(theDirection Indirection);
	theDirection GetDirection(){return Direction;}
	sf::Sprite & GetShipImage(){return Shipimage;}


private:

	
	theDirection Direction;
	//sfml objects
	sf::Sprite Shipimage;
	sf::Texture Textureshipnorth;
	sf::Texture Textureshipeast;
	sf::Texture Textureshipsouth;
	sf::Texture Textureshipwest;

};


#endif /* SHIP_H */