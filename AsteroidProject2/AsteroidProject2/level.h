class levelObj {

public:
	levelObj();
	
	
	static int maxBullets;
	
	void AdvanceLevelByOne();
	
	int GetNumLargeAsteroids(){return numOfLargeAsteroids;}

	int GetNumSmallAsteroids(){return numOfSmallAsteroids;}

	static int GetMaxNumBullets(){return maxBullets;}


private:

	int levelNumber;
	int numOfSmallAsteroids;
	int numOfLargeAsteroids;



};