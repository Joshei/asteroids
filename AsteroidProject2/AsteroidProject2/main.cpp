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


//enumeration for the asteroid used for passing to function that has different 
//(and very little) programming dependant upon which type.
enum asteroidtype { smallerasteroid, largerasteroid };

//global variables g_NumOfLargerAsteroids must be two times as many small asteroids: g_NumOfSmallerAsteroids
//level that game is on : starts at 1, increase in level causes more asteroids
int g_Level = 1;
int g_NumOfLargerAsteroids = 1;
int g_NumOfSmallerAsteroids = g_NumOfLargerAsteroids * 2;
//used to break out of while, when is set 
int g_Shutdownflag = 0;



//GLOBAL FUNCTION DECLARATIONS
int drawShip(void);
int moveShip(int amountForMovem, int keyPressed);
int checkkeyboard();
int checkCollisionsShipWithAsteroids(int numInVector, std::vector<asteroid> & v);
int checkCollisionsaAllBulletsWithAnAsteroids(int numAsteroids, std::vector<asteroid> & vector, asteroidtype whichAsteroidSize);
int shoot(void);
int movebullets(void);
int checkForBulletOffscreen(int index);
int checkForAsteroidOffScreen(std::vector<asteroid> & vector, int amount);
int checkForShipOffScreen(int x, int y);
void shutdown(int exitNum);
int fillAsteroidVector(int numAsteroids, int theWidth, int theHeight, std::vector<asteroid> & v, asteroidtype whichTyoe, sf::Texture & TextureAsteroid);
int createSmallerAsteroids(int indexOfAsteroid, sf::Texture smallerTextureAstroid);
int checkAllAsteroidsDestroyed(int totalNumbOfAsteroids, std::vector<asteroid> & vect);
int startNextLevel(void);
int moveasteroids(int numbOfTotalAsteroids, std::vector<asteroid> & vect);
int reinitializeOffscreenAsteroids(int numbOfTotalAsteroids, std::vector<asteroid> & vect);
int fillBulletVector(int numberOfBullets, sf::Texture & textureOfBullet);
int unitializeAsteroids(std::vector<asteroid>  & vector);

/////////!!!!!!!!!!!!!!!!!!


//put here together because smallerTextureAsteroid used in: checkCollisionsaAllBulletsWithAnAsteroid 
sf::Texture largerTextureAsteroid;
sf::Texture smallerTextureAsteroid;
sf::Texture texturebullet;
sf::Font fontForScore;

//initialized of the vectors for asteroids
std::vector<asteroid> largerAsteroidObject;
std::vector<asteroid> smallerAsteroidObject;
std::vector <bullet> bullets;
score theScore(10, 10);
sf::Event event;
sf::RenderWindow window(sf::VideoMode(gScreenWidth, gScreenHeight), "Asteroids!");

//global ship pbject
ship shipObject(500, 500);



//GLOBAL FUNCTION DEFINITIONS FOLLOW:


int drawShip(void)
{
	
	
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
	if (checkForShipOffScreen(x, y) == -1)
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
int checkCollisionsShipWithAsteroids(int numOfAsteroidsInVector, std::vector<asteroid> & v) 
{


	for (int i = 0; i <= numOfAsteroidsInVector - 1; i++)
	{

		//checks if asteroid on screen if so is not initialized, destroyed, instantiated, or offscreen
		//so if it is enters beneath this if.  Otherwise it continues to the for loop with next value of i.
		if (v[i].getActivate() != onscreen )
		{
			continue;

		}


		//ship above and left of asteroid - looks ok 

		//ship's top is below or equl to asteroid.  ships bottom is above or equal to the asteroids top 
		//AND ship's left is to the left or equal to the left of asteroid and ship's right is to the right or
		//equal to the asteroids left side
		
		
		if ((shipObject.getY() <= v[i].getY()) && ((shipObject.getY() + shipObject.getHeight()) >= v[i].getY())
			&&
			((shipObject.getX() <= v[i].getX()) && ((shipObject.getX() + shipObject.getWidth()) >= v[i].getX())))
		{

			shutdown(-1);
		}
		
		//ship above and right of asteroid -looks ok, comments okay
		
		
		//ship's top is above or equal to asteroids top and ship's bottom is below or equal asteroids top
		//AND ship's left is to the right or equal to asteroids left and ship's left is to left or equal of asteroids right 
		if ((shipObject.getY() <= v[i].getY()) && ((shipObject.getY() + shipObject.getHeight()) >= v[i].getY())
			&&
			((shipObject.getX() >= v[i].getX()) && (shipObject.getX() <= (v[i].getX() + v[i].getWidth()))))
		{

			shutdown(-2);
		}

		

		//ship below and left of asteroid -looks ok : commented ok

		//ships top is below or equal to asteroids top and ships top is above or equal to asteroids bottom
		//AND ship's right is equal or to right to asteroids left side and ship's left side is to the left
		//or equal to asteroids left side.

		
		if ((shipObject.getY() >= v[i].getY()) && ((shipObject.getY()) <= (v[i].getY() + v[i].getHeight()))
			&&
		//	(((shipObject.getX()) >= (v[i].getX() + v[i].getWidth())) && ((shipObject.getX() + shipObject.getWidth()) >= (v[i].getX()))))
		(  (  (shipObject.getX() + shipObject.getWidth()  ) >= (v[i].getX()  ) ) && (shipObject.getX() <= v[i].getX()  )  )  )
		
		{
			shutdown(-3);

		}



		
		//ship below and right of asteroid looks ok
	
		//ship's top is below or equal to asteroids top and ship's top is above or equal asteroids bottom
		//AND ship's left is to the right or equal asteroids left side   and ships left side is to the left or equal to 
		//the asteroids right side
		if ((shipObject.getY() >= v[i].getY()) && ((shipObject.getY()) <= (v[i].getY() + v[i].getHeight()))
			&&
			(((shipObject.getX()) >= (v[i].getX())) && ((shipObject.getX()) <= (v[i].getX() + v[i].getWidth()))))
		{


			shutdown(-4);
		}

	}

	return(1);
}




//check for collision and if so and is a smallerasteroid the bullet is changed to inactive and
//the asteroid is changed to destroyed.  If it is larger asteroid than the asteroid is set to
//destroyed and two new smaller asteroids are created.
//With every for loop that checks bullets the bullet is checked to be inactive and if it is then
//the loop continues which means the for loop is run again with the next index.
int checkCollisionsaAllBulletsWithAnAsteroids(int numOfAsteroids, std::vector<asteroid> & v, asteroidtype whichAsteroid )
{


	for (int j = 0; j <= (numOfAsteroids - 1); j++)
	{
		

		if (v[j].getActivate() != onscreen )
		{
			continue;
		}

		for (int i = 0; i <= (bullet::getMaxNumBullets()-1); i++)
		{


			if (!bullets[i].getIsactive())
			{
				continue;
			}

			

			//bullets top edge is below or equal asteroid's top edge and bullets top edge is above or equal asteroids lower edge
			//And bullets left edge is right or equal to asteroid's left edge and bullets left edge is to the 
			//left or equal of asteroid's right edge
			//
			//draw out if necessary.
			//if there is an intersection and images colllide and bullet 

			//asteroid are removed after this function that sets both bullet and asteroid as inactive!
			if (((bullets[i].getY() >= (v[j].getY())) && (bullets[i].getY() <= ((v[j].getY()) + v[j].getHeight())) &&
				((bullets[i].getX() >= v[j].getX()) && ((bullets[i].getX() <= (v[j].getX() + v[j].getWidth()))))))
			{

				//bullet is used and not active until refired
				bullets[i].setIsactive(false);
				
				//asteroid is destroyed and iss used later after level is passed
				v[j].setActivate(destroyed);



				//This is the diference of the two different sized asteroids when they are hit.  
				//Remember so far the enumeration difference is just two : smallerasteroid and 
				//larger asteroid
				if (whichAsteroid == largerasteroid)
				{
					//passes in next number of small asteroid and than creates two
					createSmallerAsteroids(j, smallerTextureAsteroid);

					
					
					theScore.addToScore(40);
					theScore.drawScore();

				
				}
				else if (whichAsteroid == smallerasteroid)
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
	
	
		int numOfBullet = 0;

		
		int madeAnActiveBullet = 0;

		//static function
 		for (int i = 0; i <= (bullet::getMaxNumBullets()-1) ; i++) 
		{

			//if bullet already active go to for loop at next index
			if (bullets[i].getIsactive())
			{
				continue;
			}

			numOfBullet = i;

			madeAnActiveBullet = 1;
			//bullet was inactive now is active (was off screen)
			bullets[i].setIsactive(true);
			break;

		}

		if (madeAnActiveBullet == 0)
		{
			return(-1);
		}

			
		
		//up key pressed direction of bullet will be upwards.  creates a bullet the same amount 
		//away for each off the four directions shot
		//for now, the bullets width is 16 and its height is 16.  values are divided by 2 to center the diferent images
			if (shipObject.getDirection() == up)
			{

				//bullet center of ship
				bullets[numOfBullet].setX(shipObject.getX() + (.5* shipObject.getWidth()) -( .5* (bullets[numOfBullet].getWidth())   ));
				//bullet a bit above ship
				bullets[numOfBullet].setY(-100 + shipObject.getY() + shipObject.getHeight());

			
				bullets[numOfBullet].setDirection(up);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBullet].bulletImage.setPosition(sf::Vector2f(bullets[numOfBullet].getX(), bullets[numOfBullet].getY()));

				window.draw(bullets[numOfBullet].bulletImage);

				//bullet has been set here as -5, different speeds of objects make them relativly
				//faster or slower, there are three speeds so far: bullet, ship, and asteroids
				bullets[numOfBullet].setDeltaX(0);
				bullets[numOfBullet].setDeltaY(-5);
				bullets[numOfBullet].setIsactive(true);
				

			}
			

			else if (shipObject.getDirection() == right) 
			{

				//bullet right of ships left value by 100. remember the ship has a width of 64.
				bullets[numOfBullet].setX(shipObject.getX() + 100);
				//bullet a bit above ship
				bullets[numOfBullet].setY((shipObject.getY() + .5*(shipObject.getHeight() - (.5*(bullets[numOfBullet].getHeight())))));

			
				bullets[numOfBullet].setDirection(right);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBullet].bulletImage.setPosition(sf::Vector2f(bullets[numOfBullet].getX(), bullets[numOfBullet].getY()));

				window.draw(bullets[numOfBullet].bulletImage);

				//sets bullet x speed at a change of 5.
				bullets[numOfBullet].setDeltaX(5);
				bullets[numOfBullet].setDeltaY(0);
				bullets[numOfBullet].setIsactive(true);
				

			}
			//ship is moving downward 
			else if (shipObject.getDirection() == down) 
			{
				//bullet is centered according to ship
				bullets[numOfBullet].setX(shipObject.getX() + .5*(shipObject.getWidth() - (.5* (bullets[numOfBullet].getWidth()))));
				//bullet a bit above ship
				bullets[numOfBullet].setY(100 + shipObject.getY());
				//direction for move bullet
				bullets[numOfBullet].setDirection(down);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBullet].bulletImage.setPosition(sf::Vector2f(bullets[numOfBullet].getX(), bullets[numOfBullet].getY()));
				//bullet image is part of SFML basic instructions on website tutorial questions
				window.draw(bullets[numOfBullet].bulletImage);
				bullets[numOfBullet].setDeltaX(0);
				//sets change of speed to 5 for each cycle through
				bullets[numOfBullet].setDeltaY(5);
				bullets[numOfBullet].setIsactive(true);
				

			}
			//ship is moving left so bullet will be left of ship
			else if (shipObject.getDirection() == left) 
			{

				//ships midpoint is used to center bullet
				bullets[numOfBullet].setX(shipObject.getX() - 100 + (shipObject.getWidth()));
				//bullet a bit above ship
				bullets[numOfBullet].setY((.5 * shipObject.getHeight()) + shipObject.getY() - (.5*( bullets[numOfBullet].getHeight())) );

				//direction set to left for moving/drawing bullet
				bullets[numOfBullet].setDirection(left);
				//sets the position of the bullet with x and y coordinates
				bullets[numOfBullet].bulletImage.setPosition(sf::Vector2f(bullets[numOfBullet].getX(), bullets[numOfBullet].getY()));

				window.draw(bullets[numOfBullet].bulletImage);
				//change is 5 per cycle of main
				bullets[numOfBullet].setDeltaX(-5);
				bullets[numOfBullet].setDeltaY(0);
				bullets[numOfBullet].setIsactive(true);
				


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
//function.  The width and height is used to check if the image is totally off the screen!
int checkForBulletOffscreen(int index) 
{

	//left
	if (bullets[index].getX() < (0 - bullets[index].getWidth()))
	{
		bullets[index].setIsactive(false);
		
		return(-1);
			
	}
	else if (bullets[index].getX() > (gScreenWidth) ) 
	{
		bullets[index].setIsactive(false);
		
		return(-1);

	}
	else if (bullets[index].getY() > (gScreenHeight)) 
	{
		bullets[index].setIsactive(false);
		
		return(-1);

	}
	else if ((bullets[index].getY()) < (0 - (bullets[index].getHeight()))) 
	{
		bullets[index].setIsactive(false);
		
		return(-1);

	}


	return(1);
}

// maxAsteroids is the number of asteroids to check minus one.  The function checks
//if the asteroid is totally off the screen using its height or width. If it is the 
//asteroid is set as offscreen which means it is not being drawn.  Later we look at
//the activation of offscreen to reinitialize and set back to onscreen so that it 
//will be drawn.
int checkForAsteroidOffScreen(std::vector<asteroid> & v, int maxAsteroids)
{

	for (int i = 0; i <= maxAsteroids-1; i++)
	{

		if (v[i].getX() < (0 - v[i].getWidth()))
		{

			v[i].setActivate(offscreen);


		}
		else if (v[i].getX() > (gScreenWidth))
		{

			v[i].setActivate(offscreen);

		}
		else if (v[i].getY() > (gScreenHeight))
		{

			v[i].setActivate(offscreen);

		}
		else if ((v[i].getY()) < (0 - ((v[i].getHeight()))))
		{

			v[i].setActivate(offscreen);

		}
	}

	return(1);
}

//checks if ship is at passed of the four borders.  If it does, sets ship  to be at border's 
//edge and returns a negative one which means no movement in the calling function : mopveShip(...)
int checkForShipOffScreen(int x, int y)
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


//fills the asteroid vectors with initialized asteroids
int fillAsteroidVector(int numOfAsteroids, int width, int height, std::vector<asteroid> &v, asteroidtype type, sf::Texture  & texture) {

	
	

	int j = 0;
	
	for (int i = 0; i <= (numOfAsteroids - 1); i++)
	{
		
		//generated is 0 through three for starting direction on screen : top, right, bottom, left
		j = (rand() % 4);
	
		//asteroid now calls constructor 
		v.push_back(asteroid(width, height, texture ));
			
			
		//boolean initialize means its largeAsteroidObject so that the large asteroids
		//are initialized for movement (there behind on of the four sides and ready
		//for movement.)  Where there activeness is set to onscreen
		//
		//if initialze is on than the large asteroids are being set.  Otherwise
		//the small asteroids have not been created on the main monitor sceen
		//(two for each large asteroid that is destroyed)
		

			 
		if (type == largerasteroid) 
		{
			//sets fromThisDirection with j and whichDirection with a randomizer in this function
			v[i].setInitialAsteroid(j);
		
		}
		else if (type == smallerasteroid)
		{

			v[i].setActivate(initialized);
		
		}
			

	}

return(1);
}

// indexOfAsteroid is the index of the large asteroid that has been shot with a bullet and
// has been replaced on the screen with the two smaller asteroids that are to be created
// (initialized) here.  Called from checkCollisionsaAllBulletsWithAnAsteroids.





int createSmallerAsteroids(int indexOfAsteroid, sf::Texture smallerTextureAst)
{
	
	int flagUnusedAsteroidIndexFound = 0;
	int indexNextSmallerAsteroid = 0;

	//This fuction finds the first index for the small asteroid.  The assumption is that
	//the second indexed asteroid created from a collission with a large asteroid and a bullet
	//will always by the index after the first small asteroid. It is assumed that if there is one
	//smallasteroid available than there should therefore be two, becauser there are two asteroids created
	//for each large asteroid.  Small asteroids created in this function will be set to onscreen. 
	//A small asteroid before this function is set with an activeness of initialized.  

	 
	for (int i = 0; i <= g_NumOfSmallerAsteroids - 1; i++)
	{

		//small asteroids are initialized as onscreen because they start on the screen
		if (smallerAsteroidObject[i].getActivate() == initialized)
		{

			flagUnusedAsteroidIndexFound = 1;
			indexNextSmallerAsteroid = i;

			//their ready for moving and drawing
			smallerAsteroidObject[i].setActivate(onscreen);
			smallerAsteroidObject[i+1].setActivate(onscreen);
			
			//unused asteroid found and breaking out of loop because of this variables amount!
			i = g_NumOfSmallerAsteroids;
			

		}
	}
	
	//somethings wrong, this function was called and there are no new asteroids unused
	//and set to initialized so we can't make two small asteroids if all the asteroids have
	//already been started and are no longer the activeness of initialized.
	if (flagUnusedAsteroidIndexFound != 1)
	{
		shutdown(-5);
	}
	
	
	
	//little asteroid located at intersection of smaller circle's diameter centered on top of larger circle (asteroid)
	//diameter of smaller circle is 32
	
	//center of little asteroid is located with center on the top tangent of larger asteroid
	

	//The small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The math here is interesting: the width of the larger asteroid minus the width of the smaller 
	//asteroid leaves us with the remaining width space on both the right and left of the small asteroid.
	//We than divide this space by two to get the smaller asteroid positioned at the center horizontally.
	//easier to draw out on paper
	smallerAsteroidObject[indexNextSmallerAsteroid].setX((largerAsteroidObject[indexOfAsteroid].getX() +
	( ( largerAsteroidObject[indexOfAsteroid].getWidth() - (smallerAsteroidObject[indexNextSmallerAsteroid].getWidth() ) / 2 ) ) ) );

	//The small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The small asteroid is simpily above the asteroid by half of its height.
	//easier to draw out on paper
	smallerAsteroidObject[indexNextSmallerAsteroid].setY((largerAsteroidObject[indexOfAsteroid].getY() -
	( smallerAsteroidObject[indexNextSmallerAsteroid].getHeight()  / 2 ) ) ) ;

	//The small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The math here is interesting: the width of the larger asteroid minus the width of the smaller 
	//asteroid leaves us with the remaining width space on both the right and left of the small asteroid.
	//We than divide this space by two to get the smaller asteroid positioned at the center horizontally.
	//center of little asteroid is located with center on the top tangent of larger asteroid
	//Drawing this might help you envision it.
	smallerAsteroidObject[indexNextSmallerAsteroid+1].setX((largerAsteroidObject[indexOfAsteroid].getX() +
	( (largerAsteroidObject[indexOfAsteroid].getWidth() - ( smallerAsteroidObject[indexNextSmallerAsteroid+1].getWidth()) / 2 ) ) ) );

	
	
	//center of little asteroid is located on bottom of larger asteroid horizontal tangent 
	//The y location of the small asteroid is the height of the larger asteroid (remember
	//that the positive direction of the height is downward.)  and subtracted to move up 
	//negatively the height of the smaller asteroid divided by two.
	//easier to do if drawn on paper.
	smallerAsteroidObject[indexNextSmallerAsteroid+1].setY(largerAsteroidObject[indexOfAsteroid].getY() +
	(  largerAsteroidObject[indexOfAsteroid].getHeight() - (  smallerAsteroidObject[indexNextSmallerAsteroid+1].getHeight()  / 2 ) ) ) ;


	





	//initializations for setposition right below.
	int x1 = smallerAsteroidObject[indexNextSmallerAsteroid].getX();
	int y1 = smallerAsteroidObject[indexNextSmallerAsteroid].getY();
	int x2 = smallerAsteroidObject[indexNextSmallerAsteroid+1].getX();
	int y2 = smallerAsteroidObject[indexNextSmallerAsteroid+1].getY();


	////sets the position of the asteroid with x and y coordinates
	smallerAsteroidObject[indexNextSmallerAsteroid].anAsteroid.setPosition(sf::Vector2f(x1, y1));
	smallerAsteroidObject[indexNextSmallerAsteroid+1].anAsteroid.setPosition(sf::Vector2f(x2, y2));


	

	//to understand Which directions look here:

	

	//starting behind top border	   :  0
	//0.  asteroid moves down and right
	//1.  asteroid moves down
	//2.  asteroid moves down and left
	//starting behind right border     :  1
	//3.  asteroid moves left and down
	//4.  asteroid moves left
	//5.  asteroid moves left and up
	//starting behind bottom border     : 2
	//6.  asteroid moves up and left 
	//7.  asteroid moves up
	//8.  asteroid moves up and right
	//starting behind left border      :  3
	//9.  asteroid moves up and right
	//10.  asteroid moves right
	//11.  asteroid moves down and right



	////////////////////////////



	//The deltas below help in relative motion that is if a delta is 3 and a delta
	//is 2 the object with delta three will change 3 pixels every move and the object
	//with delta 2 will move two.
	//set which direction is for future programming for the possibility of non random
	//wrapping from right border to left, top to bottom, vice versa, etc.

	//the set deltas are the change  for evey cycle of main.  The direction set 
	//is 45 degrees clockwise and 45 degrees counter clockwise from the 
	//angle of the direction of the large asteroid that was destroyed and caused the
	//two small asteroids to be created.



	//looks good
	//////////////////////

	//behind border 0 : top
	//large asteroid direction is : down and right
	 if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 0)
	{


		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(4);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(1);
	}



	//behind border 0 : top
	//large asteroid direction is :down
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 1)
	{

		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(3);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(11);
	}
	//behind border 0 : top
	//large asteroid direction is :left down
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 2)
	{

		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(10);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(1);
	}




	/////////////////////

	//behind border 1 : right
	//large asteroid direction is :left down
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 3)
	{

		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(4);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(1);

	}


	 //behind border 1 : right
	 //large asteroid direction is :left
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 4)
	{

		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(5);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(3);
	}
	 //behind border 1 : right
	 //large asteroid direction is :left up
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 5)
	{

		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(4);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(7);
	}



	 /////////////////////


	 //behind border 2 : down
	 //large asteroid direction is :up and left
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 6)
	{

		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(7);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(0);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(4);
	}
	 //behind border 2 : down
	 //large asteroid direction is :up
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 7)
	{


		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(8);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(6);
	}
	 //behind border 2 : down
	 //large asteroid direction is :up and right
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 8)
	{


		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(7);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX(0);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(10);
	}



	 ////////////////////

	//behind border 3 : left
	//large asteroid direction is : right-up
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 9)
	{
		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(7);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX (0);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY (-2);
		smallerAsteroidObject[indexNextSmallerAsteroid+1].setDeltaX(2);
		smallerAsteroidObject[indexNextSmallerAsteroid+1].setDeltaY (0);
		smallerAsteroidObject[indexNextSmallerAsteroid+1].setWhichDirection(10);

		
		
	
	}
	//behind border 3 : left
	//large asteroid direction is :  right
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 10)
	{
		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(9);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX( 2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY(-2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY(2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(0);
		
	}
	//behind border 3 : left
	//large asteroid direction is :right-down
	else if (largerAsteroidObject[indexOfAsteroid].getWhichDirection() == 11)
	{

		
		smallerAsteroidObject[indexNextSmallerAsteroid].setWhichDirection(10);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaX ( 2);
		smallerAsteroidObject[indexNextSmallerAsteroid].setDeltaY ( 0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaX ( 0);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setDeltaY ( 2);
		smallerAsteroidObject[indexNextSmallerAsteroid + 1].setWhichDirection(1);
	}

	return(1);
}

//Checks if all large or small asteroids are destroyed 
int checkAllAsteroidsDestroyed(int totalNumberOfAsteroids, std::vector<asteroid> & v)
{

	int asteroidCount = 0;
	for (int i = 0; i <= (totalNumberOfAsteroids - 1); i++)
	{

		if (v[i].getActivate() == destroyed)
		{
			asteroidCount++;
			
		
		}
		else
		{
			break;
		}

	}
	if (asteroidCount == totalNumberOfAsteroids)
	{
		return(1);
	}


	return(-1);
}

	

//Important : make sure there are twice as many small asteroids as there are large asteroids
int startNextLevel() {

	

	//g_Level was initialized as 1
	g_Level++;

	switch (g_Level) {

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

int moveasteroids(int numberOfTotalAsteroids, std::vector<asteroid> & v)
{

	for (int i = 0; i <= (numberOfTotalAsteroids - 1); i++)
	{

		if (v[i].getActivate() == onscreen)
		{



			v[i].moveAsteroid();
			window.draw(v[i].anAsteroid);


		}


	}


	return(1);
}


//check for all asteroids offscreen and set them up for moving putting them 
//their height or their width behind the four screen borders so that there 
//ready but just unvisable.
int reinitializeOffscreenAsteroids(int numberOfTotalAsteroids, std::vector<asteroid> & v)
{
	int randNum = 0;
	for (int i = 0; i <= numberOfTotalAsteroids - 1; i++)
	{
		if (v[i].getActivate() == offscreen)
		{
			randNum = std::rand() % (4);

			//resets asteroid to onscreen for draw and move.
			//this is used for both large and small asteroids and is not the same
			//as when (two) asteroids are created in the createSmallerAsteroids called
			//in checkCollisionsAllBullets...
			v[i].setInitialAsteroid(randNum);
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



int unitializeAsteroids(std::vector<asteroid>  & v)
{

	while (!v.empty())
	{
		v.pop_back();
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
	//uses setInitialAsteroid third and fourth argument is width an than height
	fillAsteroidVector(g_NumOfLargerAsteroids, 64, 64, largerAsteroidObject, largerasteroid, largerTextureAsteroid);
	//creates vector with small asteroids
	fillAsteroidVector(g_NumOfSmallerAsteroids, 32, 32, smallerAsteroidObject, smallerasteroid, smallerTextureAsteroid);
	
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
		moveasteroids(g_NumOfLargerAsteroids, largerAsteroidObject);
		moveasteroids(g_NumOfSmallerAsteroids, smallerAsteroidObject);

		
		//checks keyboard and if pressed calls moveship with the deltas otherwise calls moveship
		//with - 1 which causes sliding effect
		if (checkkeyboard() == -1)
		{
			//also checks if movement would be beyond border is so returns -1
			moveShip(-1);
		}


		checkCollisionsShipWithAsteroids(g_NumOfLargerAsteroids, largerAsteroidObject);
		checkCollisionsShipWithAsteroids(g_NumOfSmallerAsteroids, smallerAsteroidObject);
		
		
		
		//draws bullets too...
		movebullets();
		
		
		
		checkCollisionsaAllBulletsWithAnAsteroids(g_NumOfLargerAsteroids, largerAsteroidObject, largerasteroid);
	    checkCollisionsaAllBulletsWithAnAsteroids(g_NumOfSmallerAsteroids, smallerAsteroidObject, smallerasteroid);


		//if 1 is returned twice than all those asteroids are destroyed and a new level is started
		if (checkAllAsteroidsDestroyed(g_NumOfLargerAsteroids, largerAsteroidObject) == 1)
		{
			if (checkAllAsteroidsDestroyed(g_NumOfSmallerAsteroids, smallerAsteroidObject) == 1)
			{

				//pop all the asteroids of both vectors and than create the new number of asteroids
				
				if (startNextLevel())
				{
					//break out of first while if set in startNextLevel and end program 
					if (g_Shutdownflag == 1)
					{
						continue;
					}

					//pop all the asteroids off the vector
					unitializeAsteroids( largerAsteroidObject);
					unitializeAsteroids( smallerAsteroidObject);

					//Important:  constinitials are used in this main.cpp only.
					//third and fourth argument is width an than height
					fillAsteroidVector(g_NumOfLargerAsteroids, 64, 64, largerAsteroidObject, largerasteroid, largerTextureAsteroid);
					//fills vector with 8 small asteroids
					fillAsteroidVector(g_NumOfSmallerAsteroids, 32, 32, smallerAsteroidObject, smallerasteroid, smallerTextureAsteroid);
				
					//these are now the values of the number of current asteroids
					//g_NumOfLargerAsteroids = g_NewNumOfLargerAsteroids;
					//g_NumOfSmallerAsteroids = g_NewNumOfSmallerAsteroids;


				}




			}
		}


		
		checkForAsteroidOffScreen(largerAsteroidObject, g_NumOfLargerAsteroids);
		checkForAsteroidOffScreen(smallerAsteroidObject, g_NumOfSmallerAsteroids);
		
		
		//check for all asteroids offscreen and if so set them up for moving behind the four screen borders
		reinitializeOffscreenAsteroids(g_NumOfLargerAsteroids, largerAsteroidObject);
		reinitializeOffscreenAsteroids(g_NumOfSmallerAsteroids, smallerAsteroidObject);

		
			

			
			
		
		
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



