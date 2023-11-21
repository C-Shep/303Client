#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:
	Paddle();
	~Paddle();

	void movement(float dt);
	sf::RectangleShape getPaddle();
	sf::Vector2f getPaddlePos();
	void setPaddlePos(float xx, float yy);
	void createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos);

	float getLastDir();

private:
	sf::RectangleShape paddle;
	int lastDir = 1;
};