#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define SPEED 200

int main()
{
	sf::IpAddress inputAddress;
	sf::TcpSocket socket;
	short port = 53000;
	char userType = '?';

	sf::Vector2f myPos, theirPos, puckPos;
	int lastDir = 1;
	int theirLastDir = 1;
	float puckY = 0.1;
	sf::Clock dtClock;
	float dt = 1.0f;


	srand((unsigned)time(NULL));

	sf::Font font;

	if (!font.loadFromFile("arial.ttf"))
	{
		//oh no :(
	}

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(200.f,32.f);

	int scores[2] = {0 , -1};

	do
	{
		std::cout << "Enter s for server player or c for client player - ";
		std::cin >> userType;
		std::cout << "Thanks...";

		if (userType == 's')
		{
			sf::TcpListener listener;
			listener.listen(port);
			listener.accept(socket);
			std::cout << "\nWelcome to Pong, Server Player\n";
			myPos = sf::Vector2f(10.0f,112.5f);
		}
		else if (userType == 'c') {
			std::cout << "\nEnter the Address of Server: ";
			std::cin >> inputAddress;
			std::cout << "\nThanks, Client Player\n";

			sf::Socket::Status status = socket.connect(inputAddress, 53000);
			if (status != sf::Socket::Done)
			{
				std::cout << "Hmmm... Couldn't connect. Please try again!\n";
				userType = '?';
			}
			else {
				std::cout << "Connected to Server Player!\n";
				myPos = sf::Vector2f(380.0f, 112.5f);
			}
		}
		else {
			std::cout << "\nError! Invalid user type. Please try again.\n";
		}
	}while (userType != 's' && userType != 'c');

	std::cout << "Let us...!\n";
	


	sf::RenderWindow window(sf::VideoMode(400, 225), "Pong!");

	sf::RectangleShape myPaddle;
	myPaddle.setSize(sf::Vector2f(10.0f, 40.0f));
	myPaddle.setFillColor(sf::Color::Green);
	myPaddle.setPosition(myPos);

	sf::RectangleShape theirPaddle;
	theirPaddle.setSize(sf::Vector2f(10.0f, 40.0f));
	theirPaddle.setFillColor(sf::Color::Red);

	sf::RectangleShape puck;
	puck.setSize(sf::Vector2f(10.0f, 10.0f));
	puck.setFillColor(sf::Color::Blue);
	puck.setPosition(sf::Vector2f(200.f,200.f));

	std::cout << "PONG!\n";

	bool update = false;
	sf::Vector2f puckDir = sf::Vector2f(-1.0, 0.0);

	//Game Loop
	while (window.isOpen())
	{
		//SFML Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

	//		if (event.type == sf::Event::GainedFocus)
		//	{ 
		//		update = true;
		//	}

		//	if (event.type == sf::Event::LostFocus)
		//	{
		//		update = false;
		//	}
		}

		dt = dtClock.restart().asSeconds();

		//if (update)
		//{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && myPaddle.getPosition().y > 0)
			{
				lastDir = -1;
				myPaddle.move(sf::Vector2f(0.0f, -500.0f * dt));

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && myPaddle.getPosition().y < 180)
			{
				lastDir = 1;
				myPaddle.move(sf::Vector2f(0.0f, 500.0f * dt));
			}
	//	}

		//The worst code youve seen in your life
		if (userType == 's')
		{
			if ( puck.getPosition().x <= 20.0f && puck.getPosition().y >= myPaddle.getPosition().y - 10.0f && puck.getPosition().y <= (myPaddle.getPosition().y + 40))
			{
				puckY = (1.f * lastDir) + rand()%3 + 0.1;
				puckDir = sf::Vector2f(1.0f, puckY);
			}else if (puck.getPosition().x >= 370.0f && puck.getPosition().y >= theirPaddle.getPosition().y - 10.0f && puck.getPosition().y <= (theirPaddle.getPosition().y + 40))
			{
				puckY = (1.f * theirLastDir) + rand()%3 + 0.1;
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
		packet << myPaddle.getPosition().x << myPaddle.getPosition().y << puck.getPosition().x << puck.getPosition().y << lastDir << scores[0] << scores[1];

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
				theirPaddle.setPosition(theirPos.x, theirPos.y);
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
		window.draw(myPaddle);
		window.draw(theirPaddle);
		window.draw(puck);
		window.draw(scoreText);
		window.display();
		
	}

	std::cout << "End\n";
	return 0;
}