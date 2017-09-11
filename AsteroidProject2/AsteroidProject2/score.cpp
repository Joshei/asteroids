#include "score.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>



score::score(int xpos, int ypos )
:scoreamount(0)
{
	scoreposition.x = xpos;
	scoreposition.y = ypos;
}


void score::SetFont(sf::Font & theFont)
{
	Textmessage.setFont(theFont);


	
}

void score::SetScore(int score)
{
	scoreamount = score;
}

void score::SetXForScore(int x)
{
	scoreposition.x = x;

}
void score::SetYForScore(int y)
{
	scoreposition.y = y;
}


//draws the score of the parameter and sets the scoreAmount variable
void  score::DrawScore(int score)
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
void score::DrawScore()
{
	DrawScore(scoreamount);
	
}



void score::AddToScore(int addamount)
{
	scoreamount += addamount;


	
}



void score::ResetScore()
{

	scoreamount = 0;

}


