#include "score.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>



Score::Score(int xpos, int ypos )
:scoreamount(0)
{
	Scoreposition.x = xpos;
	Scoreposition.y = ypos;
}


void Score::SetFont(sf::Font & theFont)
{
	Textmessage.setFont(theFont);


	
}

void Score::SetScore(int score)
{
	scoreamount = score;
}

void Score::SetXForScore(int x)
{
	Scoreposition.x = x;

}
void Score::SetYForScore(int y)
{
	Scoreposition.y = y;
}


//draws the score of the parameter and sets the scoreAmount variable
void Score::DrawScore(int score)
{

	std::string Scorestring("Score :  ");
	std::string Thisstring = std::to_string(score);
	Scorestring = Scorestring + Thisstring;
	Textmessage.setCharacterSize(24);
	Textmessage.setFillColor(sf::Color::Red);
	Textmessage.setStyle(sf::Text::Bold);
	Textmessage.setPosition(10, 50);
	scoreamount = score;
	Textmessage.setString(Scorestring);

	

}

//draws the current score (used after addToScore)
void Score::DrawScore()
{
	DrawScore(scoreamount);
	
}



void Score::AddToScore(int addamount)
{
	scoreamount += addamount;


	
}



void Score::ResetScore()
{

	scoreamount = 0;

}


