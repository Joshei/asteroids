class levelObj {

public:
	levelObj();
	
	
	static int maxBullets;
	
	void AdvanceLevelByOne();
	
	int GetNumLargeAsteroids(){return numoflargeasteroids;}

	int GetNumSmallAsteroids(){return numofsmallasteroids;}

	static int GetMaxNumBullets(){return maxBullets;}


private:

	int levelnumber;
	int numofsmallasteroids;
	int numoflargeasteroids;



};