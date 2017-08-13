#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>

class score {

public:

	//sfml object:  holds the score message and the sf::Font is passed in to it from outside class
	sf::Text textMessage;
	
	
	score(int xpos , int ypos );
	void setFont(sf::Font & theFont);
	void setScore(int scoreIn);
	void setXForScore(int xDimension);
	void setYForScore(int yDimension);
	int getScore() { return scoreAmount; }
	int getXForScore() { return scorePosition.x; }
	int getYforScore() { return scorePosition.y; }
	
	void resetScore(void);
	void drawScore(int score);
	void drawScore(void);
	void addToScore(int addAmount);
	
	
	
	sf::Text & getTextMessage() { return textMessage; }
	
	
private:
	
	
	int scoreAmount;
	//these two positions are for the upper left hand corner of the text
	struct {
		int x;
		int y;
	}scorePosition;
	
	

};

#endif /* SCORE_H */