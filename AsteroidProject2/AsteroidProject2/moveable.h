#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <windows.h>
#include "enumeration.h"
#include <SFML/Graphics.hpp>


//class asteroid and class bullet inherit from this
class MoveableObject 
{

public:

	


	MoveableObject();


	bool Intersects(MoveableObject & Theotherobject);
	bool IntersectsWithRectangles(RECT & Thisrect , RECT & Otherrect);
	bool IntersectsWithScreenRect(int displaywidth, int displayheight);
	
	void SetX(int inx);
	void SetY(int iny);
	void SetDeltaX(int  indeltax);
	void SetDeltaY(int indeltay);
	
	void SetWidth(int inwidth);
	void SetHeight(int inheight);

	void SetPrevX(int inprevx);
	void SetPrevY(int inprevy);
	void SetVector(sf::Vector2f  Invector);
	void SetPrevVector(sf::Vector2f  Invector);



	//inlines
	float GetX(){return Vectorposition.x;}
	
	float GetY(){return Vectorposition.y;}
	
	int GetDeltaY(){return deltay;}
	
	int GetDeltaX(){return deltax;}

	int GetHeight(){return height;}

	int GetWidth(){return width;}

	float GetPrevX(){return Vectorprevposition.x;}
	float GetPrevY(){return Vectorprevposition.y;}
	sf::Vector2f  GetVectorPosition(){return Vectorposition;}
	sf::Vector2f   GetVectorPrevPosition(){return Vectorprevposition;}


protected:

	sf::Vector2f  Vectorposition;
	sf::Vector2f  Vectorprevposition;

	

	//used for intercept of moveable objects or screen and moveable (not intercept)
	RECT Thisrect;
	RECT Otherrect;
	int deltax;
	int deltay;
	int width;


	int height;
	
	

	
};


#endif  /*  MOVEABLEOBJECT_H  */