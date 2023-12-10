#include "Paddle.h"

Paddle::Paddle()
{

}

Paddle::~Paddle()
{

}

//Move up and down within the game area
void Paddle::movement(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle.getPosition().y > 0)
	{
		lastDir = -1;
		paddle.move(sf::Vector2f(0.0f, -500.0f * dt));

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle.getPosition().y < 180)
	{
		lastDir = 1;
		paddle.move(sf::Vector2f(0.0f, 500.0f * dt));
	}
}

sf::RectangleShape Paddle::getPaddle()
{
	return paddle;
}

sf::Vector2f Paddle::getPaddlePos()
{
	return paddle.getPosition();
}

void Paddle::setPaddlePos(float xx, float yy)
{
	paddle.setPosition(xx, yy);
}

//create a rectange shape.
void Paddle::createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos)
{
	paddle.setSize(size);
	paddle.setFillColor(colour);
	paddle.setPosition(pos);

}

float Paddle::getLastDir()
{
	return lastDir;
}

sf::Vector2f Paddle::prediction(float gameTime) {
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = messages.size();
	if (msize < 3) {
		return sf::Vector2f(predictedX, predictedX);
	}
	const PaddleMessage& msg0 = messages[msize - 1];
	const PaddleMessage& msg1 = messages[msize - 2];
	const PaddleMessage& msg2 = messages[msize - 3];

	// FIXME: Implement prediction here!
	// You have:
	// - the history of position messages received, in "m_Messages"
	//   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
	// - the current time, in "gameTime"
	//
	// You need to update:
	// - the predicted position at the current time, in "predictedX" and "predictedY"

	float spdX = (msg0.x - msg1.x) / (msg0.time);
	float spdY = (msg0.y - msg1.y) / (msg0.time);

	float dispX = spdX * gameTime;
	float dispY = spdY * gameTime;

	predictedX = msg0.x + dispX;
	predictedY = msg0.y + dispY;

	return sf::Vector2f(predictedX, predictedY);
}