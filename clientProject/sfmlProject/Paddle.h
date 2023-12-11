#pragma once
#include <SFML/Graphics.hpp>
#include "PuckMessage.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	void movement(float dt);
	sf::RectangleShape getPaddle();
	sf::Vector2f getPaddlePos();
	void setPaddlePos(float xx, float yy);
	void setPredictedPos(float yy);
	float getPredictedPos();
	void createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos);
	float prediction(float dt);

	float getLastDir();

	sf::Vector2f lastPos;
	std::vector<objectMessage> messages;
	float lastTime;

private:
	sf::RectangleShape paddle;
	int lastDir = 1;
	
	float predictPos;
};