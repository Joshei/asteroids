#ifndef BULLET_H
#define BULLET_H

#include "moveable.h"


class bullet : public moveableObject
{

public:

	
		static int maxBullets;
		
		bullet(sf::Texture & textureBullet, int bulletHeight, int bulletWidth);
		
		void setIsactive(bool activateFlag); 

		void setDirection(theDirection inDirection);

		sf::Sprite  & getBulletImage(){return bulletImage;}
		
		
		int getIsactive(){return isactive;}
	

		theDirection getDirection(){return direction;}
		

private:

		theDirection direction;

		sf::Sprite bulletImage;

		bool isactive;
	
};


#endif /* BULLET_H */










