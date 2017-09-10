#ifndef BULLET_H
#define BULLET_H

#include "moveable.h"


class bullet : public moveableObject
{

public:

	
		
		
		bullet(sf::Texture & Texturebullet, int bulletheight, int bulletwidth);
		
		void SetIsactive(bool activateflag); 

		void SetDirection(theDirection Indirection);

		sf::Sprite  & GetBulletImage(){return Bulletimage;}
		
		
		int GetIsactive(){return isactive;}
	

		theDirection GetDirection(){return direction;}
		

private:

		theDirection direction;

		sf::Sprite Bulletimage;

		bool isactive;
	
};


#endif /* BULLET_H */










