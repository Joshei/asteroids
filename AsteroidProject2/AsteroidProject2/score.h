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
	int GetScore(){return scoreAmount;}
	int GetXForScore(){return scorePosition.x;}
	int GetYforScore(){return scorePosition.y;}
	

	sf::Text & getTextMessage(){return textMessage;}

	
	
	
	
	
	
	
	
private:
	
	
	//sfml object:  holds the score message and the sf::Font is passed in to it from outside class
	sf::Text textMessage;

	int scoreAmount;
	//these two positions are for the upper left hand corner of the text
	struct{
		int x;
		int y;
	}scorePosition;
	
	

};

#endif /* SCORE_H */