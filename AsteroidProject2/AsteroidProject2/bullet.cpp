#include <SFML/Graphics.hpp>
#include "bullet.h"








Bullet::Bullet( sf::Texture & Texturebullet, int bulwidth, int bulheight )
{
	height = bulheight;
	width =  bulwidth;
	isactive = false;
	Bulletimage.setTexture(Texturebullet);
	


	

}

void Bullet::SetIsactive(bool activateflag) { isactive = activateflag; }


//direction is used to determine the deltax and deltay of the asteroids to use when
//two asteroids are created upon destruction of larger.
//also could be used later if a "wrapping effect" is needed for the asteroids from
//border to border
void Bullet::SetDirection(theDirection indirection)
{
	Direction = indirection;
}