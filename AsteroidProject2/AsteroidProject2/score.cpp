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
	textMessage.setFont(theFont);


	
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

	std::string scoreString("Score :  ");
	std::string thisString = std::to_string(score);
	scoreString = scoreString + thisString;
	textMessage.setCharacterSize(24);
	textMessage.setFillColor(sf::Color::Red);
	textMessage.setStyle(sf::Text::Bold);
	textMessage.setPosition(10, 50);
	scoreamount = score;
	textMessage.setString(scoreString);

	

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


