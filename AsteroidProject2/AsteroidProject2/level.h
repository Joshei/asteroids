class levelObj {

public:
	levelObj(void);
	
	int getNumLargeAsteroids();
	int getNumSmallAsteroids();

	int advanceLevelByOne();

	static int maxBullets;

	static void setMaxNumBullets(int maxNumBullets);
	static int getMaxNumBullets(void)
	{
		return maxBullets;
	}
private:

	int levelNumber;
	int numOfSmallAsteroids;
	int numOfLargeAsteroids;



};