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

sf::Vector2f Puck::prediction(float gameTime)
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = messages.size();

	if (msize < 2)
	{
		return sf::Vector2f(predictedX,predictedY);
	}

	const objectMessage& msg0 = messages[msize - 1];
	const objectMessage& msg1 = messages[msize - 2];

	if ((msg0.time) - (msg1.time) > 0.f)
	{
		float spdX = (msg0.x - msg1.x) / (msg0.time) - (msg1.time);
		float spdY = (msg0.y - msg1.y) / (msg0.time) - (msg1.time);

		float dispX = spdX * gameTime;
		float dispY = spdY * gameTime;

		predictedX = msg0.x + dispX;
		predictedY = msg0.y + dispY;
	}

	if (msize > 4) {
		messages.erase(messages.begin());
	}

	if (predictedY > 200)
	{
		predictedY = 200;
	}
	else if (predictedY < 0) {
		predictedY = 0;
	}

	return sf::Vector2f(predictedX, predictedY);
}

void Puck::setPredictedPos(sf::Vector2f newPos)
{
	predictPos = newPos;
}

sf::Vector2f Puck::getPredictedPos()
{
	return predictPos;
}