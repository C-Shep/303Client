#include "Puck.h"

Puck::Puck()
{

}

Puck::~Puck()
{

}

//create a square shape.
void Puck::createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos)
{
	puck.setSize(size);
	puck.setFillColor(colour);
	puck.setPosition(pos);
}

//bouncing off of paddle
void Puck::bounceFromPaddle(float paddleX, float paddleY, float theirPaddleX, float theirPaddleY, int lastDir, int theirLastDir)
{
	float offset = 10.0f;
	float paddleLength = 40.f;

	if (puck.getPosition().x <= paddleX + offset && puck.getPosition().y >= paddleY - offset && puck.getPosition().y <= (paddleY + paddleLength))
	{
		YDir = (1.f * lastDir) + rand() % 3 + 0.1;
		dir = sf::Vector2f(1.0f, YDir);
	}
	else if (puck.getPosition().x >= theirPaddleX - offset && puck.getPosition().y >= theirPaddleY - offset && puck.getPosition().y <= (theirPaddleY + paddleLength))
	{
		YDir = (1.f * theirLastDir) -rand() % 3 + 0.1;
		dir = sf::Vector2f(-1.f, YDir);
	}
}

//bouncing off of wall
void Puck::bounceFromWall()
{
	if (puck.getPosition().y > 215.f || puck.getPosition().y < 0.f)
	{
		dir = (sf::Vector2f(dir.x, dir.y * -1));
		if (puck.getPosition().y < 0.f)
		{
			puck.setPosition(puck.getPosition().x, 5.f);
		}
		else {
			puck.setPosition(puck.getPosition().x, 214.f);
		}
	}
}

//set pucks y direction
void Puck::setYDir(float newY)
{
	YDir = newY;
}

//get pucks y direction
float Puck::getYDir()
{
	return YDir;
}

//set pucks dir
void Puck::setDir(sf::Vector2f newDir)
{
	dir = newDir;
}

//get pucks direction
sf::Vector2f Puck::getDir()
{
	return dir;
}

//get puck shape
sf::RectangleShape Puck::getPuck()
{
	return puck;
}

//get puck positon
sf::Vector2f Puck::getPuckPos()
{
	return puck.getPosition();
}

//set pucks position
void Puck::setPuckPos(float xx, float yy)
{
	puck.setPosition(xx, yy);
}