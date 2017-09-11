#include "moveable.h"



moveableObject::moveableObject()
	: width(0), height(0), deltax(0), deltay(0)
{
	//used for collision functions for checking for itersects with moveable objects and 
	//also screen non intercept
	Thisrect = { 0,0,0,0 };
	Otherrect = { 0,0,0,0 };
	

	
}
//checks for collision of two moveable objects by calling intersectsWithRectangles function. Returns
//bool value for if collides
bool moveableObject::Intersects(moveableObject & Other)
{
	Thisrect.left = Vectorposition.x;
	Thisrect.top = Vectorposition.y;
	Thisrect.right = Vectorposition.x + width;
	Thisrect.bottom = Vectorposition.y + height;

	Otherrect.left = Other.Vectorposition.x;
	Otherrect.top = Other.Vectorposition.y;
	Otherrect.right = Other.Vectorposition.x + Other.width;
	Otherrect.bottom = Other.Vectorposition.y + Other.height;
	bool isintersected = IntersectsWithRectangles(Thisrect, Otherrect);
	return isintersected;
}
//returns boolean if intersected or not, called from either moveableObject::intersects or 
//moveableObject::screenIntersects 
bool moveableObject::IntersectsWithRectangles(RECT & Thisrectangle, RECT & Otherrectangle)
{
	int objectoneleft = Thisrectangle.left;
	int objectonetop = Thisrectangle.top;
	int objectoneright = Thisrectangle.right;
	int objectonebottom = Thisrectangle.bottom;
	int objecttwoleft = Otherrectangle.left;
	int objecttwotop = Otherrectangle.top;
	int objecttworight = Otherrectangle.right;
	int objecttwobottom = Otherrectangle.bottom;
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
	Thisrect.left = Vectorposition.x;
	Thisrect.top = Vectorposition.y;
	Thisrect.right = Vectorposition.x + width;
	Thisrect.bottom = Vectorposition.y + height;

	//screen Rectangle the next two changes are to make sure that the object is totally off the screen
	//the left and top edge "of the screen" is when the moveable object is located so it's edge is
	//on zero.
	Otherrect.left = 0;
	Otherrect.top = 0;

	//allows for one space past border to be part of rectangle to work 
	//when the object is readied with onscreen status
	Otherrect.right = screenwidth ;
	Otherrect.bottom = screenheight;
	
	return(IntersectsWithRectangles(Thisrect, Otherrect));


}

void moveableObject::SetVector(sf::Vector2f  Invector)
{

	Vectorposition.x = Invector.x;
	Vectorposition.y = Invector.y;
}

void moveableObject::SetPrevVector(sf::Vector2f  Invector)
{
	Vectorprevposition.x = Invector.x;
	Vectorprevposition.y = Invector.y;

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

