#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>



class score {

public:

	
	
	score(int xpos, int ypos);
	void setFont(sf::Font & theFont);
	void setScore(int scoreIn);
	void setXForScore(int xDimension);
	void setYForScore(int yDimension);
	void drawScore(int score);
	void drawScore();
	void addToScore(int addAmount);
	void resetScore();
	int getScore(){return scoreAmount;}
	int getXForScore(){return scorePosition.x;}
	int getYforScore(){return scorePosition.y;}
	

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