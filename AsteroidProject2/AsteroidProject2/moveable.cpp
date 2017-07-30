#include "moveable.h"

moveableObject::moveableObject(void)
	: width(0), height(0), x(0), y(0), deltaX(0), deltaY(0), direction(0)
{



}

//sets x position for those objects that inherit from moveable
void moveableObject::setX(int  inX) 
{
	x = inX;

}

//sets y positio for those objects that inherit from moveable
void moveableObject::setY(int inY) 
{
	y = inY;

}

//deltaX is the change in x after each key press and cycle in main
void moveableObject::setDeltaX(int  inDeltaX) 
{
	deltaX = inDeltaX;

}


//deltaY is the change in x after each key press and cycle in main
void moveableObject::setDeltaY(int inDeltaY) 
{
	deltaY = inDeltaY;

}


//direction is used to determine the deltax and deltay of the asteroids to use when
//two asteroids are created upon destruction of larger.
//also could be used later if a "wrapping effect" is needed for the asteroids from
//border to border

void moveableObject::setDirection(int inDirection)
{
	direction = inDirection;

}

//this allows each object to have its own width
void moveableObject::setWidth(int inWidth)
{

	width = inWidth;

}
//this allow each object to have its own height
void moveableObject::setHeight(int inHeight)
{
	height = inHeight;

}