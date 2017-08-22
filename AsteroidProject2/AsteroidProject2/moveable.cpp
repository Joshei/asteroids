#include "moveable.h"


moveableObject::moveableObject()
	: width(0), height(0), x(0), y(0), deltaX(0), deltaY(0)
{
	//used for collision functions for checking for itersects with moveable objects and 
	//also screen non intercept
	thisRect = { 0,0,0,0 };
	otherRect = { 0,0,0,0 };
}
//checks for collision of two moveable objects by calling intersectsWithRectangles function. Returns
//bool value for if collides
bool moveableObject::intersects(moveableObject & other)
{
	thisRect.left = x;
	thisRect.top = y;
	thisRect.right = x + width;
	thisRect.bottom = y + height;

	otherRect.left = other.x;
	otherRect.top = other.y;
	otherRect.right = other.x + other.width;
	otherRect.bottom = other.y + other.height;
	bool isIntersected = intersectsWithRectangles(thisRect, otherRect);
	return isIntersected;
}
//returns boolean if intersected or not, called from either moveableObject::intersects or 
//moveableObject::screenIntersects 
bool moveableObject::intersectsWithRectangles(RECT & thisRectangle, RECT & otherRectangle)
{
	int objectOneLeft = thisRectangle.left;
	int objectOneTop = thisRectangle.top;
	int objectOneRight = thisRectangle.right;
	int objectOneBottom = thisRectangle.bottom;
	int objectTwoLeft = otherRectangle.left;
	int objectTwoTop = otherRectangle.top;
	int objectTwoRight = otherRectangle.right;
	int objectTwoBottom = otherRectangle.bottom;
	//clever check for non intersection with rectangles
	if (objectOneLeft > objectTwoRight)
	{
		return false;
	}
	if (objectOneTop > objectTwoBottom)
	{
		return false;
	}
	if (objectOneRight < objectTwoLeft)
	{
		return false;
	}
	if (objectOneBottom < objectTwoTop)
	{
		return false;
	}
	return true;
}
bool moveableObject::intersectsWithScreenRect(int screenWidth, int screenHeight)
{
	//moveable object
	thisRect.left = x;
	thisRect.top = y;
	thisRect.right = x + width;
	thisRect.bottom = y + height;

	//screen Rectangle the next two changes are to make sure that the object is totally off the screen
	//the left and top edge "of the screen" is when the moveable object is located so it's edge is
	//on zero.
	otherRect.left = 0 ;
	otherRect.top = 0;

	//allows for one space past border to be part of rectangle to work 
	//when the object is readied with onscreen status
	otherRect.right = screenWidth ;
	otherRect.bottom = screenHeight;
	
	return(intersectsWithRectangles(thisRect, otherRect));


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