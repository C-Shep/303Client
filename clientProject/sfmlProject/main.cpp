#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Paddle.h"

#define SPEED 200

//Setup the connection, includes setting up server and connecting with the client. Using TCP connection as UDP isn't really needed with the simplicity of the game.
char connectionSetup(char type, sf::Vector2f pos, sf::TcpSocket &sock)
{
	short port = 53000;

	do
	{
		std::cout << "Enter s for server player or c for client player - ";
		std::cin >> type;
		std::cout << "Thanks...";
	
		if (type == 's')
		{
			sf::IpAddress ip = sf::IpAddress::getLocalAddress();

			std::cout << "\nWelcome to Pong, Server Player. Your IP Address is: " << ip << "\n";
			std::cout << "Waiting for Client Player to Connect...\n";
			sf::TcpListener listener;
			listener.listen(port);
			listener.accept(sock);
		}
		else if (type == 'c') {
			sf::IpAddress inputAddress;
			std::cout << "\nEnter the Address of Server: ";
			std::cin >> inputAddress;
			std::cout << "\nThanks, Client Player\n";

			sf::Socket::Status status = sock.connect(inputAddress, 53000);
			if (status != sf::Socket::Done)
			{
				std::cout << "Hmmm... Couldn't connect. Please try again!\n";
				type = '?';
			}
			else {
				std::cout << "Connected to Server Player!\n";
				
			}
		}
		else {
			std::cout << "\nError! Invalid user type. Please try again.\n";
		}
	} while (type != 's' && type != 'c');

	return type;
}

//Set starting position for player
sf::Vector2f getStartPos(char type)
{
	sf::Vector2f pos;
	if (type == 's')
	{
		pos = sf::Vector2f(10.0f, 112.5f);
	}
	else {
		pos = sf::Vector2f(380.0f, 112.5f);
	}
	return pos;
}

//load font
sf::Font setupFont(sf::Font fnt, std::string file)
{
	if (!fnt.loadFromFile(file))
	{
		//oh no :(
	}
	return fnt;
}

//create a rectange shape. Used for both players and the puck.
sf::RectangleShape createShape(sf::Vector2f size, sf::Color colour, sf::Vector2f pos)
{
	sf::RectangleShape shape;
	shape.setSize(size);
	shape.setFillColor(colour);
	shape.setPosition(pos);

	return shape;
}

//Deal with any SFML Events
void eventManager(sf::RenderWindow &window)
{
	sf::Event evnt;

	while (window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
		{
			window.close();
		}

		//	if (event.type == sf::Event::GainedFocus)
		//	{ 
		//		imHim = true;
		//	}

		//	if (event.type == sf::Event::LostFocus)
		//	{
		//		imHim = false;
		//	}
	}
}

void playerMove(int lastDir)
{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && myPaddle.getPosition().y > 0)
//	{
//		lastDir = -1;
//		myPaddle.move(sf::Vector2f(0.0f, -500.0f * dt));
//
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && myPaddle.getPosition().y < 180)
//	{
//		lastDir = 1;
//		myPaddle.move(sf::Vector2f(0.0f, 500.0f * dt));
//	}
}

int main()
{
	//Create the TCP Sockets
	sf::TcpSocket socket;

	//Create a Vector for the Players Position, the Opponents Position and the Pucks Position
	sf::Vector2f myPos, theirPos, puckPos;

	//The Last direction each player has moved in
	int lastDir = 1;
	int theirLastDir = 1;

	//Setup Delta Time
	sf::Clock dtClock;
	float dt = 1.0f;
	srand((unsigned)time(NULL));

	//Setup Text For Score
	sf::Font font;
	font = setupFont(font,"arial.ttf");
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(200.f, 32.f);

	//Scores for each player, puck is created at 0,0 by default which scores automatically so player 2s score has to start at -1 to make it 0 when the puck is made
	int scores[2] = { 0 , -1 };

	//Setup the connection between server player and client player
	//Usertype determines if the user is server or client side
	char userType = '?';
	userType = connectionSetup(userType, myPos, socket);

	//set the starting position of your paddle based on usertype
	myPos = getStartPos(userType);

	std::cout << "Pong Time Start!\n";
	
	//Create the Game Window
	sf::RenderWindow window(sf::VideoMode(400, 225), "Pong!");

	//Create the 3 main objects, the Players Paddle, the Opponents Paddle and the Puck
	Paddle myPaddle;
	Paddle theirPaddle;

	//sf::RectangleShape myPaddle;
	myPaddle.createShape(sf::Vector2f(10.0f, 40.0f), sf::Color::Green, myPos);

//	sf::RectangleShape theirPaddle;
	theirPaddle.createShape(sf::Vector2f(10.0f, 40.0f), sf::Color::Red, theirPos);

	sf::RectangleShape puck;
	sf::Vector2f puckStart = sf::Vector2f(200.f, 200.f);
	puck = createShape(sf::Vector2f(10.0f, 10.0f), sf::Color::Blue, puckStart);
	
	float puckY = 0.0f;//The Y direction of the Puck
	sf::Vector2f puckDir = sf::Vector2f(-1.0, puckY);//The Pucks movement vector

	//DEBUG
	bool imHim = false;

	//Game Loop
	while (window.isOpen())
	{
		//SFML Events
		eventManager(window);

		dt = dtClock.restart().asSeconds();

		//if (imHim)
		//{
		myPaddle.movement(dt);
		//}

		//The worst code youve seen in your life
		if (userType == 's')
		{
			float offset = 10.0f;

			if ( puck.getPosition().x <= myPaddle.getPaddlePos().x + offset && puck.getPosition().y >= myPaddle.getPaddlePos().y - 10.0f && puck.getPosition().y <= (myPaddle.getPaddlePos().y + 40))
			{
				puckY = (1.f * lastDir) + rand()%3 + 0.1;
				puckDir = sf::Vector2f(1.0f, puckY);
			}else if (puck.getPosition().x >= theirPaddle.getPaddlePos().x - offset && puck.getPosition().y >= theirPaddle.getPaddlePos().y - 10.0f && puck.getPosition().y <= (theirPaddle.getPaddlePos().y + 40))
			{
				puckY = (1.f * theirLastDir) - rand()%3 + 0.1;
				puckDir = sf::Vector2f(-1.f, puckY);
			}

			if (puck.getPosition().y > 215.f || puck.getPosition().y < 0.f)
			{
				puckDir.y *= -1;
				if (puck.getPosition().y < 0.f)
				{
					puck.setPosition(puck.getPosition().x, 1.f);
				}
				else {
					puck.setPosition(puck.getPosition().x, 214.f);
				}
				
			}

			puck.setPosition(puck.getPosition().x + (puckDir.x*SPEED)*dt, puck.getPosition().y + (puckDir.y * SPEED)* dt);
			
			if (puck.getPosition().x < 0.0f || puck.getPosition().x > 400.0f)
			{
				if (puck.getPosition().x < 0.0f)
				{
					scores[1] += 1;
				}
				else 
				{
					scores[0] += 1;
				}
				puck.setPosition(200.0f, 112.5f);
			}
		}

		//Packet
		sf::Packet packet;
		packet << myPaddle.getPaddlePos().x << myPaddle.getPaddlePos().y << puck.getPosition().x << puck.getPosition().y << lastDir << scores[0] << scores[1];

		//Send my data to the server
		if (socket.send(packet) != sf::Socket::Done)
		{
			std::cout << "Error, Can't sent packet to other player :(\n";
		}

		if (socket.receive(packet) == sf::Socket::Done)
		{
			int tempScores[2];
			if (packet >> theirPos.x >> theirPos.y >> puckPos.x >> puckPos.y >> theirLastDir >> tempScores[0] >> tempScores[1])
			{
				theirPaddle.setPaddlePos(theirPos.x, theirPos.y);
				if (userType == 'c')
				{
					puck.setPosition(puckPos.x, puckPos.y);
					scores[0] = tempScores[0];
					scores[1] = tempScores[1];
				}
			}
		}

		std::string s = std::to_string(scores[0]);
		std::string ss = std::to_string(scores[1]);


		scoreText.setString(s + "/" + ss);

		window.clear();
		window.draw(myPaddle.getPaddle());
		window.draw(theirPaddle.getPaddle());
		window.draw(puck);
		window.draw(scoreText);
		window.display();
		
	}

	std::cout << "End\n";
	return 0;
}