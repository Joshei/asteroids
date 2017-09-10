#include "moveable.h"



moveableObject::moveableObject()
	: width(0), height(0), deltax(0), deltay(0)
{
	//used for collision functions for checking for itersects with moveable objects and 
	//also screen non intercept
	thisrect = { 0,0,0,0 };
	otherrect = { 0,0,0,0 };
	

	//prevx = 500;
	//prevy = 500;
}
//checks for collision of two moveable objects by calling intersectsWithRectangles function. Returns
//bool value for if collides
bool moveableObject::Intersects(moveableObject & other)
{
	thisrect.left = vectorposition.x;
	thisrect.top = vectorposition.y;
	thisrect.right = vectorposition.x + width;
	thisrect.bottom = vectorposition.y + height;

	otherrect.left = other.vectorposition.x;
	otherrect.top = other.vectorposition.y;
	otherrect.right = other.vectorposition.x + other.width;
	otherrect.bottom = other.vectorposition.y + other.height;
	bool isIntersected = IntersectsWithRectangles(thisrect, otherrect);
	return isIntersected;
}
//returns boolean if intersected or not, called from either moveableObject::intersects or 
//moveableObject::screenIntersects 
bool moveableObject::IntersectsWithRectangles(RECT & thisrectangle, RECT & otherrectangle)
{
	int objectOneLeft = thisrectangle.left;
	int objectOneTop = thisrectangle.top;
	int objectOneRight = thisrectangle.right;
	int objectOneBottom = thisrectangle.bottom;
	int objectTwoLeft = otherrectangle.left;
	int objectTwoTop = otherrectangle.top;
	int objectTwoRight = otherrectangle.right;
	int objectTwoBottom = otherrectangle.bottom;
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
bool moveableObject::IntersectsWithScreenRect(int screenwidth, int screenheight)
{
	//moveable object
	thisrect.left = vectorposition.x;
	thisrect.top = vectorposition.y;
	thisrect.right = vectorposition.x + width;
	thisrect.bottom = vectorposition.y + height;

	//screen Rectangle the next two changes are to make sure that the object is totally off the screen
	//the left and top edge "of the screen" is when the moveable object is located so it's edge is
	//on zero.
	otherrect.left = 0 ;
	otherrect.top = 0;

	//allows for one space past border to be part of rectangle to work 
	//when the object is readied with onscreen status
	otherrect.right = screenwidth ;
	otherrect.bottom = screenheight;
	
	return(IntersectsWithRectangles(thisrect, otherrect));


}

void moveableObject::SetVector(sf::Vector2f  invector)
{

	vectorposition.x = invector.x;
	vectorposition.y = invector.y;
}

void moveableObject::SetPrevVector(sf::Vector2f  invector)
{
	vectorprevposition.x = invector.x;
	vectorprevposition.y = invector.y;

}

//sets x position for those objects that inherit from moveable
void moveableObject::SetX(int  inx)
{
	vectorposition.x = inx;
	
}
//sets y positio for those objects that inherit from moveable
void moveableObject::SetY(int iny)
{
	vectorposition.y = iny;
}

//these two set functions hold the prev x and y postions so that the main loop can interpolate correctly 
void moveableObject::SetPrevX(int inprevx)
{
	vectorprevposition.x = inprevx;
}
void moveableObject::SetPrevY(int inprevy)
{
	vectorprevposition.y = inprevy;

}
//deltaX is the change in x after each key press and cycle in main
void moveableObject::SetDeltaX(int  indeltax)
{
	deltax = indeltax;
}
//deltaY is the change in x after each key press and cycle in main
void moveableObject::SetDeltaY(int indeltay)
{
	deltay = indeltay;
}

//this allows each object to have its own width
void moveableObject::SetWidth(int inwidth)
{
	width = inwidth;
}
//this allow each object to have its own height
void moveableObject::SetHeight(int inheight)
{
	height = inheight;
}

