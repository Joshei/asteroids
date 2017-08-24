#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>



class score {

public:

	
	
	score(int xpos, int ypos);
	void SetFont(sf::Font & theFont);
	void SetScore(int scoreIn);
	void SetXForScore(int xDimension);
	void SetYForScore(int yDimension);
	void DrawScore(int score);
	void DrawScore();
	void AddToScore(int addAmount);
	void ResetScore();
	int GetScore(){return scoreamount;}
	int GetXForScore(){return scoreposition.x;}
	int GetYforScore(){return scoreposition.y;}
	

	sf::Text & getTextMessage(){return textMessage;}

	
	
	
	
	
	
	
	
private:
	
	
	//sfml object:  holds the score message and the sf::Font is passed in to it from outside class
	sf::Text textMessage;

	int scoreamount;
	//these two positions are for the upper left hand corner of the text
	struct{
		int x;
		int y;
	}scoreposition;
	
	

};

#endif /* SCORE_H */