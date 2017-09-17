//headers
//comment for learning push changes




#include "windows.h"
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "asteroid.h"
#include "ship.h"
#include "score.h"
#include <vector>
#include <ctime>
#include "enumeration.h"
#include "level.h"


//used to break out of while, when is set 
int g_TotalNumAllAsteroids = 0;




//GLOBAL FUNCTION DECLARATIONS

//the vector holds x an y
bool checkForShipOnBorder(sf::Vector2f shipvector);
bool checkKeyboard();
bool checkAllAsteroidsDestroyed();
int  moveShip(int amountForMovem, int keyPressed);
int shoot();
void checkForBulletOffscreen(int index);


void drawShip();
void checkCollisionsShipWithAsteroids();
void checkCollisionsaAllBulletsWithAnAsteroids();
void moveBullets();
void checkForAsteroidOffScreen();
void shutdown(int exitNum);
void fillAsteroidVector(int numOfAsteroid , int theWidth, int theHeight, asteroidType theAsteroidType, sf::Texture & theTexture);
int createSmallerAsteroids(int indexOfAsteroid);
void moveAsteroids();
void reinitializeOffscreenAsteroids();
void fillBulletVector(int numberOfBullets, sf::Texture & textureOfBullet);
void refillAsteroidVectors(int createThisManyAsteroids, int theWidth, int theHeight, asteroidType asteroidType, sf::Texture & theTexture);
void getTwoDirectionsFromMajorDirection(asteroidMovement & theMajorDirection, asteroidMovement & smallAsteroidDirection1, asteroidMovement & smallAsteroidDirection2);
void setAllAsteroidsPrev();
void positionAsteroidsAndDraw(int theinterpolation);
void positionBulletsAndDraw(int interpolation);
void setAllBulletsPrev();
/////////!!!!!!!!!!!!!!!!!!


//put here together because smallerTextureAsteroid used in: checkCollisionsaAllBulletsWithAnAsteroid 
sf::Texture Largertextureasteroid;
sf::Texture Smallertextureasteroid;
sf::Texture Texturebullet;
sf::Font Fontforscore;

//initialized of the vectors for asteroids
std::vector<Asteroid> asteroidCollection;
std::vector <Bullet> bullets;
Score Thescore(10, 10);
sf::Event event;
sf::RenderWindow window(sf::VideoMode(G_SCREEN_WIDTH, G_SCREEN_HEIGHT), "Asteroids!");

//global ship pbject
Ship shipObject(500, 500, up);
LevelObj levelObject;




//GLOBAL FUNCTION DEFINITIONS FOLLOW:

void drawShip(){


	window.draw(shipObject.GetShipImage());
	
}


//this function is called from keypress and main so that from every keypress there is 
//a reaction but the main also calls the move with a pressedKey set at -1 so that there
//is a gliding effect.  If the keypress is not pressed than the ship will move with
//its current deltax and deltay. 
int moveShip(int amountForMovement = -1,  int pressedKey = -1)
{

	

	//delta amountForMovement of ship:
	
	//up :   -3
	//down:   3
	//left:  -3
	//right:  3
	
	//these functions use enumeration to change the deltas.  The deltas are the change in x or y
	//now set at 3 or -3 so the x and y can also be computed.  This is if the paramter passed in 
	//is not -1.  If it is -1 then ship is moved with the same deltas.  Deltas are also used to set
	//the SFML move function below.
	if (pressedKey == up) 
	{
		shipObject.SetDeltaY(amountForMovement); 
	}
	else if (pressedKey == down) 
	{ 
		shipObject.SetDeltaY(amountForMovement);
	}
	else if (pressedKey == right)
	{ 
		shipObject.SetDeltaX(amountForMovement);
	}
	else if (pressedKey == left)
	{ 
		shipObject.SetDeltaX(amountForMovement); 
	}
	

		
	//set the change in y and the change in x variables (meaning if delta)
	int Deltax = shipObject.GetDeltaX();
	int Deltay = shipObject.GetDeltaY();


	//set the x and y using the delta (change of x or y) and updating the x and y values for checking 
	

	sf::Vector2f temp =  shipObject.GetVectorPosition();
	temp.x = temp.x + Deltax;
	temp.y = temp.y + Deltay;


	
	
	

	//is off screen returns false
	if (checkForShipOnBorder(temp) == false)
	{
		drawShip();
		return (-1);
	}



	shipObject.SetVector(temp);
	//set for interpolation
	shipObject.SetPrevVector(temp);

	
	
	
	
	return(1);
}


bool checkKeyboard() 
{

	
	//this is setting the change in x and the change in y to a minimum value of negative three
	//or a maximum of postive three.  Value is set as one of these numbers. for now
	//they are set to 3 or -3.  There are two other speeds set one for asteroids and one for
	//bullets.  
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  
	{
		moveShip(-3, left); 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{ 
		moveShip(3, right); 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveShip(-3, up); 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveShip(3, down ); 
	}
	else
	{
		//if in here no key pressed this cycle
		return(false);
	}

	return(true);
}


//The idea is to check if the ship is in the y-range and x-range of the asteroid
//if so there is a collision!
void checkCollisionsShipWithAsteroids() 
{
	


	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		//checks if asteroid on screen if so is not initialized, destroyed, instantiated, or offscreen
		//so if it is onscreen enters beneath this if.  Otherwise it continues to the for loop with next value of i.
		if (asteroidCollection[i].GetActivate() != onscreen )
		{
			continue;

		}
		if (shipObject.Intersects(asteroidCollection[i]))
		{
			shutdown(-1);
		}
	}

		
}




//check for collision and if so and is a smallerasteroid the bullet is changed to inactive and
//the asteroid is changed to destroyed.  If it is larger asteroid than the asteroid is set to
//destroyed and two new smaller asteroids are created.
//With every for loop that checks bullets the bullet is checked to be inactive and if it is then
//the loop continues which means the for loop is run again with the next index.
void checkCollisionsaAllBulletsWithAnAsteroids( )
{

	
	for (std::size_t j = 0; j <  asteroidCollection.size(); j++)
	{
		

		if (asteroidCollection[j].GetActivate() != onscreen )
		{
			continue;
		}

		for (int i = 0; i < LevelObj::GetMaxNumBullets(); i++)
		{


			if (!bullets[i].GetIsactive())
			{
				continue;
			}




			//did they collide?
			if (bullets[i].Intersects(asteroidCollection[j]))
			{
				



				//bullet is used and not active until refired
				bullets[i].SetIsactive(false);
				
				//asteroid is destroyed and is used later after level is passed in advanceLevelByOne 
				asteroidCollection[j].SetActivate(destroyed);



				//This is the diference of the two different sized asteroids when they are hit.  
				//Remember so far the enumeration difference is just two : smaller and 
				//larger asteroid
				if (asteroidCollection[j].GetAsteroidType() == larger)
				{
					//passes in the index of the larger asteroid and than activates two small asteroids 
					createSmallerAsteroids(j);

					
					
					Thescore.AddToScore(40);
					Thescore.DrawScore();

				
				}
				else if (asteroidCollection[j].GetAsteroidType() == smaller)
				{
					Thescore.AddToScore(60);
					Thescore.DrawScore();
				}
				
				break;

			}
		//second for loop brace
		
			
		}

	//first for loop brace
	}

		
}




int shoot() 
{

	

	
	
	
 	 int Numofbulletindex = -1;
	

		//static function
 		for (int i = 0; i < LevelObj::GetMaxNumBullets(); i++)
		{

			//if bullet already active go to for loop at next index
			if (bullets[i].GetIsactive())
			{
				continue;
			}

			Numofbulletindex = i;

			//bullet was inactive now is active (was off screen)
			//will be set to : bullets[i].SetIsactive(true);
			break;

		}

		//there was no free bullet for shooting, leaves function
		if (Numofbulletindex < 0)
		{
			return(-1);
		}


		//to make all the following member function simpler to look at, uses bulletIndex instead
		Bullet & bulletIndex = bullets[Numofbulletindex];


			
		
		//up key pressed direction of bullet will be upwards.  creates a bullet the same amount 
		//away for each off the four directions shot
		//for now, the bullets width is 16 and its height is 16.  values are divided by 2 to center the diferent images
			if (shipObject.GetDirection() == up)
			{


				//to make easier to understand
				float Centershipwidth = .5* shipObject.GetWidth();
				float Centerbulletwidth = .5* bulletIndex.GetWidth();
				

				
				//bullet positioned at  center of ship horizontally
				bulletIndex.SetX(shipObject.GetX() + Centershipwidth - Centerbulletwidth);
				
				//bullet starts a bit under the ship
				
				bulletIndex.SetY(shipObject.GetY() - 10);


				//for interpolation in main game loop
				bulletIndex.SetPrevX(bulletIndex.GetX());
				bulletIndex.SetPrevY(bulletIndex.GetY());

				//same direction as ship
				bulletIndex.SetDirection(shipObject.GetDirection());
				
				//there are three speeds so far: bullet, ship, and asteroids
				//sets bullet speed to downward 7 per cycle.
				bulletIndex.SetDeltaX(0);
				bulletIndex.SetDeltaY(-7);
				bulletIndex.SetIsactive(true);





				

			}
			

			else if (shipObject.GetDirection() == right) 
			{

				
				float Centershipheight = .5* shipObject.GetHeight();
				float Centerbulletheight = .5* bulletIndex.GetHeight();
				

				//bullet a bit under ship (horizontally)
				bulletIndex.SetX(shipObject.GetX() + shipObject.GetWidth() - 10);
				//bullet centered from ship vertically
				bulletIndex.SetY(shipObject.GetY() + Centershipheight - Centerbulletheight);

				//bullet a bit under ship (horizontally)
				bulletIndex.SetPrevX(bulletIndex.GetX());
				//bullet centered from ship vertically
				bulletIndex.SetPrevY(bulletIndex.GetY());




				//same direction as ship
				bulletIndex.SetDirection(shipObject.GetDirection());
				

				//sets bullet x speed at a change of 5.
				bulletIndex.SetDeltaX(7);
				bulletIndex.SetDeltaY(0);
				bulletIndex.SetIsactive(true);
				

			}
			//ship is moving downward 
			else if (shipObject.GetDirection() == down) 
			{

				float Centershipwidth = .5* shipObject.GetWidth();
				float Centerbulletwidth = .5* bulletIndex.GetWidth();
				

				//bullet is centered on ship horizontally
				bulletIndex.SetX(shipObject.GetX() + Centershipwidth - Centerbulletwidth);
				//bullet a bit under vertically
				bulletIndex.SetY(shipObject.GetY() + shipObject.GetHeight() - 10 );
				
				//bullet is centered on ship horizontally
				bulletIndex.SetPrevX(bulletIndex.GetX());
				//bullet a bit under vertically
				bulletIndex.SetPrevY(bulletIndex.GetY());

				
				
				
				//direction for move bullet
				bulletIndex.SetDirection(shipObject.GetDirection());
				
				bulletIndex.SetDeltaX(0);
				//sets change of speed to 7 for each cycle through
				bulletIndex.SetDeltaY(7);
				bulletIndex.SetIsactive(true);
				

			}
			//ship is moving left so bullet will be left of ship
			else if (shipObject.GetDirection() == left) 
			{

				
				float Centershipheight = .5* shipObject.GetHeight();
				float Centerbulletheight = .5* bulletIndex.GetHeight();

				//bullet a bit under horizontal of ship
				bulletIndex.SetX(shipObject.GetX()  - 10 );
				//bullet centered vertically on shiop
				bulletIndex.SetY(shipObject.GetY() + Centershipheight  - Centerbulletheight);

				//bullet a bit under horizontal of ship
				bulletIndex.SetPrevX(bulletIndex.GetX());
					//bullet centered vertically on shiop
				bulletIndex.SetPrevY(bulletIndex.GetY());

				//same direction as ship
				bulletIndex.SetDirection(shipObject.GetDirection());
				
				//change is 7 per cycle of main
				bulletIndex.SetDeltaX(-7);
				bulletIndex.SetDeltaY(0);
				bulletIndex.SetIsactive(true);
				


			}

		

			return(1);
}

//move the bullets and if still on screen draw them
void moveBullets() 
{

	
	//static function
	for (int i = 0; i < LevelObj::GetMaxNumBullets(); i++)
	{

		if (bullets[i].GetIsactive()) 
		{
			
			//changes x and y for detection of collision and offscreen and positioning
			bullets[i].SetX(bullets[i].GetX() + bullets[i].GetDeltaX());
			bullets[i].SetY(bullets[i].GetY() + bullets[i].GetDeltaY());

			//for interpolation
			bullets[i].SetPrevX(bullets[i].GetX());
			bullets[i].SetPrevY(bullets[i].GetY());

			
			checkForBulletOffscreen(i);
			
		
		}
	}


	
}



////////////////////////////////

//position bullet without drawing uses inteplation
void positionBulletsAndDraw(int interpolation)
{

	

	//static function
	for (int i = 0; i < LevelObj::GetMaxNumBullets(); i++)
	{

		if (bullets[i].GetIsactive())
		{



			bullets[i].GetBulletImage().setPosition(bullets[i].GetPrevX() + ((bullets[i].GetX() - bullets[i].GetPrevX())* interpolation),
				bullets[i].GetPrevY() + ((bullets[i].GetY() - bullets[i].GetPrevY()) * interpolation));



		}
	}


}




















///////////////////////////////////







//if the bullet is off the screen it is set as inactive so that it will not be drawn
//The drawing function will check to see if the bullet is still active.  The screenWidth 
//and screenHeight is used to check if the image is totally off the screen!
void checkForBulletOffscreen(int index) 
{
	//is bullet not on screen?
	if (!(bullets[index].IntersectsWithScreenRect(G_SCREEN_WIDTH, G_SCREEN_HEIGHT)))
	{
		//bullet is not on screen
		bullets[index].SetIsactive(false);
		
	}
	//bullet is on screen
	
}

//The function checks if the asteroid is totally off the screen. If it is the asteroid 
//is set as offscreen which means it is not being drawn.  Later we look at the activation of
//offscreen to reinitialize and set back to onscreen so that it will be drawn.
void checkForAsteroidOffScreen()
{

	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		//if offsecreen totally...
		if (!(asteroidCollection[i].IntersectsWithScreenRect( G_SCREEN_WIDTH, G_SCREEN_HEIGHT)))
		{
			

			asteroidCollection[i].SetActivate(offscreen);
		}

	}
	
}

//checks if ship is at passed or on one of the four borders.  If so places at border's edge.  
bool checkForShipOnBorder(sf::Vector2f Tempvar)
{


	//left
	if (Tempvar.x < 0 )
	{
		shipObject.SetX(0);
		shipObject.SetPrevX(0);
		
		return(false);

	}
	//right
	if (Tempvar.x  > (G_SCREEN_WIDTH - shipObject.GetWidth())) 
	{
		shipObject.SetX(G_SCREEN_WIDTH - shipObject.GetWidth());
		shipObject.SetPrevX(G_SCREEN_WIDTH - shipObject.GetWidth());
		
		return(false);

	}
	//bottom
	if (Tempvar.y > (G_SCREEN_HEIGHT - shipObject.GetHeight()))
	{
		shipObject.SetY(G_SCREEN_HEIGHT - shipObject.GetHeight());
		shipObject.SetPrevY(G_SCREEN_HEIGHT - shipObject.GetHeight());
		return(false);

	}
	//top
	if (Tempvar.y < 0 ) 
	{
		shipObject.SetY(0);
		shipObject.SetPrevY(0);
		return(false);

	}


	return(true);
}


//shutdown with an exitnumber for debugging
void shutdown(int exitNum) 
{

	exit(-11);

}


//fills the asteroid vector with initialized asteroids. asterType is the type of the asteroid.
void fillAsteroidVector(int numAsteroid,  int width, int height, asteroidType Astertype,  sf::Texture & Texture) {

	// for random direction
	
	//g_TotalAsteroids is the total number of asteroids : already created plus newly added that we are adding
	//right now
	int g_TotalAsteroids = g_TotalNumAllAsteroids + numAsteroid;

	//g_TotalNumAllAsteroids increases whenever ther is a new asteroid creation 
	//(from push_back)
	for (std::size_t i = asteroidCollection.size(); i < g_TotalAsteroids; i++)
	{
		g_TotalNumAllAsteroids++;

		//large asteroids are initialized for movement (there at on of the four sides and ready
		//for movement.)  Where there activeness is set to onscreen.  The small asteroids have not 
		//been created on the main monitor sceen (two for each large asteroid that is destroyed)
		//they are initialized with 'initialized' and is changed to 'onscreen' in createSmallAsteroid
		//function when created.
		if (Astertype == smaller)
		{
			asteroidCollection.push_back(Asteroid(width, height, Texture, smaller));
			//readies for onscreen usage in createSmallerAsteroid which sets deltax and deltay and whichdirection
			asteroidCollection[i].SetActivate(initialized);
		}
		else if (Astertype == larger)
		{
			//generated is 0 through three for starting direction on screen : top, right, bottom, left
			int j = rand() % 4;
			//asteroid now calls constructor 
			asteroidCollection.push_back(Asteroid(width, height, Texture, larger));
			//sets deltax and deltay and which direction, and activation
			asteroidCollection[i].SetInitialAsteroid(j);
		}

	}


}

// indexOfAsteroid is the index of the large asteroid that has been shot with a bullet and
// is being replaced on the screen with the two smaller asteroids that are to be activate
// (onscree) here.  They were set to intialize in fillAsteroidVectors and refillAsteroidVectors.
// Called from checkCollisionsaAllBulletsWithAnAsteroids.
int createSmallerAsteroids(int indexOfAsteroid)
{
	
	
	//for checking if both small asteroids can be created.
	int Flagunusedasteroidindexfound = 0;
	
	//to hold the two asteroids index
	int Indexnextsmallerasteroid1 = 0;
	int Indexnextsmallerasteroid2 = 0;

	
	//checks for first availbable index
	for (std::size_t i = 0 ; i < asteroidCollection.size(); i++)
	{
		

		//small asteroids are initialized as onscreen because they were initailized 
		if (asteroidCollection[i].GetActivate() == initialized)
		{

			
			Flagunusedasteroidindexfound++;
			Indexnextsmallerasteroid1 = i;
			//their ready for moving and drawing
			asteroidCollection[i].SetActivate(onscreen);
			//unused asteroid found and breaking out of loop 
			break;
		}
	}


	//Checks for second available index
	for (std::size_t j = 0; j < asteroidCollection.size(); j++)
	{


		//small asteroids are initialized as onscreen because they were set as "initialized"
		//in fillAsteroidVectors() or refillAsteroidVectors()
		if (asteroidCollection[j].GetActivate() == initialized)
		{

			//found an unused asteroid, records indes and sets as onscreen
			Flagunusedasteroidindexfound++;
			Indexnextsmallerasteroid2 = j;

			//their ready for moving and drawing
			asteroidCollection[j].SetActivate(onscreen);
			
			//unused asteroid found and breaking out of loop 
			break;


		}
	}
	
	//somethings wrong, this function was called and there are no 2 new asteroids readied
	//as initialized
	if (Flagunusedasteroidindexfound != 2)
	{
		exit(-5);
	}
	
	
	
	
	

	//diameter of smaller circle is 32
	//The larger asteroid in the remaining code is the asteroidCollection with the index : indexOfAsteoid
	//the center of little asteroid is located with it's center on the top horizontal tangent of larger asteroid
	//or on the lower horizontal tangent of the large asteroid.
	//
	//to simplify the four assignments of x and y below these intermediate statements:
	
	int largeAsteroidLeft = asteroidCollection[indexOfAsteroid].GetX();
	int largeAsteroidWidth = asteroidCollection[indexOfAsteroid].GetWidth();
	int largeAsteroidHeight = asteroidCollection[indexOfAsteroid].GetHeight();
	int largeAsteroidTop = asteroidCollection[indexOfAsteroid].GetY();
	int smallAsteroid1Height = (asteroidCollection[Indexnextsmallerasteroid1].GetHeight());
	int smallAsteroid2Height = (asteroidCollection[Indexnextsmallerasteroid2].GetHeight());
	int smallAsteroid1Width = (asteroidCollection[Indexnextsmallerasteroid1].GetWidth());
	int smallAsteroid2Width = (asteroidCollection[Indexnextsmallerasteroid2].GetWidth());
	


	//The position of the two small asteroids are as follows:
	//the small asteroids midpoint is located on the large asteroids two horizontal tangents, one small
	//asteroid on the top and one asteroid on bottom.
	
	//The math here is interesting: the width of the larger asteroid minus the width of the smaller 
	//asteroid leaves us with the remaining width space on both the right and left of the small asteroid.
	//We than divide this space by two to get the smaller asteroid positioned at the center horizontally.
	//if needed, easier to draw out on paper.

	//small asteroid's center is located on the horizontal tangent of large asteroid top.
	asteroidCollection[Indexnextsmallerasteroid1].SetX(largeAsteroidLeft + ((largeAsteroidWidth - (smallAsteroid1Width / 2))));
	asteroidCollection[Indexnextsmallerasteroid1].SetY(largeAsteroidTop  - (smallAsteroid1Height / 2));

	
	//small asteroid's center is on the horizontal tangent of the bottom large asteroid.
	asteroidCollection[Indexnextsmallerasteroid2].SetX(largeAsteroidLeft + ((largeAsteroidWidth - (smallAsteroid2Width / 2))));
	asteroidCollection[Indexnextsmallerasteroid2].SetY(largeAsteroidTop + ((largeAsteroidHeight - (smallAsteroid2Height / 2))));

	

	


	//initializations for set previous position right below.
	float x1 = asteroidCollection[Indexnextsmallerasteroid1].GetX();
	float y1 = asteroidCollection[Indexnextsmallerasteroid1].GetY();
	float x2 = asteroidCollection[Indexnextsmallerasteroid2].GetX();
	float y2 = asteroidCollection[Indexnextsmallerasteroid2].GetY();
	
	
	//copies the small asteroids values to the previous variables for the interpolation.
	asteroidCollection[Indexnextsmallerasteroid1].SetPrevX(x1);
	asteroidCollection[Indexnextsmallerasteroid1].SetPrevY(y1);

	asteroidCollection[Indexnextsmallerasteroid2].SetPrevX(x2);
	asteroidCollection[Indexnextsmallerasteroid2].SetPrevY(y2);



	
	
	//get direction of large asteroid for use in determining small asteroids deltaX and deltaY
	asteroidMovement majorDirection = asteroidCollection[indexOfAsteroid].GetWhichDirection();
	//local objects for use of passing in below by reference
	asteroidMovement newDirection1= directions[0][0];
	asteroidMovement newDirection2 = directions[0][0];
	
	//Calls by reference so new direction variables can be used again.  The new directions are
	//for the small asteroids and are determined by the larger asteroids direction in this function call.
	getTwoDirectionsFromMajorDirection(majorDirection, newDirection1, newDirection2);
	
	
	
	//indexNextSmallerAsteroid1 is the index of the small asteroid position that is higher than
	//indexNextSmallerAsteroid2.  This furthor indicates that newDirection1 is higher on screen
	//than newDirection2 (one asteroid above and one asteroid below.)

	asteroidCollection[Indexnextsmallerasteroid1].SetDeltaWithDirection(newDirection1);
	asteroidCollection[Indexnextsmallerasteroid2].SetDeltaWithDirection(newDirection2);
	

	

	
}

//Checks if all large and small asteroids are destroyed 
bool checkAllAsteroidsDestroyed()
{

	int Asteroidcount = 0;
	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		if (asteroidCollection[i].GetActivate() == destroyed)
		{
			Asteroidcount++;
			
		
		}
		else
		{
			break;
		}

	}
	if (Asteroidcount == g_TotalNumAllAsteroids)
	{
		return(true);
	}


	return(false);
}

	



//if the asteroid is onscreen it is either a large asteroid that is initialized 
//or reinitialized which means its waiting on the border to be drawn and moved.
//It could also be on the screen ..."onscreen"
//if it is a small asteroid it is onscreen if it has been created with :
//createsmallasteroids.
void moveAsteroids()
{

	

	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		if (asteroidCollection[i].GetActivate() == onscreen)
		{

			

			asteroidCollection[i].MoveAsteroid();

			
			


		}


	}


	
}

//Not used anymore but still useful.  Doesn't draw just sets position using interpolation
void positionAsteroidsAndDraw(int interpolation)
{
	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		if (asteroidCollection[i].GetActivate() == onscreen)
		{

			
			asteroidCollection[i].GetSprite().setPosition(asteroidCollection[i].GetPrevX() + ((asteroidCollection[i].GetX() - asteroidCollection[i].GetPrevX())* interpolation),
			asteroidCollection[i].GetPrevY() + ((asteroidCollection[i].GetY() - asteroidCollection[i].GetPrevY()) * interpolation));

			
			

		}


	}

}


//check for all asteroids offscreen and set them up for moving putting them 
//flush against borders
void reinitializeOffscreenAsteroids()
{
	
	

	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{
		if (asteroidCollection[i].GetActivate() == offscreen)
		{
			
			int Randnum = rand() % 4;
			//resets asteroid to onscreen for draw and move.
			//this is used for both large and small asteroids and is not the same
			//as when (two) asteroids are created in the createSmallerAsteroids called
			//in checkCollisionsAllBullets...
			//this sets deltax, deltay, whichdirection, and activation
			asteroidCollection[i].SetInitialAsteroid(Randnum);
		}

	}
	
}


//fills vector with numOfBullets and fills the vector.  Lastly, sets 
//the static variaable.
void fillBulletVector (int numOfBullets, sf::Texture & Texture)
{

	
	
	for (int i = 0; i < numOfBullets  ; i++)
	{
		///height than width
		bullets.push_back( Bullet(Texture, 16, 16));
	
	}

	

	
}
//set all asteroids for interpolation in main loop 
void setAllAsteroidsPrev()
{

	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		if (asteroidCollection[i].GetActivate() == onscreen)
		{
			asteroidCollection[i].SetPrevX(asteroidCollection[i].GetX());
			asteroidCollection[i].SetPrevY(asteroidCollection[i].GetY());


		}
	}

}










///////////////////////////////





int main(void)
{



//window.setVerticalSyncEnabled(true);


// All four for interpolation at end of game loop.
const float Tickspersecond = 30.f;
const float SKIP_TICKS = 1000.f / Tickspersecond;
sf::Clock Mainclock;
float Interpolation = 0;


	
	

	

	

//seeds the time for random direction and postion of asteroids right before drawing on screen
std::srand(time(NULL));

//gets rid of extra window
FreeConsole();


if (!Largertextureasteroid.loadFromFile("largerasteroid.png"))
{
	shutdown(-2);
}


if (!Smallertextureasteroid.loadFromFile("smallerasteroid.png"))
{
	shutdown(-3);
}


if (!Texturebullet.loadFromFile("bullet.png"))
{
	shutdown(-4);
}


if (!Fontforscore.loadFromFile("ARIALBD.ttf"))
{
	shutdown(-5);
}



//new amounts of new asteroids are set in getNumSmallAsteroids() and getNumLargeAsteroids
//this will setlevelto one because it is zero before call.
levelObject.AdvanceLevelByOne();





//create vector fills the object with a random entry border (0-3)
//Uses setInitialAsteroid. third and fourth argument is width and than height

//creates vector with asteroids - order (large and small) is not important
fillAsteroidVector(levelObject.GetNumLargeAsteroids(), 64, 64, larger, Largertextureasteroid);
fillAsteroidVector(levelObject.GetNumSmallAsteroids(), 32, 32, smaller, Smallertextureasteroid);


//this will set the vector to 10 bullets index  of 9 of course
fillBulletVector(levelObject.GetMaxNumBullets(), Texturebullet);
Thescore.SetFont(Fontforscore);

//initial ship draw
drawShip();




//for interpolation (smooth motion)  is advanced by SKIP_TICKS and checked in loop below.
double Nexttick = Mainclock.restart().asMilliseconds();

	while (window.isOpen())
	{
		
		

		
			
			
			

			while (window.pollEvent(event))
			{

				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				
				if (event.type == sf::Event::KeyPressed)
				{
					//shoots at asteroid
					if (event.key.code == sf::Keyboard::Space)
					{
						shoot();
					}
					else if (event.key.code == sf::Keyboard::N)
					{
						shipObject.RotateShipCClock();

					}
					else if (event.key.code == sf::Keyboard::M)
					{
						shipObject.RotateShipClock();
					}



				}



			}

			//timer used for interpolation
			while (Mainclock.getElapsedTime().asMilliseconds() > Nexttick)
			{



				// sets all position varibles to prevpostion for interpolation near end of main loop
				setAllAsteroidsPrev();
				setAllBulletsPrev();
				shipObject.SetPrevX(shipObject.GetX());
				shipObject.SetPrevY(shipObject.GetY());



				

			//checks keyboard and if pressed calls moveship with the deltas otherwise calls moveship
			//with - 1 which causes sliding effect
			if (checkKeyboard() == false)
			{

				
				//also checks if movement would be beyond border 
				moveShip(-1);
				
				
			}

			

			
			//if the asteroids are not on the screen they will not be moved
			//put before collision checks so that new asteroids created will be a blit without movement
			//and there prev is set within to the same as there positioning variable

			moveAsteroids();

			moveBullets();

			
			
			
			checkCollisionsShipWithAsteroids();


			checkCollisionsaAllBulletsWithAnAsteroids();


			
			
			

			

			


		


		//if true is returned than all those asteroids are destroyed and reinitializeation and new asteroids are created
		//and a new level is started
		if (checkAllAsteroidsDestroyed() == true)
		{

			//holds this levels value because they are changed in advanceLevelByOne for RefillAsteroidVector
			int Oldlevelssmallasteroidamt = levelObject.GetNumSmallAsteroids();
			int Oldlevelslargeasteroidamt = levelObject.GetNumLargeAsteroids();


			//remove bullets from screen by way of status
			for (std::size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].SetIsactive(false);
			}
			//removes asteroids from screen by way of status
			for (std::size_t i = 0; i < asteroidCollection.size(); i++)
			{
				asteroidCollection[i].SetActivate(destroyed);
				

			}

			
			



			//new amounts of new asteroids are set in numofsmallasteroids and numoflargeasteroids
			//this function can shutdown program
			levelObject.AdvanceLevelByOne();








			//fills one asteroid collection with two statements.
			//numofsmallasteroids and numoflargeasteroids are new levels values
			//the new levels minus the old levels gives us the new asteroids to create
			int createThisAmtAsteroids = (levelObject.GetNumLargeAsteroids() - Oldlevelslargeasteroidamt);
			//creates the newly created asteroids with push_back and reinitializes the older asteroids
			//with a new active setting - 
			refillAsteroidVectors(createThisAmtAsteroids, 64, 64, larger, Largertextureasteroid);
			//see right above
			createThisAmtAsteroids = levelObject.GetNumSmallAsteroids() - Oldlevelssmallasteroidamt;
			//same as above : just a smaller asteroid group for the collection
			refillAsteroidVectors(createThisAmtAsteroids, 32, 32, smaller, Smallertextureasteroid);


		}


		//sets asteroids to offscreen if they are
		checkForAsteroidOffScreen();


		//check for all asteroids offscreen and if so set them up for moving at the four screen borders
		reinitializeOffscreenAsteroids();


		//initial score text is drawn here until there is a score and than set and drawm elsewhere
		//(checkCollisionWithAllBullets...)
		if (Thescore.GetScore() == 0)
		{
			Thescore.DrawScore(0);
		}



		

	
	
		   
		
			












/////////////////////////////////////////

		//Used for interpolation - loop runs once every 0.033 seconds.
		Nexttick += SKIP_TICKS;

		

		}



		
		
		
		
		

			

		window.clear();
		window.draw(Thescore.getTextMessage());


		//sets interpolation varicable for non stuttering effect (smooth)
		Interpolation = float(((Mainclock.getElapsedTime().asMilliseconds() + SKIP_TICKS) - (Nexttick)) / (SKIP_TICKS));



		//commented out for testing:
		//shipObject.GetShipImage().setPosition(spx + ((sx - spx) * interpolation), spy + ((sy - spy) * interpolation));
		//shipObject.GetShipImage().setPosition(shipObject.GetX(), shipObject.GetY());//(shipObject.GetPrevY() + ((shipObject.GetY() - shipObject.GetPrevY()) * interpolation)));

		//interpolates ship image
		shipObject.GetShipImage().setPosition(shipObject.GetPrevX()  + ((shipObject.GetX() - shipObject.GetPrevX())*Interpolation),
		shipObject.GetPrevY() + ((shipObject.GetY() - shipObject.GetPrevY()) * Interpolation));


		

		
		

		//interpolate all the asteroid's movement
		for (std::size_t i = 0; i < asteroidCollection.size(); i++)
		{

			if (asteroidCollection[i].GetActivate() == onscreen)
			{


				Interpolation = float(((Mainclock.getElapsedTime().asMilliseconds() + SKIP_TICKS) - (Nexttick)) / (SKIP_TICKS));
				

				//interpolation asteroids movement		
				asteroidCollection[i].GetSprite().setPosition(asteroidCollection[i].GetPrevX() + ((asteroidCollection[i].GetX() - asteroidCollection[i].GetPrevX())* Interpolation),
				asteroidCollection[i].GetPrevY() + ((asteroidCollection[i].GetY() - asteroidCollection[i].GetPrevY()) * Interpolation));

				//just in case needed for testing purposes
				//asteroidCollection[i].GetSprite().setPosition(sf::Vector2f(asteroidCollection[i].GetX(), asteroidCollection[i].GetY()));

				window.draw(asteroidCollection[i].GetSprite());


			}


		}



		
		


		//interpolate all the bullets movement
		for (int i = 0; i < LevelObj::GetMaxNumBullets(); i++)
		{

			if (bullets[i].GetIsactive())
			{

				Interpolation = float(((Mainclock.getElapsedTime().asMilliseconds() + SKIP_TICKS) - (Nexttick)) / (SKIP_TICKS));

				//sets the position
				bullets[i].GetBulletImage().setPosition(bullets[i].GetPrevX() + ((bullets[i].GetX() - bullets[i].GetPrevX())* Interpolation),
					bullets[i].GetPrevY() + ((bullets[i].GetY() - bullets[i].GetPrevY()) * Interpolation));

				window.draw(bullets[i].GetBulletImage());

			}
		}

		
		
		window.draw(shipObject.GetShipImage());


		
		
		
		window.display();

		
	}

	return 0;
}






//pushes the new asteroids for the new level if either small or large
//than reinitializes their deltax and deltay and their direction and x and y
//in setInitialAsteroid
void refillAsteroidVectors(int numAsteroidsToCreate, int width, int height, asteroidType Type , sf::Texture & Texture)
{
	
	if (Type == larger)
	{
		for (int i = 0; i < numAsteroidsToCreate; i++)
		{
			//create the new additional asteroids 
			asteroidCollection.push_back(Asteroid(width, height, Texture, larger));
			g_TotalNumAllAsteroids++;
		}
		//Checks all even newly created and sets all the values
		for (std::size_t i = 0; i < asteroidCollection.size(); i++)
		{
			if (asteroidCollection[i].GetAsteroidType() == larger)
			{
				int j = rand() % 4;
				//sets deltax and deltay, x and y, direction, and activation
				asteroidCollection[i].SetInitialAsteroid(j);
			}
		}

	}
	else if (Type == smaller)
	{
		for (int i = 0; i < numAsteroidsToCreate; i++)
		{
				//creates extra small asteroids
				asteroidCollection.push_back(Asteroid(width, height, Texture, smaller));
				g_TotalNumAllAsteroids++;
		}
		//reinitalizes the old and new asteroids with the new activation so that they
		//can be moved after their changed from initialized to onscreen in createsmallasteroids
		for (std::size_t i = 0; i < asteroidCollection.size(); i++)
		{

			if (asteroidCollection[i].GetAsteroidType() == smaller)
			{
				
				asteroidCollection[i].SetActivate(initialized);
			}
		}
	}

	
}

	


//Takes one direction from a large asteroid and returns the two new directions of small asteroid by reference
void getTwoDirectionsFromMajorDirection(asteroidMovement & Themajordirection, asteroidMovement & Smallasteroiddirection1, asteroidMovement & Smallasteroiddirection2)
{

	//the smallasteroiddirectio1 is always higher than the smallasteroidirection2
	//it is passed in as newdirection1 and newdirectio2.  newdirection1 is also higher  
	//than newDirection2 on the screen.  Easy to understand how the small asteroids are
	//moving with regards to large asteroid (Themajordirection)
	switch (Themajordirection) {


	case asteroidMovement::UP:
		Smallasteroiddirection1 = asteroidMovement::UP_RIGHT;
		Smallasteroiddirection2 = asteroidMovement::UP_LEFT;
		break;
	case asteroidMovement::DOWN:
		Smallasteroiddirection1 = asteroidMovement::DOWN_LEFT;
		Smallasteroiddirection2 = asteroidMovement::DOWN_RIGHT;
		break;
	case asteroidMovement::LEFT:
		Smallasteroiddirection1 = asteroidMovement::UP_LEFT;
		Smallasteroiddirection2 = asteroidMovement::DOWN_LEFT;
		break;
	case asteroidMovement::UP_LEFT:
		Smallasteroiddirection1 = asteroidMovement::UP;
		Smallasteroiddirection2 = asteroidMovement::LEFT;
		break;
	case asteroidMovement::DOWN_LEFT:
		Smallasteroiddirection1 = asteroidMovement::DOWN;
		Smallasteroiddirection2 = asteroidMovement::LEFT;
		break;
	case asteroidMovement::RIGHT:
		Smallasteroiddirection1 = asteroidMovement::UP_RIGHT;
		Smallasteroiddirection2 = asteroidMovement::DOWN_RIGHT;

		break;
	case asteroidMovement::UP_RIGHT:
		Smallasteroiddirection1 = asteroidMovement::UP;
		Smallasteroiddirection2 = asteroidMovement::RIGHT;
		break;
	case asteroidMovement::DOWN_RIGHT:
		Smallasteroiddirection1 = asteroidMovement::DOWN;
		Smallasteroiddirection2 = asteroidMovement::RIGHT;
		break;

	default:
		break;
	}
}

//sets bullets for interpolation in main loop
void setAllBulletsPrev()
{

	for (std::size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].GetIsactive())
		
		{
			bullets[i].SetPrevX(bullets[i].GetX());
			bullets[i].SetPrevY(bullets[i].GetY());


		}
	}

}

