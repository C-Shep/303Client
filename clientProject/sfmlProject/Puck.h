#pragma once
#include <SFML/Graphics.hpp>
class Puck
{
public:
	Puck();
	~Puck();

	void bounceFromPaddle(float paddleX, float paddleY, float theirPaddleX, float theirPaddleY, int lastDir, int theirLastDir);
	void bounceFromWall();
	void createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos);
	
	void setYDir(float newY);
	float getYDir();

	void setDir(sf::Vector2f newDir);
	sf::Vector2f getDir();

	sf::RectangleShape getPuck();
	sf::Vector2f getPuckPos();
	void setPuckPos(float xx, float yy);

private:
	sf::RectangleShape puck;

	sf::Vector2f dir = sf::Vector2f(1.0f,0.0f);
	float YDir = -1.0f;
};

