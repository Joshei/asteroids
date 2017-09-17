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


//direction of bullet
void Bullet::SetDirection(theDirection indirection)
{
	Direction = indirection;
}