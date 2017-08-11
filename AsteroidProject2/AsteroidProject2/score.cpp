#include "score.h"
#include <iostream>
#include <conio.h>
#include <string.h>
#include <SFML/Graphics.hpp>


//x = 10 and y = 10 is good for starters
score::score(int xpos, int ypos )
:scoreAmount(0)
{
	scorePosition.x = xpos;
	scorePosition.y = ypos;
}


int score::setFont(sf::Font & theFont)
{
	textMessage.setFont(theFont);


	return(1);
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
int  score::drawScore(int score)
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

	return(1);

}

//draws the current score (used after addToScore)
int  score::drawScore(void)
{
	drawScore(scoreAmount);
	return(1);

}



int score::addToScore(int addAmount)
{
	scoreAmount += addAmount;


	return(1);
}



int score::resetScore(void) 
{

	scoreAmount = 0;
	
	return(1);
}



