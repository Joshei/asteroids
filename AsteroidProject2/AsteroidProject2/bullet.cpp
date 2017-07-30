#include <SFML/Graphics.hpp>
#include "bullet.h"



void bullet::setMaxNumBullets(int maxNumBullets) { maxBullets = maxNumBullets; }
void bullet::setIsactive(bool activateFlag) { isactive = activateFlag; }

//statics	
int bullet::maxBullets = 10;

//upon creation of vector maxBullets has to be set (a static variable)
bullet::bullet( sf::Texture & textureBullet, int bulHeight, int bulWidth )
{
	height = bulHeight;
	width =  bulWidth;
	isactive = false;
	bulletImage.setTexture(textureBullet);

}

