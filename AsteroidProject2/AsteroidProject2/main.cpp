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




//global variables g_NumOfLargerAsteroids must be two times as many small asteroids: g_NumOfSmallerAsteroids
//level that game is on : starts at 0, increase in level causes more asteroids
int g_Level = 0;
int g_NumOfLargerAsteroids = 1;
int g_NumOfSmallerAsteroids = g_NumOfLargerAsteroids * 2;
//used to break out of while, when is set 
int g_Shutdownflag = 0;
int g_TotalNumAllAsteroids = 0;




//GLOBAL FUNCTION DECLARATIONS
int drawShip();
int moveShip(int amountForMovem, int keyPressed);
int checkkeyboard();
int checkCollisionsShipWithAsteroids();
int checkCollisionsaAllBulletsWithAnAsteroids();
int shoot(void);
int movebullets(void);
int checkForBulletOffscreen(int index);
int checkForAsteroidOffScreen();
int checkForShipOnBorder(int x, int y);
void shutdown(int exitNum);
int fillAsteroidVector(int numOfAsteroid , int theWidth, int theHeight, asteroidType theAsteroidType, sf::Texture & theTexture);
int createSmallerAsteroids(int indexOfAsteroid, sf::Texture smallerTextureAstroid);
int checkAllAsteroidsDestroyed();
int startNextLevel(void);
int moveasteroids();
int reinitializeOffscreenAsteroids();
int fillBulletVector(int numberOfBullets, sf::Texture & textureOfBullet);
int refillAsteroidVectors(int createThisManyAsteroids, int theWidth, int theHeight, asteroidType asteroidType, sf::Texture & theTexture);
void getTwoDirectionsFromMajorDirection(asteroidMovement & theMajorDirection, asteroidMovement & smallAsteroidDirection1, asteroidMovement & smallAsteroidDirection2);



/////////!!!!!!!!!!!!!!!!!!


//put here together because smallerTextureAsteroid used in: checkCollisionsaAllBulletsWithAnAsteroid 
sf::Texture largerTextureAsteroid;
sf::Texture smallerTextureAsteroid;
sf::Texture texturebullet;
sf::Font fontForScore;

//initialized of the vectors for asteroids
std::vector<asteroid> asteroidCollection;
std::vector<asteroid> largerAsteroidObject;
std::vector<asteroid> smallerAsteroidObject;
std::vector <bullet> bullets;
score theScore(10, 10);
sf::Event event;
sf::RenderWindow window(sf::VideoMode(gScreenWidth, gScreenHeight), "Asteroids!");

//global ship pbject
ship shipObject(500, 500);



//GLOBAL FUNCTION DEFINITIONS FOLLOW:

int drawShip(void){


	window.draw(shipObject.shipImage);
	return(1);
}


//this function is called from keypress and main so that from every keypress there is 
//a reaction but the main also calls the move with a pressedKey set at -1 so that there
//is a gliding effect.  If the keypress is not pressed than the ship will move with
//its current deltax and deltay.  The sleep function in main controls the speed of this movement!
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
	if (pressedKey == up) { shipObject.setDeltaY(amountForMovement); }
	else if (pressedKey == down) { shipObject.setDeltaY(amountForMovement); }
	else if (pressedKey == right) { shipObject.setDeltaX(amountForMovement); }
	else if (pressedKey == left) { shipObject.setDeltaX(amountForMovement); }
	

		
	//set the change in y and the change in x variables (meaning if delta)
	int deltaX = shipObject.getDeltaX();
	int deltaY = shipObject.getDeltaY();


	//set the x and y using the delta (change of x or y) and updating the x and y values for checking 
	//for collisions and off screen
	int x = shipObject.getX();
	int y = shipObject.getY();
	x = x + deltaX;
	y = y + deltaY;


	//is off screen returns -1
	if (checkForShipOnBorder(x, y) == -1)
	{
		drawShip();
		return (-1);
	}

	shipObject.setX(x);
	shipObject.setY(y);

	
	//SFML moves to the new location changing the ships postion by these two numbers.  X and Y are 
	//still computed above though, for collisions and offscreen detection.
	shipObject.shipImage.move(sf::Vector2f(deltaX, deltaY));
	

	drawShip();

	return(1);
}


int checkkeyboard(void) 
{

	
	//this is setting the change in x and the change in y to a minimum value of negative three
	//or a maximum of postive three.  Value is set as one of these numbers. for now
	//they are set to 3 or -3.  There are two other speeds set one for asteroids and one for
	//bullets.  All together the asteroids, bullets, and ship speeds set up the relative 
	//distance-by-movement.  (they can move at different speeds!)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  { moveShip(-3, left); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { moveShip(3, right); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	 { moveShip(-3, up); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { moveShip(3, down ); }
	else
	{
		//if in here no key pressed this cycle
		return(-1);
	}

	return(1);
}


//The idea is to check if the ship is in the y-range and x-range of the asteroid
//if so there is a collision!
int checkCollisionsShipWithAsteroids() 
{


	for (int i = 0; i <= g_TotalNumAllAsteroids - 1; i++)
	{

		//checks if asteroid on screen if so is not initialized, destroyed, instantiated, or offscreen
		//so if it is onscreen enters beneath this if.  Otherwise it continues to the for loop with next value of i.
		if (asteroidCollection[i].getActivate() != onscreen )
		{
			continue;

		}
		if (shipObject.intersects(asteroidCollection[i]))
		{
			shutdown(-1);
		}
	}

		return(1);
}




//check for collision and if so and is a smallerasteroid the bullet is changed to inactive and
//the asteroid is changed to destroyed.  If it is larger asteroid than the asteroid is set to
//destroyed and two new smaller asteroids are created.
//With every for loop that checks bullets the bullet is checked to be inactive and if it is then
//the loop continues which means the for loop is run again with the next index.
int checkCollisionsaAllBulletsWithAnAsteroids( )
{


	for (int j = 0; j < g_TotalNumAllAsteroids ; j++)
	{
		

		if (asteroidCollection[j].getActivate() != onscreen )
		{
			continue;
		}

		for (int i = 0; i <= (bullet::getMaxNumBullets()-1); i++)
		{


			if (!bullets[i].getIsactive())
			{
				continue;
			}





			if (bullets[i].intersects(asteroidCollection[j]))
			{
				



				//bullet is used and not active until refired
				bullets[i].setIsactive(false);
				
				//asteroid is destroyed and is used later after level is passed (startNextLevel)
				asteroidCollection[j].setActivate(destroyed);



				//This is the diference of the two different sized asteroids when they are hit.  
				//Remember so far the enumeration difference is just two : smaller and 
				//larger asteroid
				if (asteroidCollection[j].getAsteroidType() == larger)
				{
					//passes in next number of small asteroid and than creates two
					createSmallerAsteroids(j, smallerTextureAsteroid);

					
					
					theScore.addToScore(40);
					theScore.drawScore();

				
				}
				else if (asteroidCollection[j].getAsteroidType() == smaller)
				{
					theScore.addToScore(60);
					theScore.drawScore();
				}
				
				break;

			}
		//second for loop brace
		
			
		}

	//first for loop brace
	}

		
return(1);
}




int shoot(void) 
{

	

	int i = 0;
	
	
		int numOfBulletIndex = -1;

		//static function
 		for (int i = 0; i <= (bullet::getMaxNumBullets()-1) ; i++) 
		{

			//if bullet already active go to for loop at next index
			if (bullets[i].getIsactive())
			{
				continue;
			}

			numOfBulletIndex = i;

			//bullet was inactive now is active (was off screen)
			bullets[i].setIsactive(true);
			break;

		}

		if (numOfBulletIndex < 0)
		{
			return(-1);
		}

			
		
		//up key pressed direction of bullet will be upwards.  creates a bullet the same amount 
		//away for each off the four directions shot
		//for now, the bullets width is 16 and its height is 16.  values are divided by 2 to center the diferent images
			if (shipObject.getDirection() == up)
			{

				//bullet center of ship
				bullets[numOfBulletIndex].setX(shipObject.getX() + (.5* shipObject.getWidth()) -( .5* (bullets[numOfBulletIndex].getWidth())   ));
				//bullet a bit above ship
				bullets[numOfBulletIndex].setY(-100 + shipObject.getY() + shipObject.getHeight());

			
				bullets[numOfBulletIndex].setDirection(up);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBulletIndex].bulletImage.setPosition(sf::Vector2f(bullets[numOfBulletIndex].getX(), bullets[numOfBulletIndex].getY()));

				window.draw(bullets[numOfBulletIndex].bulletImage);

				//bullet has been set here as -5, different speeds of objects make them relativly
				//faster or slower, there are three speeds so far: bullet, ship, and asteroids
				bullets[numOfBulletIndex].setDeltaX(0);
				bullets[numOfBulletIndex].setDeltaY(-5);
				bullets[numOfBulletIndex].setIsactive(true);
				

			}
			

			else if (shipObject.getDirection() == right) 
			{

				//bullet right of ships left value by 100. remember the ship has a width of 64.
				bullets[numOfBulletIndex].setX(shipObject.getX() + 100);
				//bullet a bit above ship
				bullets[numOfBulletIndex].setY((shipObject.getY() + .5*(shipObject.getHeight() - (.5*(bullets[numOfBulletIndex].getHeight())))));

			
				bullets[numOfBulletIndex].setDirection(right);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBulletIndex].bulletImage.setPosition(sf::Vector2f(bullets[numOfBulletIndex].getX(), bullets[numOfBulletIndex].getY()));

				window.draw(bullets[numOfBulletIndex].bulletImage);

				//sets bullet x speed at a change of 5.
				bullets[numOfBulletIndex].setDeltaX(5);
				bullets[numOfBulletIndex].setDeltaY(0);
				bullets[numOfBulletIndex].setIsactive(true);
				

			}
			//ship is moving downward 
			else if (shipObject.getDirection() == down) 
			{
				//bullet is centered according to ship
				bullets[numOfBulletIndex].setX(shipObject.getX() + .5*(shipObject.getWidth() - (.5* (bullets[numOfBulletIndex].getWidth()))));
				//bullet a bit above ship
				bullets[numOfBulletIndex].setY(100 + shipObject.getY());
				//direction for move bullet
				bullets[numOfBulletIndex].setDirection(down);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBulletIndex].bulletImage.setPosition(sf::Vector2f(bullets[numOfBulletIndex].getX(), bullets[numOfBulletIndex].getY()));
				//bullet image is part of SFML basic instructions on website tutorial questions
				window.draw(bullets[numOfBulletIndex].bulletImage);
				bullets[numOfBulletIndex].setDeltaX(0);
				//sets change of speed to 5 for each cycle through
				bullets[numOfBulletIndex].setDeltaY(5);
				bullets[numOfBulletIndex].setIsactive(true);
				

			}
			//ship is moving left so bullet will be left of ship
			else if (shipObject.getDirection() == left) 
			{

				//ships midpoint is used to center bullet
				bullets[numOfBulletIndex].setX(shipObject.getX() - 100 + (shipObject.getWidth()));
				//bullet a bit above ship
				bullets[numOfBulletIndex].setY((.5 * shipObject.getHeight()) + shipObject.getY() - (.5*( bullets[numOfBulletIndex].getHeight())) );

				//direction set to left for moving/drawing bullet
				bullets[numOfBulletIndex].setDirection(left);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBulletIndex].bulletImage.setPosition(sf::Vector2f(bullets[numOfBulletIndex].getX(), bullets[numOfBulletIndex].getY()));

				window.draw(bullets[numOfBulletIndex].bulletImage);
				//change is 5 per cycle of main
				bullets[numOfBulletIndex].setDeltaX(-5);
				bullets[numOfBulletIndex].setDeltaY(0);
				bullets[numOfBulletIndex].setIsactive(true);
				


			}

		

			return(1);
}

//move the bullets and if still on screen draw them
int movebullets(void) 
{

	int returnValue = 0;

	//static function
	for (int i = 0; i <= bullet::getMaxNumBullets()-1; i++)
	{

		if (bullets[i].getIsactive()) 
		{
			//changes the postion for the draw function in this function
			bullets[i].bulletImage.move(sf::Vector2f(bullets[i].getDeltaX(), bullets[i].getDeltaY()));

			//changes x and y for detection of collision and offscreen
			bullets[i].setX(bullets[i].getX() + bullets[i].getDeltaX());
			bullets[i].setY(bullets[i].getY() + bullets[i].getDeltaY());

			
			returnValue = checkForBulletOffscreen(i);
			
			//bullet not offscreen
			if (returnValue == 1)
			{
				//SFML code from web site tutorial
				window.draw(bullets[i].bulletImage);
			}
		}
	}


	return(1);
}

//if the bullet is off the screen it is set as inactive so that it will not be drawn
//The drawing function will check to see if the bullet is still active.  if the bullet
//is offscreen than a return of -1 means that the bullet will not be drawn in the movebullets
//function.  The screenWidth and screenHeight is used to check if the image is totally off the screen!
int checkForBulletOffscreen(int index) 
{

	if (!(bullets[index].intersectsWithScreenRect(gScreenWidth, gScreenHeight)))
	{
		bullets[index].setIsactive(false);
		return(-1);
	}
	
	return(1);
}

//The function checks if the asteroid is totally off the screen. If it is the asteroid 
//is set as offscreen which means it is not being drawn.  Later we look at the activation of
//offscreen to reinitialize and set back to onscreen so that it will be drawn.
int checkForAsteroidOffScreen()
{

	for (int i = 0; i <= (g_TotalNumAllAsteroids-1); i++)
	{


		if (!(asteroidCollection[i].intersectsWithScreenRect( gScreenWidth, gScreenHeight)))
		{

			asteroidCollection[i].setActivate(offscreen);
		}

	}
	return(1);
}

//checks if ship is at passed or on one of the four borders.  If it does, sets ship  to be at border's 
//edge and returns a negative one which means no movement in the calling function : mopveShip(...)
int checkForShipOnBorder(int x, int y)
{


	//left
	if (x < 0 )
	{
		shipObject.setX(0);
		
		return(-1);

	}
	//right
	else if (x  > (gScreenWidth - shipObject.getWidth())) 
	{
		shipObject.setX(gScreenWidth - shipObject.getWidth());
		return(-1);

	}
	//bottom
	else if (y > (gScreenHeight - shipObject.getHeight()))
	{
		shipObject.setY(gScreenHeight - shipObject.getHeight());
		return(-1);

	}
	//top
	else if (y < 0 ) 
	{
		shipObject.setY(0);
		return(-1);

	}


	return(1);
}


// To look at later, we need to deal with the shutdown of the three vectors:
// large asteroids, small asteroids, bullet and the deconstruction where it
// needs to be considered. 
void shutdown(int exitNum) 
{

	exit(exitNum);

}


//fills the asteroid vector with initialized asteroids. asterType is the type of the asteroid.
int fillAsteroidVector(int numAsteroid,  int width, int height, asteroidType asterType,  sf::Texture & texture) {

	// for random direction
	int j = 0;
	//g_TotalAsteroids is the total number of asteroids : already created plus newly added that we are adding
	//right now
	int g_TotalAsteroids = g_TotalNumAllAsteroids + numAsteroid;

	//g_TotalNumAllAsteroids increases whenever ther is a new asteroid creation 
	//(from push_back)
	for (int i = g_TotalNumAllAsteroids; i < g_TotalAsteroids; i++)
	{
		g_TotalNumAllAsteroids++;

		//large asteroids are initialized for movement (there behind on of the four sides and ready
		//for movement.)  Where there activeness is set to onscreen.  The small asteroids have not 
		//been created on the main monitor sceen (two for each large asteroid that is destroyed)
		//they are initialized with 'initialized' and is changed to 'onscreen' in createSmallAsteroid
		//function
		if (asterType == smaller)
		{
			asteroidCollection.push_back(asteroid(width, height, texture, smaller));
			//readies for onscreen usage in createSmallerAsteroid which sets deltax and deltay and whichdirection
			asteroidCollection[i].setActivate(initialized);
		}
		else if (asterType == larger)
		{
			//generated is 0 through three for starting direction on screen : top, right, bottom, left
			j = (rand() % 4);
			//asteroid now calls constructor 
			asteroidCollection.push_back(asteroid(width, height, texture, larger));
			//sets deltax and deltay and which direction
			asteroidCollection[i].setInitialAsteroid(j);
		}

	}

return(1);
}

// indexOfAsteroid is the index of the large asteroid that has been shot with a bullet and
// is being replaced on the screen with the two smaller asteroids that are to be activate
// (onscree) here.  They were set to intialize in fillAsteroidVectors and refillAsteroidVectors.
// Called from checkCollisionsaAllBulletsWithAnAsteroids.
int createSmallerAsteroids(int indexOfAsteroid, sf::Texture smallerTextureAst)
{
	
	int flagUnusedAsteroidIndexFound = 0;
	int indexNextSmallerAsteroid1 = 0;
	int indexNextSmallerAsteroid2 = 0;

	//This fuction finds the first index for the small asteroid.  The assumption is that
	//the second indexed asteroid created from a collission with a large asteroid and a bullet
	//will always by the index after the first small asteroid. It is assumed that if there is one
	//smallasteroid available than there should therefore be two, becauser there are two asteroids created
	//for each large asteroid.  Small asteroids created in this function will be set to onscreen. 
	//A small asteroid before this function is set with an activeness of initialized.  
	for (int i = 0 ; i <= (g_TotalNumAllAsteroids - 1); i++)
	{
		

		//small asteroids are initialized as onscreen because they were initailized - see comment above
		if (asteroidCollection[i].getActivate() == initialized)
		{

			//if this is two from these to for loops than two small asteroids have been found for
			//using.  Because they were set as initalized
			flagUnusedAsteroidIndexFound++;
			indexNextSmallerAsteroid1 = i;
			//their ready for moving and drawing
			asteroidCollection[i].setActivate(onscreen);
			//unused asteroid found and breaking out of loop because of this variables amount!
			i = g_TotalNumAllAsteroids;
		}
	}

	for (int j = 0; j <= (g_TotalNumAllAsteroids - 1); j++)
	{


		//small asteroids are initialized as onscreen because they were set as "initialized"
		//in fillAsteroidVectors() or refillAsteroidVectors()
		if (asteroidCollection[j].getActivate() == initialized)
		{

			//if this is two one for each for loop,  both small asteroids ready for movement
			flagUnusedAsteroidIndexFound++;
			indexNextSmallerAsteroid2 = j;

			//their ready for moving and drawing
			asteroidCollection[j].setActivate(onscreen);
			
			//unused asteroid found and breaking out of loop because of this variables amount!
			j = g_TotalNumAllAsteroids;


		}
	}
	
	//somethings wrong, this function was called and there are no 2 new asteroids readied
	//as initialized
	if (flagUnusedAsteroidIndexFound != 2)
	{
		shutdown(-5);
	}
	
	
	
	//little asteroid located at intersection of smaller circle's diameter centered on top of larger circle (asteroid)
	//diameter of smaller circle is 32

	//The larger asteroid in the remaining code is the asteroidCollection with the indes : indexOfAsteoid
	
	//center of little asteroid is located with center on the top horizontal tangent of larger asteroid
	

	//The small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The math here is interesting: the width of the larger asteroid minus the width of the smaller 
	//asteroid leaves us with the remaining width space on both the right and left of the small asteroid.
	//We than divide this space by two to get the smaller asteroid positioned at the center horizontally.
	//easier to draw out on paper
	asteroidCollection[indexNextSmallerAsteroid1].setX((asteroidCollection[indexOfAsteroid].getX() +
	( ( asteroidCollection[indexOfAsteroid].getWidth() - (asteroidCollection[indexNextSmallerAsteroid1].getWidth() ) / 2 ) ) ) );
	//The small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The small asteroid is simpily above the asteroid by half of its height.
	//easier to draw out on paper
	asteroidCollection[indexNextSmallerAsteroid1].setY((asteroidCollection[indexOfAsteroid].getY() -
	( asteroidCollection[indexNextSmallerAsteroid1].getHeight()  / 2 ) ) ) ;
	//The small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The math here is interesting: the width of the larger asteroid minus the width of the smaller 
	//asteroid leaves us with the remaining width space on both the right and left of the small asteroid.
	//We than divide this space by two to get the smaller asteroid positioned at the center horizontally.
	//center of little asteroid is located with center on the top tangent of larger asteroid
	//Drawing this might help you envision it.
	asteroidCollection[indexNextSmallerAsteroid2].setX((asteroidCollection[indexOfAsteroid].getX() +
	( (asteroidCollection[indexOfAsteroid].getWidth() - ( asteroidCollection[indexNextSmallerAsteroid2].getWidth()) / 2 ) ) ) );
	//center of little asteroid is located on bottom of larger asteroid horizontal tangent 
	//The y location of the small asteroid is the height of the larger asteroid (remember
	//that the positive direction of the height is downward.)  and subtracted to move up 
	//negatively the height of the smaller asteroid divided by two.
	//easier to do if drawn on paper.
	asteroidCollection[indexNextSmallerAsteroid2].setY(asteroidCollection[indexOfAsteroid].getY() +
	(  asteroidCollection[indexOfAsteroid].getHeight() - (  asteroidCollection[indexNextSmallerAsteroid2].getHeight()  / 2 ) ) ) ;
	//initializations for setposition right below.
	int x1 = asteroidCollection[indexNextSmallerAsteroid1].getX();
	int y1 = asteroidCollection[indexNextSmallerAsteroid1].getY();
	int x2 = asteroidCollection[indexNextSmallerAsteroid2].getX();
	int y2 = asteroidCollection[indexNextSmallerAsteroid2].getY();
	////sets the position of the asteroid with x and y coordinates
	asteroidCollection[indexNextSmallerAsteroid1].anAsteroid.setPosition(sf::Vector2f(x1, y1));
	asteroidCollection[indexNextSmallerAsteroid2].anAsteroid.setPosition(sf::Vector2f(x2, y2));
	
	//get direction of large asteroid for use in determining small asteroids deltaX and deltaY
	asteroidMovement majorDirection = asteroidCollection[indexOfAsteroid].getWhichDirection();
	//local objects for use of passing in below by reference
	asteroidMovement newDirection1 = directions[0][0];
	asteroidMovement newDirection2 = directions[0][0];
	//calls with refernce si we can use the obtained direction in the following two functions
	getTwoDirectionsFromMajorDirection(majorDirection, newDirection1, newDirection2);
	//sets deltas inside for these small asteroid objects
	asteroidCollection[indexNextSmallerAsteroid1].setDeltaWithDirection(newDirection1);
	asteroidCollection[indexNextSmallerAsteroid2].setDeltaWithDirection(newDirection2);	
	return(1);
}

//Checks if all large and small asteroids are destroyed 
int checkAllAsteroidsDestroyed()
{

	int asteroidCount = 0;
	for (int i = 0; i <= (g_TotalNumAllAsteroids - 1); i++)
	{

		if (asteroidCollection[i].getActivate() == destroyed)
		{
			asteroidCount++;
			
		
		}
		else
		{
			break;
		}

	}
	if (asteroidCount == g_TotalNumAllAsteroids)
	{
		return(1);
	}


	return(-1);
}

	

//Important : make sure there are twice as many small asteroids as there are large asteroids
int startNextLevel() {

	

	//g_Level was initialized as 0
	g_Level++;

	switch (g_Level) {

	case 1:

		g_NumOfLargerAsteroids = 1;
		g_NumOfSmallerAsteroids = g_NumOfLargerAsteroids * 2;


	case 2:
		
		g_NumOfLargerAsteroids = 2;
		g_NumOfSmallerAsteroids = g_NumOfLargerAsteroids * 2;
		
		break;
	case 3:
		g_NumOfLargerAsteroids = 3;
		g_NumOfSmallerAsteroids = g_NumOfLargerAsteroids * 2;


		break;
	case 4:
		g_NumOfLargerAsteroids = 4;
		g_NumOfSmallerAsteroids = g_NumOfLargerAsteroids * 2;


		break;

	case 5:
		
		//will break out of while loop in main and end program
		g_Shutdownflag = 1;


		break;

	default:

		break;

	}

	
	return(1);
	

}

//if the asteroid is onscreen it is either a large asteroid that is initialized 
//or reinitialized which means its waiting behind the border to be drawn and moved.
//It could also be on the screen ..."onscreen"
//if it is a small asteroid it is onscreen if it has been created with :
//createsmallasteroids.
int moveasteroids()
{

	for (int i = 0; i <= (g_TotalNumAllAsteroids - 1); i++)
	{

		if (asteroidCollection[i].getActivate() == onscreen)
		{



			asteroidCollection[i].moveAsteroid();
			window.draw(asteroidCollection[i].anAsteroid);


		}


	}


	return(1);
}


//check for all asteroids offscreen and set them up for moving putting them 
//their height or their width behind the four screen borders so that there 
//ready but just unvisable.
int reinitializeOffscreenAsteroids()
{
	int randNum = 0;
	for (int i = 0; i <= (g_TotalNumAllAsteroids - 1); i++)
	{
		if (asteroidCollection[i].getActivate() == offscreen)
		{
			randNum = std::rand() % (4);

			//resets asteroid to onscreen for draw and move.
			//this is used for both large and small asteroids and is not the same
			//as when (two) asteroids are created in the createSmallerAsteroids called
			//in checkCollisionsAllBullets...
			asteroidCollection[i].setInitialAsteroid(randNum);
		}

	}
	return(1);
}


//fills vector with numOfBullets and fills the vector.  Lastly, sets 
//the static variaable.
int fillBulletVector (int numOfBullets, sf::Texture & texture)
{

	
	
	for (int i = 0; i <= numOfBullets -1 ; i++)
	{
		
		bullets.push_back( bullet(texture, 16, 16));
	
	}

	

	return(1);
}






int main(void)
{
	
	
	//seeds the time for random direction and postion of asteroids right before drawing on screen
	std::srand(time(NULL));
	
	const int constInitialNumBullets = 10;

	int tempFlagForTest = 0;
	


	FreeConsole();

	
	if (!largerTextureAsteroid.loadFromFile("largerasteroid.png"))
	{
		shutdown(-6);
	}

	
	if (!smallerTextureAsteroid.loadFromFile("smallerasteroid.png"))
	{
		shutdown(-7);
	}

	
	if (!texturebullet.loadFromFile("bullet.png"))
	{
		shutdown(-8);
	}

	
	if (!fontForScore.loadFromFile("ARIALBD.ttf"))
	{
		shutdown(-9);
	}


	//create vector fills the object with a random entry border (0-3)
	//Uses setInitialAsteroid. third and fourth argument is width an than height
	
	//creates vector with asteroids - order is not important
	fillAsteroidVector(g_NumOfLargerAsteroids, 64, 64, larger, largerTextureAsteroid);
	fillAsteroidVector(g_NumOfSmallerAsteroids, 32, 32, smaller, smallerTextureAsteroid);
	
	
	//this will set the vector to 10 bullets index  of 9 of course
	fillBulletVector(constInitialNumBullets, texturebullet);
	theScore.setFont(fontForScore);

	//initial ship draw
	drawShip();

	while (window.isOpen() && (g_Shutdownflag == 0))
	{
		
		while (window.pollEvent(event))
		{
	
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::M))
			{
				shipObject.rotateShipClock();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::N))
			{
				shipObject.rotateShipCClock();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				shoot();
			}

			
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}


		window.clear();
		

		//if the asteroids are not on the screen they will not be moved.  draws the asteroid too.
		moveasteroids();
		
		//checks keyboard and if pressed calls moveship with the deltas otherwise calls moveship
		//with - 1 which causes sliding effect
		if (checkkeyboard() == -1)
		{
			//also checks if movement would be beyond border is so returns -1
			moveShip(-1);
		}


		checkCollisionsShipWithAsteroids();
		
		
		
		//draws bullets too...
		movebullets();
		
		
		
		checkCollisionsaAllBulletsWithAnAsteroids();
	   

		//if 1 is returned than all those asteroids are destroyed and reinitializeation and new asteroids are created
		//and a new level is started
		if (checkAllAsteroidsDestroyed() == 1)
		{
			
			//holds this levels value because they are changed in startNextLevel for RefillAsteroidVector
			int oldLevelsSmallAsteroidAmt = g_NumOfSmallerAsteroids;
			int oldLevelsLargeAsteroidAmt = g_NumOfLargerAsteroids;

				
				//new amounts of new asteroids are set in g_NumOfSmallAsteroids and g_NumOfLargerAsteroids
				if (startNextLevel())
				{
					//break out of first while if set in startNextLevel and end program 
					if (g_Shutdownflag == 1)
					{
						continue;
					}

					//fills one asteroid collection with two statements.
					//oldLevels... are g_NumOfSmallAsteroids and g_NumOfLargerAsteroids and are last levels values
					//the new levels minus the old levels gives us the new asteroids to create
					int createThisAmtAsteroids = (g_NumOfLargerAsteroids - oldLevelsLargeAsteroidAmt); 
		 			//creates the newly created asteroids with push_back and reinitializes the older asteroids
					//with a new active setting
 					refillAsteroidVectors(createThisAmtAsteroids, 64, 64, larger, largerTextureAsteroid);
					//see right above
					createThisAmtAsteroids = (g_NumOfSmallerAsteroids - oldLevelsSmallAsteroidAmt);
					//same as above : just a smaller asteroid group for the collection
					refillAsteroidVectors(createThisAmtAsteroids, 32, 32, smaller, smallerTextureAsteroid);
					
				}
			}


		//sets asteroids to offscreen if they are
		checkForAsteroidOffScreen();
		
		
		//check for all asteroids offscreen and if so set them up for moving behind the four screen borders
		reinitializeOffscreenAsteroids();
		

		if (theScore.getScore() == 0)
		{
			theScore.drawScore(0);
		}


		window.draw(theScore.getTextMessage());

		Sleep(10);
		
		window.display();
		
	}

	return 0;
}


//pushes the new asteroids for the new level if either small or large
//than reinitializes their deltax and deltay and their direction and x and y
//in setInitialAsteroid
int refillAsteroidVectors(int numAsteroidsToCreate, int Width, int Height, asteroidType type , sf::Texture & texture)
{
	int j = 0;
	if (type == larger)
	{
		for (int i = 0; i <= (numAsteroidsToCreate - 1); i++)
		{
			//create the new additional asteroids 
			asteroidCollection.push_back(asteroid(Width, Height, texture, larger));
			g_TotalNumAllAsteroids++;
		}
		for (int i = 0; i <= (g_TotalNumAllAsteroids - 1); i++)
		{
			if (asteroidCollection[i].getAsteroidType() == larger)
			{
				j = (rand() % 4);
				//sets deltax and deltay, x and y, direction
				asteroidCollection[i].setInitialAsteroid(j);
			}
		}

	}
	else if (type == smaller)
	{
		for (int i = 0; i <= (numAsteroidsToCreate - 1); i++)
		{
				//creates extra small asteroids
				asteroidCollection.push_back(asteroid(Width, Height, texture, smaller));
				g_TotalNumAllAsteroids++;
		}
		//reinitalizes the old and new asteroids with the new activation so that they
		//can be moved after their changed from initialized to onscreen in createsmallasteroids
		for (int i = 0; i <= (g_TotalNumAllAsteroids-1); i++)
		{

			if (asteroidCollection[i].getAsteroidType() == 
				smaller)
			{
				
				asteroidCollection[i].setActivate(initialized);
			}
		}
	}

	return(1);
}

	


//Takes one direction from a large asteroid and returns the two new directions of small asteroid by reference
void getTwoDirectionsFromMajorDirection(asteroidMovement & theMajorDirection, asteroidMovement & smallAsteroidDirection1, asteroidMovement & smallAsteroidDirection2)
{
	switch (theMajorDirection) {


	case asteroidMovement::UP:
		smallAsteroidDirection1 = asteroidMovement::UP_RIGHT;
		smallAsteroidDirection2 = asteroidMovement::UP_LEFT;
		break;
	case asteroidMovement::DOWN:
		smallAsteroidDirection1 = asteroidMovement::DOWN_RIGHT;
		smallAsteroidDirection2 = asteroidMovement::DOWN_LEFT;
		break;
	case asteroidMovement::LEFT:
		smallAsteroidDirection1 = asteroidMovement::DOWN_LEFT;
		smallAsteroidDirection2 = asteroidMovement::UP_LEFT;
		break;
	case asteroidMovement::UP_LEFT:
		smallAsteroidDirection1 = asteroidMovement::UP;
		smallAsteroidDirection2 = asteroidMovement::LEFT;
		break;
	case asteroidMovement::DOWN_LEFT:
		smallAsteroidDirection1 = asteroidMovement::DOWN;
		smallAsteroidDirection2 = asteroidMovement::LEFT;
		break;
	case asteroidMovement::RIGHT:
		smallAsteroidDirection1 = asteroidMovement::UP_RIGHT;
		smallAsteroidDirection2 = asteroidMovement::DOWN_RIGHT;
		break;
	case asteroidMovement::UP_RIGHT:
		smallAsteroidDirection1 = asteroidMovement::UP;
		smallAsteroidDirection2 = asteroidMovement::RIGHT;
		break;
	case asteroidMovement::DOWN_RIGHT:
		smallAsteroidDirection1 = asteroidMovement::DOWN;
		smallAsteroidDirection2 = asteroidMovement::RIGHT;
		break;

	default:
		break;
	}
}

