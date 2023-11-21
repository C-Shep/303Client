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

void Puck::bounceFromWall()
{

}

void Puck::setYDir(float newY)
{
	YDir = newY;
}

float Puck::getYDir()
{
	return YDir;
}

void Puck::setDir(sf::Vector2f newDir)
{
	dir = newDir;
}

sf::Vector2f Puck::getDir()
{
	return dir;
}

sf::RectangleShape Puck::getPuck()
{
	return puck;
}

sf::Vector2f Puck::getPuckPos()
{
	return puck.getPosition();
}

void Puck::setPuckPos(float xx, float yy)
{
	puck.setPosition(xx, yy);
}