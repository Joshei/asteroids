#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <windows.h>
#include "enumeration.h"
 
//class asteroid and class bullet inherit from this
class moveableObject 
{

public:

	

	moveableObject();


	bool intersects(const moveableObject & theOtherObject);
	bool intersectsWithRectangles(const RECT & thisRect , const RECT & otherRect);
	bool intersectsWithScreenRect(int displayWidth, int displayHeight);
	


	//inlines
	int getX() 
	{ 
		return(x); 
	}
	
	int getY() 
	{
		return(y); 
	}
	
	int getDeltaY() 
	{
		return(deltaY); 
	}
	
	int getDeltaX() 
	{
		return(deltaX); 
	}

	theDirection getDirection()
	{
		return(direction);
	}

	int getHeight() {
		return (height);
	}

	int getWidth() {
		return(width);
	}

	void setX(int inX);
	void setY(int inY);
	void setDeltaX(int  inDeltaX);
	void setDeltaY(int inDeltaY);
	void setDirection(theDirection inDirection);
	void setWidth(int inWidth);
	void setHeight(int inHeight);

protected:

	//used for intercept of moveable objects or screen and moveable (not intercept)
	RECT thisRect;
	RECT otherRect;
	int deltaX;
	int deltaY;
	int width;
	int height;
	theDirection direction;
	int x;
	int y;
	

	
};


#endif  /*  MOVEABLEOBJECT_H  */