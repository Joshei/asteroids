class levelObj {

public:
	levelObj();
	
	
	static int maxbullets;
	
	void AdvanceLevelByOne();
	
	int GetNumLargeAsteroids(){return numoflargeasteroids;}

	int GetNumSmallAsteroids(){return numofsmallasteroids;}

	static int GetMaxNumBullets(){return maxbullets;}


private:

	int levelnumber;
	int numofsmallasteroids;
	int numoflargeasteroids;



};