class LevelObj {

public:
	LevelObj();
	
	
	static int Maxbullets;
	
	void AdvanceLevelByOne();
	
	int GetNumLargeAsteroids(){return numoflargeasteroids;}

	int GetNumSmallAsteroids(){return numofsmallasteroids;}

	static int GetMaxNumBullets(){return Maxbullets;}


private:

	int levelnumber;
	int numofsmallasteroids;
	int numoflargeasteroids;



};