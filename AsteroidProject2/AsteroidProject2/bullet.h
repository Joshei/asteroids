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
		
		void setIsactive(bool activateFlag); 

		
	
		
		
		int getIsactive() 
		{
			return (isactive); 
		}
	
private:

		bool isactive;
	
};


#endif /* BULLET_H */










