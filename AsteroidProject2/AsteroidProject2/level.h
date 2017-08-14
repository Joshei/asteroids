class levelObj {

public:
	levelObj();
	
	int getNumLargeAsteroids();
	int getNumSmallAsteroids();

	void advanceLevelByOne();

	static int maxBullets;

	static void setMaxNumBullets(int maxNumBullets);

	static int getMaxNumBullets()
	{
		return maxBullets;
	}
private:

	int levelNumber;
	int numOfSmallAsteroids;
	int numOfLargeAsteroids;



};