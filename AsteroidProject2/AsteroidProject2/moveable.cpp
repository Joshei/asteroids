#include "moveable.h"



MoveableObject::MoveableObject()
	: width(0), height(0), deltax(0), deltay(0)
{
	//used for collision functions for checking for itersects with moveable objects and 
	//also screen non intercept
	Thisrect = { 0,0,0,0 };
	Otherrect = { 0,0,0,0 };
	

	
}
//checks for collision of two moveable objects by calling intersectsWithRectangles function. Returns
//bool value for if collides
bool MoveableObject::Intersects(MoveableObject & Other)
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
bool MoveableObject::IntersectsWithRectangles(RECT & Thisrectangle, RECT & Otherrectangle)
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
bool MoveableObject::IntersectsWithScreenRect(int screenwidth, int screenheight)
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

	//used for checking for off screen
	Otherrect.right = screenwidth ;
	Otherrect.bottom = screenheight;
	
	return(IntersectsWithRectangles(Thisrect, Otherrect));


}

//simplified setting of x and y with one call when needed
void MoveableObject::SetVector(sf::Vector2f  Invector)
{

	Vectorposition.x = Invector.x;
	Vectorposition.y = Invector.y;
}

//for interpolation (smooth movement)
void MoveableObject::SetPrevVector(sf::Vector2f  Invector)
{
	Vectorprevposition.x = Invector.x;
	Vectorprevposition.y = Invector.y;

}

//sets x position for those objects that inherit from moveable
void MoveableObject::SetX(int  inx)
{
	Vectorposition.x = inx;
	
}
//sets y position for those objects that inherit from moveable
void MoveableObject::SetY(int iny)
{
	Vectorposition.y = iny;
}

//these two set functions hold the prev x and y postions so that the main loop can interpolate correctly 
void MoveableObject::SetPrevX(int inprevx)
{
	Vectorprevposition.x = inprevx;
}
void MoveableObject::SetPrevY(int inprevy)
{
	Vectorprevposition.y = inprevy;

}
//deltaX is the change in x after each key press or cycle in main with an unpressed key
void MoveableObject::SetDeltaX(int  indeltax)
{
	deltax = indeltax;
}
//deltaY is the change in x after each key press or cycle in main with an unpressed key
void MoveableObject::SetDeltaY(int indeltay)
{
	deltay = indeltay;
}


void MoveableObject::SetWidth(int inwidth)
{
	width = inwidth;
}

void MoveableObject::SetHeight(int inheight)
{
	height = inheight;
}

