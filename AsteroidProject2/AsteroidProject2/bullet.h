#ifndef BULLET_H
#define BULLET_H

#include "moveable.h"


class Bullet : public MoveableObject
{

public:

	
		
		
		Bullet(sf::Texture & Texturebullet, int bulletheight, int bulletwidth);
		
		void SetIsactive(bool activateflag); 

		void SetDirection(theDirection Indirection);

		sf::Sprite  & GetBulletImage(){return Bulletimage;}
		
		
		int GetIsactive(){return isactive;}
	

		theDirection GetDirection(){return Direction;}
		

private:

		theDirection Direction;

		sf::Sprite Bulletimage;

		bool isactive;
	
};


#endif /* BULLET_H */










