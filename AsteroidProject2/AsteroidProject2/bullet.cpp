#include <SFML/Graphics.hpp>
#include "bullet.h"





//statics	
int bullet::maxBullets = 10;

//upon creation of vector maxBullets has to be set (a static variable)
bullet::bullet( sf::Texture & texturebullet, int bulheight, int bulwidth )
{
	height = bulheight;
	width =  bulwidth;
	isactive = false;
	bulletimage.setTexture(texturebullet);

}

void bullet::SetIsactive(bool activateflag) { isactive = activateflag; }


//direction is used to determine the deltax and deltay of the asteroids to use when
//two asteroids are created upon destruction of larger.
//also could be used later if a "wrapping effect" is needed for the asteroids from
//border to border
void bullet::SetDirection(theDirection indirection)
{
	direction = indirection;
}