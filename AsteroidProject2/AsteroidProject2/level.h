class levelObj {

public:
	levelObj();
	
	
	static int maxBullets;
	
	void advanceLevelByOne();
	
	int getNumLargeAsteroids(){return numOfLargeAsteroids;}

	int getNumSmallAsteroids(){return numOfSmallAsteroids;}

	static int getMaxNumBullets(){return maxBullets;}


private:

	int levelNumber;
	int numOfSmallAsteroids;
	int numOfLargeAsteroids;



};