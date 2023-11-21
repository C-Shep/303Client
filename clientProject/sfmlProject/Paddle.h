#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:
	void movement(float dt);
	sf::RectangleShape getPaddle();
	sf::Vector2f getPaddlePos();
	void setPaddlePos(float xx, float yy);
	void createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos);

	
	int lastDir = 1;

private:

	sf::RectangleShape paddle;
};