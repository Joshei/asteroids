#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <windows.h>

//class asteroid and class bullet inherit from this
class moveableObject 
{

public:

	

	moveableObject(void);


	bool intersects(const moveableObject & theOtherObject);
	
	bool intersectsWithRectangles(const RECT & thisRect , const RECT & otherRect);


	//inlines
	int getX(void) 
	{ 
		return(x); 
	}
	
	int getY(void) 
	{
		return(y); 
	}
	
	int getDeltaY(void) 
	{
		return(deltaY); 
	}
	
	int getDeltaX(void) 
	{
		return(deltaX); 
	}

	int getDirection(void)
	{
		return(direction);
	}

	int getHeight(void) {
		return (height);
	}

	int getWidth(void) {
		return(width);
	}

	void setX(int inX);
	void setY(int inY);
	void setDeltaX(int  inDeltaX);
	void setDeltaY(int inDeltaY);
	void setDirection(int inDirection);
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
	int direction;
	int x;
	int y;
	

	
};


#endif  /*  MOVEABLEOBJECT_H  */