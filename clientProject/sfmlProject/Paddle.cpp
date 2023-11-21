#include "Paddle.h"

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
