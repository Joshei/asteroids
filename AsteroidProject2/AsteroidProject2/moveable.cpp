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
bool moveableObject::Intersects(moveableObject & Other)
{
	thisrect.left = Vectorposition.x;
	thisrect.top = Vectorposition.y;
	thisrect.right = Vectorposition.x + width;
	thisrect.bottom = Vectorposition.y + height;

	otherrect.left = Other.Vectorposition.x;
	otherrect.top = Other.Vectorposition.y;
	otherrect.right = Other.Vectorposition.x + Other.width;
	otherrect.bottom = Other.Vectorposition.y + Other.height;
	bool isintersected = IntersectsWithRectangles(thisrect, otherrect);
	return isintersected;
}
//returns boolean if intersected or not, called from either moveableObject::intersects or 
//moveableObject::screenIntersects 
bool moveableObject::IntersectsWithRectangles(RECT & thisrectangle, RECT & otherrectangle)
{
	int objectoneleft = thisrectangle.left;
	int objectonetop = thisrectangle.top;
	int objectoneright = thisrectangle.right;
	int objectonebottom = thisrectangle.bottom;
	int objecttwoleft = otherrectangle.left;
	int objecttwotop = otherrectangle.top;
	int objecttworight = otherrectangle.right;
	int objecttwobottom = otherrectangle.bottom;
	//clever check for non intersection with rectangles
	if (objectoneleft > objecttworight)
	{
		return false;
	}
	if (objectonetop > objecttwobottom)
	{
		return false;
	}
	if (objectoneright < objecttwoleft)
	{
		return false;
	}
	if (objectonebottom < objecttwotop)
	{
		return false;
	}
	return true;
}
bool moveableObject::IntersectsWithScreenRect(int screenwidth, int screenheight)
{
	//moveable object
	thisrect.left = Vectorposition.x;
	thisrect.top = Vectorposition.y;
	thisrect.right = Vectorposition.x + width;
	thisrect.bottom = Vectorposition.y + height;

	//screen Rectangle the next two changes are to make sure that the object is totally off the screen
	//the left and top edge "of the screen" is when the moveable object is located so it's edge is
	//on zero.
	otherrect.left = 0;
	otherrect.top = 0;

	//allows for one space past border to be part of rectangle to work 
	//when the object is readied with onscreen status
	otherrect.right = screenwidth ;
	otherrect.bottom = screenheight;
	
	return(IntersectsWithRectangles(thisrect, otherrect));


}

void moveableObject::SetVector(sf::Vector2f  invector)
{

	Vectorposition.x = invector.x;
	Vectorposition.y = invector.y;
}

void moveableObject::SetPrevVector(sf::Vector2f  invector)
{
	Vectorprevposition.x = invector.x;
	Vectorprevposition.y = invector.y;

}

//sets x position for those objects that inherit from moveable
void moveableObject::SetX(int  inx)
{
	Vectorposition.x = inx;
	
}
//sets y positio for those objects that inherit from moveable
void moveableObject::SetY(int iny)
{
	Vectorposition.y = iny;
}

//these two set functions hold the prev x and y postions so that the main loop can interpolate correctly 
void moveableObject::SetPrevX(int inprevx)
{
	Vectorprevposition.x = inprevx;
}
void moveableObject::SetPrevY(int inprevy)
{
	Vectorprevposition.y = inprevy;

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

