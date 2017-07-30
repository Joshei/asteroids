#ifndef BULLET_H
#define BULLET_H

#include "moveable.h"


class bullet : public moveableObject
{

public:

		
		//sfml object passed a texture uses a pointer
		sf::Sprite bulletImage;
		
		static int maxBullets;
		
		bullet( sf::Texture & textureBullet, int bulletHeight, int bulletWidth );
		
		static void setMaxNumBullets(int maxNumBullets);
		void setIsactive(bool activateFlag);
	
		static int getMaxNumBullets(void)
		{ 
			return maxBullets; 
		}
		
		int getIsactive(void) 
		{
			return (isactive); 
		}
	
private:

		bool isactive;
	
};


#endif /* BULLET_H */










