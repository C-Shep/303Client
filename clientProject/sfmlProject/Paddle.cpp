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

//get the paddle shape
sf::RectangleShape Paddle::getPaddle()
{
	return paddle;
}

//get the paddles position
sf::Vector2f Paddle::getPaddlePos()
{
	return paddle.getPosition();
}

//set the paddles position
void Paddle::setPaddlePos(float xx, float yy)
{
	paddle.setPosition(xx, yy);
}

//set the predicted position
void Paddle::setPredictedPos(float yy)
{
	predictPos = yy;
}

//Get the predicted position
float Paddle::getPredictedPos()
{
	return predictPos;
}

//create a rectange shape.
void Paddle::createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos)
{
	paddle.setSize(size);
	paddle.setFillColor(colour);
	paddle.setPosition(pos);
}

//Get the last moved in direction
float Paddle::getLastDir()
{
	return lastDir;
}

//Prediction for the Paddle
float Paddle::prediction(float gameTime) 
{
	float predictedY = -1.0f;

	const int msize = messages.size();

	if (msize < 2)
	{
		return predictedY;
	}

	const objectMessage& msg0 = messages[msize - 1];
	const objectMessage& msg1 = messages[msize - 2];

	if ((msg0.time) - (msg1.time) > 0.f)
	{
		float spdY = (msg0.y - msg1.y) / (msg0.time) - (msg1.time);

		float dispY = spdY * gameTime;

		predictedY = msg0.y + dispY;
	}

	if (msize > 4) {
		messages.erase(messages.begin());
	}


	if (predictedY > 180)
	{
		predictedY = 180;
	}
	else if (predictedY < 0) {
		predictedY = 0;
	}

	return predictedY;
}