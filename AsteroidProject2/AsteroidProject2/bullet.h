#ifndef BULLET_H
#define BULLET_H

#include "moveable.h"


class bullet : public moveableObject
{

public:

	
		static int maxBullets;
		
		bullet( sf::Texture & textureBullet, int bulletHeight, int bulletWidth );
		
		void setIsactive(bool activateFlag); 

		
		sf::Sprite  & getBulletImage()
		{
			return(bulletImage);
		}
		
		
		int getIsactive() 
		{
			return (isactive); 
		}
	
private:

		sf::Sprite bulletImage;

		bool isactive;
	
};


#endif /* BULLET_H */










