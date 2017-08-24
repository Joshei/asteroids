#ifndef BULLET_H
#define BULLET_H

#include "moveable.h"


class bullet : public moveableObject
{

public:

	
		
		
		bullet(sf::Texture & textureBullet, int bulletheight, int bulletwidth);
		
		void SetIsactive(bool activateFlag); 

		void SetDirection(theDirection inDirection);

		sf::Sprite  & GetBulletImage(){return bulletImage;}
		
		
		int GetIsactive(){return isactive;}
	

		theDirection GetDirection(){return direction;}
		

private:

		theDirection direction;

		sf::Sprite bulletImage;

		bool isactive;
	
};


#endif /* BULLET_H */










