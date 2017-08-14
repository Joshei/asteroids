#include "score.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>



score::score(int xpos, int ypos )
:scoreAmount(0)
{
	scorePosition.x = xpos;
	scorePosition.y = ypos;
}


void score::setFont(sf::Font & theFont)
{
	textMessage.setFont(theFont);


	
}

void score::setScore(int score)
{
	scoreAmount = score;
}

void score::setXForScore(int x)
{
	scorePosition.x = x;

}
void score::setYForScore(int y)
{
	scorePosition.y = y;
}


//draws the score of the parameter and sets the scoreAmount variable
void  score::drawScore(int score)
{

	std::string scoreString("Score :  ");
	std::string thisString = std::to_string(score);
	scoreString = scoreString + thisString;
	textMessage.setCharacterSize(24);
	textMessage.setFillColor(sf::Color::Red);
	textMessage.setStyle(sf::Text::Bold);
	textMessage.setPosition(10, 50);
	scoreAmount = score;
	textMessage.setString(scoreString);

	

}

//draws the current score (used after addToScore)
void score::drawScore()
{
	drawScore(scoreAmount);
	
}



void score::addToScore(int addAmount)
{
	scoreAmount += addAmount;


	
}



void score::resetScore()
{

	scoreAmount = 0;

}


