#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <windows.h>
#include "enumeration.h"
#include <SFML/Graphics.hpp>


//class asteroid and class bullet inherit from this
class moveableObject 
{

public:

	


	moveableObject();


	bool Intersects(moveableObject & theotherobject);
	bool IntersectsWithRectangles(RECT & thisrect , RECT & otherrect);
	bool IntersectsWithScreenRect(int displaywidth, int displayheight);
	
	void SetX(int inx);
	void SetY(int iny);
	void SetDeltaX(int  indeltax);
	void SetDeltaY(int indeltay);
	
	void SetWidth(int inwidth);
	void SetHeight(int inheight);

	void SetPrevX(int inprevx);
	void SetPrevY(int inprevy);
	void SetVector(sf::Vector2f  invector);
	void SetPrevVector(sf::Vector2f  invector);



	//inlines
	float GetX(){return vectorposition.x;}
	
	float GetY(){return vectorposition.y;}
	
	int GetDeltaY(){return deltay;}
	
	int GetDeltaX(){return deltax;}

	int GetHeight(){return height;}

	int GetWidth(){return width;}

	float GetPrevX(){return vectorprevposition.x;}
	float GetPrevY(){return vectorprevposition.y;}
	sf::Vector2f  GetVectorPosition(){return vectorposition;}
	sf::Vector2f   GetVectorPrevPosition(){return vectorprevposition;}


protected:

	sf::Vector2f  vectorposition;
	sf::Vector2f  vectorprevposition;

	

	//used for intercept of moveable objects or screen and moveable (not intercept)
	RECT thisrect;
	RECT otherrect;
	int deltax;
	int deltay;
	int width;


	int height;
	
	//int x;
	//int y;
	
	//int prevx;
	//int prevy;

	
};


#endif  /*  MOVEABLEOBJECT_H  */