#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <windows.h>
#include "enumeration.h"
 
//class asteroid and class bullet inherit from this
class moveableObject 
{

public:

	

	moveableObject();


	bool Intersects(moveableObject & theOtherObject);
	bool IntersectsWithRectangles(RECT & thisRect , RECT & otherRect);
	bool IntersectsWithScreenRect(int displayWidth, int displayHeight);
	
	void SetX(int inX);
	void SetY(int inY);
	void SetDeltaX(int  inDeltaX);
	void SetDeltaY(int inDeltaY);
	
	void SetWidth(int inWidth);
	void SetHeight(int inHeight);


	//inlines
	int GetX(){return x;}
	
	int GetY(){return y;}
	
	int GetDeltaY(){return deltaY;}
	
	int GetDeltaX(){return deltaX;}

	int GetHeight(){return height;}

	int GetWidth(){return width;}

	

protected:

	//used for intercept of moveable objects or screen and moveable (not intercept)
	RECT thisRect;
	RECT otherRect;
	int deltaX;
	int deltaY;
	int width;
	int height;
	
	int x;
	int y;
	

	
};


#endif  /*  MOVEABLEOBJECT_H  */