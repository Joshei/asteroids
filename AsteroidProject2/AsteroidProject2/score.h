#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>



class score {

public:

	
	
	score(int xpos, int ypos);
	void SetFont(sf::Font & Thefont);
	void SetScore(int scorein);
	void SetXForScore(int xdimension);
	void SetYForScore(int ydimension);
	void DrawScore(int score);
	void DrawScore();
	void AddToScore(int addamount);
	void ResetScore();
	int GetScore(){return scoreamount;}
	int GetXForScore(){return Scoreposition.x;}
	int GetYforScore(){return Scoreposition.y;}
	

	sf::Text & getTextMessage(){return Textmessage;}

	
	
	
	
	
	
	
	
private:
	
	
	//sfml object:  holds the score message and the sf::Font is passed in to it from outside class
	sf::Text Textmessage;

	int scoreamount;
	//these two positions are for the upper left hand corner of the text
	struct{
		int x;
		int y;
	}Scoreposition;
	
	

};

#endif /* SCORE_H */