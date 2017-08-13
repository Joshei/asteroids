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

int g_Shutdownflag = 0;

int g_Level = 0;
//g_NumOfSmallerAsteroids  g_NumOfLargerAsteroids
//used to break out of while, when is set 
int g_TotalNumAllAsteroids = 0;




//GLOBAL FUNCTION DECLARATIONS

bool checkForShipOnBorder(int x, int y);
int checkkeyboard();
int checkAllAsteroidsDestroyed();
int  moveShip(int amountForMovem, int keyPressed);
int shoot(void);
int checkForBulletOffscreen(int index);


void drawShip();
void checkCollisionsShipWithAsteroids();
void checkCollisionsaAllBulletsWithAnAsteroids();
void movebullets(void);
void checkForAsteroidOffScreen();
void shutdown(int exitNum);
void fillAsteroidVector(int numOfAsteroid , int theWidth, int theHeight, asteroidType theAsteroidType, sf::Texture & theTexture);
void createSmallerAsteroids(int indexOfAsteroid, sf::Texture smallerTextureAstroid);
void moveasteroids();
void reinitializeOffscreenAsteroids();
void fillBulletVector(int numberOfBullets, sf::Texture & textureOfBullet);
void refillAsteroidVectors(int createThisManyAsteroids, int theWidth, int theHeight, asteroidType asteroidType, sf::Texture & theTexture);
void getTwoDirectionsFromMajorDirection(asteroidMovement & theMajorDirection, asteroidMovement & smallAsteroidDirection1, asteroidMovement & smallAsteroidDirection2);



/////////!!!!!!!!!!!!!!!!!!


//put here together because smallerTextureAsteroid used in: checkCollisionsaAllBulletsWithAnAsteroid 
sf::Texture largerTextureAsteroid;
sf::Texture smallerTextureAsteroid;
sf::Texture texturebullet;
sf::Font fontForScore;

//initialized of the vectors for asteroids
std::vector<asteroid> asteroidCollection;
std::vector <bullet> bullets;
score theScore(10, 10);
sf::Event event;
sf::RenderWindow window(sf::VideoMode(G_SCREEN_WIDTH, G_SCREEN_HEIGHT), "Asteroids!");


//global ship pbject
ship shipObject(500, 500, up);
levelObj levelObject;




//GLOBAL FUNCTION DEFINITIONS FOLLOW:

void drawShip(void){


	window.draw(shipObject.shipImage);
	
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


	//is off screen returns false
	if (checkForShipOnBorder(x, y) == false)
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
void checkCollisionsShipWithAsteroids() 
{


	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
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
		

		if (asteroidCollection[j].getActivate() != onscreen )
		{
			continue;
		}

		for (int i = 0; i < levelObj::getMaxNumBullets(); i++)
		{


			if (!bullets[i].getIsactive())
			{
				continue;
			}





			if (bullets[i].intersects(asteroidCollection[j]))
			{
				



				//bullet is used and not active until refired
				bullets[i].setIsactive(false);
				
				//asteroid is destroyed and is used later after level is passed in advanceLevelByOne 
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

		
}




int shoot(void) 
{

	

	int i = 0;
	
	
	int numOfBulletIndex = -1;
	

		//static function
 		for (int i = 0; i < levelObj::getMaxNumBullets(); i++)
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


		//to make all the following member function simpler, uses bulletIndex instead
		bullet & bulletIndex = bullets[numOfBulletIndex];
			
		//pre condition : bullet is smaller in width and height than asteroid
		//up key pressed direction of bullet will be upwards.  creates a bullet the same amount 
		//away for each off the four directions shot
		//for now, the bullets width is 16 and its height is 16.  values are divided by 2 to center the diferent images
			if (shipObject.getDirection() == up)
			{


				int centerShipWidth = .5* shipObject.getWidth();
				int centerBulletWidth = .5* bulletIndex.getWidth();
				

				//bullet center of ship
				bulletIndex.setX(shipObject.getX() + centerShipWidth - centerBulletWidth);
				
				//bullet a bit above ship
				//the four of these start from the circles most farthest boundry and add 100
				bulletIndex.setY(-100 + shipObject.getY() + shipObject.getHeight());

			
				bulletIndex.setDirection(shipObject.getDirection());
				//sets the position of the bullet with x and y coordinates
				bulletIndex.bulletImage.setPosition(sf::Vector2f(bulletIndex.getX(), bulletIndex.getY()));

				window.draw(bulletIndex.bulletImage);

				//there are three speeds so far: bullet, ship, and asteroids
				//sets bullet speed to downward 5 per cycle.
				bulletIndex.setDeltaX(0);
				bulletIndex.setDeltaY(-5);
				bulletIndex.setIsactive(true);
				

			}
			

			else if (shipObject.getDirection() == right) 
			{

				
				int centerShipHeight = .5* shipObject.getHeight();
				int centerBulletHeight = .5* bulletIndex.getHeight();

				//the four of these start from the circles most farthest boundry and add 100
				bulletIndex.setX(shipObject.getX() + 100);
				//bullet a bit above ship
				bulletIndex.setY(shipObject.getY() + centerShipHeight - centerBulletHeight);

			
				bulletIndex.setDirection(shipObject.getDirection());
				//sets the position of the bullet with x and y coordinates
				bulletIndex.bulletImage.setPosition(sf::Vector2f(bulletIndex.getX(), bulletIndex.getY()));

				window.draw(bulletIndex.bulletImage);

				//sets bullet x speed at a change of 5.
				bulletIndex.setDeltaX(5);
				bulletIndex.setDeltaY(0);
				bulletIndex.setIsactive(true);
				

			}
			//ship is moving downward 
			else if (shipObject.getDirection() == down) 
			{

				int centerShipWidth = .5* shipObject.getWidth();
				int centerBulletWidth = .5* bulletIndex.getWidth();
				

				//bullet is centered according to ship
				bulletIndex.setX(shipObject.getX() + centerShipWidth - centerBulletWidth);
				//the four of these start from the circles most farthest boundry and add 100
				bulletIndex.setY(100 + shipObject.getY());
				//direction for move bullet
				bulletIndex.setDirection(shipObject.getDirection());
				//sets the position of the bullet with x and y coordinates
				bulletIndex.bulletImage.setPosition(sf::Vector2f(bulletIndex.getX(), bulletIndex.getY()));
				//bullet image is part of SFML basic instructions on website tutorial questions
				window.draw(bulletIndex.bulletImage);
				bulletIndex.setDeltaX(0);
				//sets change of speed to 5 for each cycle through
				bulletIndex.setDeltaY(5);
				bulletIndex.setIsactive(true);
				

			}
			//ship is moving left so bullet will be left of ship
			else if (shipObject.getDirection() == left) 
			{

				
				int centerShipHeight = .5* shipObject.getHeight();
				int centerBulletHeight = .5* bulletIndex.getHeight();

				//the four of these start from the circles most farthest boundry and add 100
				bulletIndex.setX(shipObject.getX() + shipObject.getWidth() - 100 );
				//bullet a bit above ship
				bulletIndex.setY(shipObject.getY() + centerShipHeight  - centerBulletHeight);

				//direction set to left for moving/drawing bullet
				bulletIndex.setDirection(shipObject.getDirection());
				//sets the position of the bullet with x and y coordinates
				bulletIndex.bulletImage.setPosition(sf::Vector2f(bulletIndex.getX(), bulletIndex.getY()));

				window.draw(bulletIndex.bulletImage);
				//change is 5 per cycle of main
				bulletIndex.setDeltaX(-5);
				bulletIndex.setDeltaY(0);
				bulletIndex.setIsactive(true);
				


			}

		

			return(1);
}

//move the bullets and if still on screen draw them
void movebullets(void) 
{

	int returnValue = 0;

	//static function
	for (int i = 0; i < levelObj::getMaxNumBullets(); i++)
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


	
}

//if the bullet is off the screen it is set as inactive so that it will not be drawn
//The drawing function will check to see if the bullet is still active.  if the bullet
//is offscreen than a return of -1 means that the bullet will not be drawn in the movebullets
//function.  The screenWidth and screenHeight is used to check if the image is totally off the screen!
int checkForBulletOffscreen(int index) 
{

	if (!(bullets[index].intersectsWithScreenRect(G_SCREEN_WIDTH, G_SCREEN_HEIGHT)))
	{
		bullets[index].setIsactive(false);
		return(-1);
	}
	
	return(1);
}

//The function checks if the asteroid is totally off the screen. If it is the asteroid 
//is set as offscreen which means it is not being drawn.  Later we look at the activation of
//offscreen to reinitialize and set back to onscreen so that it will be drawn.
void checkForAsteroidOffScreen()
{

	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{


		if (!(asteroidCollection[i].intersectsWithScreenRect( G_SCREEN_WIDTH, G_SCREEN_HEIGHT)))
		{

			asteroidCollection[i].setActivate(offscreen);
		}

	}
	
}

//checks if ship is at passed or on one of the four borders.  If it does, sets ship  to be at border's 
//edge and returns a negative one which means no movement in the calling function : mopveShip(...)
bool checkForShipOnBorder(int x, int y)
{


	//left
	if (x < 0 )
	{
		shipObject.setX(0);
		
		return(false);

	}
	//right
	if (x  > (G_SCREEN_WIDTH - shipObject.getWidth())) 
	{
		shipObject.setX(G_SCREEN_WIDTH - shipObject.getWidth());
		return(false);

	}
	//bottom
	if (y > (G_SCREEN_HEIGHT - shipObject.getHeight()))
	{
		shipObject.setY(G_SCREEN_HEIGHT - shipObject.getHeight());
		return(false);

	}
	//top
	if (y < 0 ) 
	{
		shipObject.setY(0);
		return(false);

	}


	return(true);
}


// To look at later, we need to deal with the shutdown of the three vectors:
// large asteroids, small asteroids, bullet and the deconstruction where it
// needs to be considered. 
void shutdown(int exitNum) 
{

	exit(exitNum);

}


//fills the asteroid vector with initialized asteroids. asterType is the type of the asteroid.
void fillAsteroidVector(int numAsteroid,  int width, int height, asteroidType asterType,  sf::Texture & texture) {

	// for random direction
	int j = 0;
	//g_TotalAsteroids is the total number of asteroids : already created plus newly added that we are adding
	//right now
	int g_TotalAsteroids = g_TotalNumAllAsteroids + numAsteroid;

	//g_TotalNumAllAsteroids increases whenever ther is a new asteroid creation 
	//(from push_back)
	for (std::size_t i = asteroidCollection.size(); i < g_TotalAsteroids; i++)
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


}

// indexOfAsteroid is the index of the large asteroid that has been shot with a bullet and
// is being replaced on the screen with the two smaller asteroids that are to be activate
// (onscree) here.  They were set to intialize in fillAsteroidVectors and refillAsteroidVectors.
// Called from checkCollisionsaAllBulletsWithAnAsteroids.
void createSmallerAsteroids(int indexOfAsteroid, sf::Texture smallerTextureAst)
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
	for (std::size_t i = 0 ; i < asteroidCollection.size(); i++)
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
			break;// i = g_TotalNumAllAsteroids;
		}
	}

	for (std::size_t j = 0; j < asteroidCollection.size(); j++)
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
			break;// j = g_TotalNumAllAsteroids;


		}
	}
	
	//somethings wrong, this function was called and there are no 2 new asteroids readied
	//as initialized
	if (flagUnusedAsteroidIndexFound != 2)
	{
		shutdown(-5);
	}
	
	
	
	
	//diameter of smaller circle is 32
	//The larger asteroid in the remaining code is the asteroidCollection with the indes : indexOfAsteoid
	//center of little asteroid is located with it's center on the top horizontal tangent of larger asteroid
	
	//to simple the four assignments of x and y below:
	asteroid & smallAsteroid1 = asteroidCollection[indexNextSmallerAsteroid1];
	asteroid & smallAsteroid2 = asteroidCollection[indexNextSmallerAsteroid2];
	//asteroid & largeAsteroid = asteroidCollection[indexOfAsteroid];
	int largeAsteroidLeft = asteroidCollection[indexOfAsteroid].getX();
	int largeAsteroidWidth = asteroidCollection[indexOfAsteroid].getWidth();
	int largeAsteroidHeight = asteroidCollection[indexOfAsteroid].getHeight();
	int largeAsteroidTop = asteroidCollection[indexOfAsteroid].getY();
	int smallAsteroid1Height = (asteroidCollection[indexNextSmallerAsteroid1].getHeight());
	int smallAsteroid2Height = (asteroidCollection[indexNextSmallerAsteroid2].getHeight());
	int smallAsteroid1Width = (asteroidCollection[indexNextSmallerAsteroid1].getWidth());
	int smallAsteroid2Width = (asteroidCollection[indexNextSmallerAsteroid2].getWidth());
	
	//For the next four assignments, the small asteroid's center is at the top horizontal tangent of the larger asteroid.
	//The math here is interesting: the width of the larger asteroid minus the width of the smaller 
	//asteroid leaves us with the remaining width space on both the right and left of the small asteroid.
	//We than divide this space by two to get the smaller asteroid positioned at the center horizontally.
	//if needed, easier to draw out on paper.

	smallAsteroid1.setX(largeAsteroidLeft + ((largeAsteroidWidth - smallAsteroid1Width) / 2));
	smallAsteroid1.setY(largeAsteroidTop - ((largeAsteroidHeight - smallAsteroid2Height) / 2));
	smallAsteroid2.setX(largeAsteroidLeft + ((largeAsteroidWidth - smallAsteroid2Width) / 2));
	smallAsteroid2.setY(largeAsteroidTop + ((largeAsteroidHeight - smallAsteroid2Height) / 2));


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
	
}

//Checks if all large and small asteroids are destroyed 
int checkAllAsteroidsDestroyed()
{

	int asteroidCount = 0;
	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
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

	



//if the asteroid is onscreen it is either a large asteroid that is initialized 
//or reinitialized which means its waiting behind the border to be drawn and moved.
//It could also be on the screen ..."onscreen"
//if it is a small asteroid it is onscreen if it has been created with :
//createsmallasteroids.
void moveasteroids()
{

	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{

		if (asteroidCollection[i].getActivate() == onscreen)
		{



			asteroidCollection[i].moveAsteroid();
			window.draw(asteroidCollection[i].anAsteroid);


		}


	}


	
}


//check for all asteroids offscreen and set them up for moving putting them 
//their height or their width behind the four screen borders so that there 
//ready but just unvisable.
void reinitializeOffscreenAsteroids()
{
	
	for (std::size_t i = 0; i < asteroidCollection.size(); i++)
	{
		if (asteroidCollection[i].getActivate() == offscreen)
		{
			int randNum = std::rand() % (4);

			//resets asteroid to onscreen for draw and move.
			//this is used for both large and small asteroids and is not the same
			//as when (two) asteroids are created in the createSmallerAsteroids called
			//in checkCollisionsAllBullets...
			asteroidCollection[i].setInitialAsteroid(randNum);
		}

	}
	
}


//fills vector with numOfBullets and fills the vector.  Lastly, sets 
//the static variaable.
void fillBulletVector (int numOfBullets, sf::Texture & texture)
{

	
	
	for (int i = 0; i < numOfBullets ; i++)
	{
		
		bullets.push_back( bullet(texture, 16, 16));
	
	}

	

	
}






int main(void)
{
	
	
	//seeds the time for random direction and postion of asteroids right before drawing on screen
	std::srand(time(NULL));
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
	fillAsteroidVector(levelObject.getNumLargeAsteroids(), 64, 64, larger, largerTextureAsteroid);
	fillAsteroidVector(levelObject.getNumSmallAsteroids(), 32, 32, smaller, smallerTextureAsteroid);
	
	
	//this will set the vector to 10 bullets index  of 9 of course
	fillBulletVector(levelObject.getMaxNumBullets(), texturebullet);
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
			
			//holds this levels value because they are changed in advanceLevelByOne for RefillAsteroidVector
			int oldLevelsSmallAsteroidAmt = levelObject.getNumSmallAsteroids();
			int oldLevelsLargeAsteroidAmt = levelObject.getNumLargeAsteroids();

				
			//new amounts of new asteroids are set in getNumSmallAsteroids() and getNumLargeAsteroids
			levelObject.advanceLevelByOne();
				





				//break out of first while if set in level::advancelevelbyone and end program 
				if (g_Shutdownflag == 1)
				{
					continue;
				}

				//fills one asteroid collection with two statements.
				//oldLevels... getNumSmallAsteroids() and .getNumLargeAsteroids() are new levels values
				//the new levels minus the old levels gives us the new asteroids to create
				int createThisAmtAsteroids = (levelObject.getNumLargeAsteroids() - oldLevelsLargeAsteroidAmt);
				//creates the newly created asteroids with push_back and reinitializes the older asteroids
				//with a new active setting
				refillAsteroidVectors(createThisAmtAsteroids, 64, 64, larger, largerTextureAsteroid);
				//see right above
				createThisAmtAsteroids = levelObject.getNumSmallAsteroids() - oldLevelsSmallAsteroidAmt;
				//same as above : just a smaller asteroid group for the collection
				refillAsteroidVectors(createThisAmtAsteroids, 32, 32, smaller, smallerTextureAsteroid);

				
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
void refillAsteroidVectors(int numAsteroidsToCreate, int Width, int Height, asteroidType type , sf::Texture & texture)
{
	int j = 0;
	if (type == larger)
	{
		for (int i = 0; i < numAsteroidsToCreate; i++)
		{
			//create the new additional asteroids 
			asteroidCollection.push_back(asteroid(Width, Height, texture, larger));
			g_TotalNumAllAsteroids++;
		}
		for (std::size_t i = 0; i < asteroidCollection.size(); i++)
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
		for (int i = 0; i < numAsteroidsToCreate; i++)
		{
				//creates extra small asteroids
				asteroidCollection.push_back(asteroid(Width, Height, texture, smaller));
				g_TotalNumAllAsteroids++;
		}
		//reinitalizes the old and new asteroids with the new activation so that they
		//can be moved after their changed from initialized to onscreen in createsmallasteroids
		for (std::size_t i = 0; i < asteroidCollection.size(); i++)
		{

			if (asteroidCollection[i].getAsteroidType() == smaller)
			{
				
				asteroidCollection[i].setActivate(initialized);
			}
		}
	}

	
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

