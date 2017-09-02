#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <windows.h>
#include "enumeration.h"
 
//class asteroid and class bullet inherit from this
class moveableObject 
{

public:

	int prevx;
	int prevy;


	moveableObject();


	bool Intersects(moveableObject & theotherobject);
	bool IntersectsWithRectangles(RECT & thisrect , RECT & otherrect);
	bool IntersectsWithScreenRect(int displaywidth, int displayheight);
	
	void SetX(int inX);
	void SetY(int inY);
	void SetDeltaX(int  indeltax);
	void SetDeltaY(int indeltay);
	
	void SetWidth(int inwidth);
	void SetHeight(int inheight);


	//inlines
	int GetX(){return x;}
	
	int GetY(){return y;}
	
	int GetDeltaY(){return deltay;}
	
	int GetDeltaX(){return deltax;}

	int GetHeight(){return height;}

	int GetWidth(){return width;}

	

protected:

	//used for intercept of moveable objects or screen and moveable (not intercept)
	RECT thisrect;
	RECT otherrect;
	int deltax;
	int deltay;
	int width;
	int height;
	
	int x;
	int y;
	

	
};


#endif  /*  MOVEABLEOBJECT_H  */