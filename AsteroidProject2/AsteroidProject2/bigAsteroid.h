#pragma once
#include "asteroid.h"
#include "moveable.h"
#include <SFML/Graphics.hpp>

class bigAsteroid : public asteroid, public moveableObject
{


public:

	static sf::Texture textureAsteroid;
	static sf::Sprite anAsteroid;
	
};