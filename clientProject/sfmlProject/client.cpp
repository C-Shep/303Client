#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Player
{
	int id = 0;
	float xx = 10.0f;
	float yy = 10.0f;
};

sf::Packet& operator << (sf::Packet& packet, const Player& player)
{
	return packet << player.id << player.xx << player.yy;
}

sf::Packet& operator >> (sf::Packet& packet, Player& player)
{
	return packet >> player.id >> player.xx >> player.yy;
}

int main()
{
	sf::IpAddress inputAddress;
	sf::TcpSocket socket;
	short port = 53000;
	char userType = '?';

	sf::Vector2f myPos, theirPos;
	int lastDir = 1;
	float puckY = 0.1;

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
			myPos = sf::Vector2f(10.0f,200.0f);
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
				myPos = sf::Vector2f(380.0f, 200.0f);
			}
		}
		else {
			std::cout << "\nError! Invalid user type. Please try again.\n";
		}
	}while (userType != 's' && userType != 'c');

	std::cout << "Let us...!\n";
	


	sf::RenderWindow window(sf::VideoMode(400, 400), "Pong!");

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

	
	sf::Vector2f puckDir = sf::Vector2f(-0.1,0.0);

	std::cout << "PONG!\n";

	bool update = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::GainedFocus)
			{ 
				update = true;
			}

			if (event.type == sf::Event::LostFocus)
			{
				update = false;
			}
		}

		sf::Vector2f moveVec = sf::Vector2f(0.0f,0.0f);

		if (update)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && myPaddle.getPosition().y > 0)
			{
				moveVec = sf::Vector2f(0.0f, -0.5f);
				lastDir = -1;
				myPaddle.move(moveVec);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && myPaddle.getPosition().y < 360)
			{
				moveVec = sf::Vector2f(0.0f, 0.5f);
				lastDir = 1;
				myPaddle.move(moveVec);
			}
		}

		puckY = (0.1f * lastDir);

		//The worst code youve seen in your life
		std::cout << puck.getPosition().x << " - PuckY =" << puckY << "\n";

		if (userType == 'c' && puck.getPosition().x >= 370.0f && puck.getPosition().y >= myPaddle.getPosition().y && puck.getPosition().y <= (myPaddle.getPosition().y + 40))
		{
			puckDir = sf::Vector2f(-0.1f, puckY);
		}
		else if (userType == 's' && puck.getPosition().x <= 20.0f && puck.getPosition().y >= myPaddle.getPosition().y && puck.getPosition().y <= (myPaddle.getPosition().y + 40))
		{
			puckDir = sf::Vector2f(0.1, puckY);
		}
		else if (userType == 's' && puck.getPosition().x >= 370.0f && puck.getPosition().y >= theirPaddle.getPosition().y && puck.getPosition().y <= (theirPaddle.getPosition().y + 40))
		{
			puckDir = sf::Vector2f(-0.1f, puckY);
		}
		else if (userType == 'c' && puck.getPosition().x <= 20.0f && puck.getPosition().y >= theirPaddle.getPosition().y && puck.getPosition().y <= (theirPaddle.getPosition().y + 40))
		{
			puckDir = sf::Vector2f(0.1f, puckY);
		}
		else if (puck.getPosition().y > 390.f)
		{
			if (puckDir.x == 0.1)
			{
				puckDir = sf::Vector2f(-0.1f, -0.1);
			}
			else {
				puckDir = sf::Vector2f(0.1f, -0.1);
			}
		}
		else if (puck.getPosition().y < 10.f)
		{
			if (puckDir.x == 0.1)
			{
				puckDir = sf::Vector2f(0.1f, 0.1);
			}
			else {
				puckDir = sf::Vector2f(-0.1f, 0.1);
			}

		}



		puck.setPosition(puck.getPosition().x + puckDir.x, puck.getPosition().y + puckDir.y);

		if (puck.getPosition().x < 0.0f || puck.getPosition().x > 400.0f)
		{
			puck.setPosition(200.0f,200.0f);
		}



	//	if (puck.getPosition().x < (myPaddle.getPosition().x+10) && puck.getPosition().y > myPaddle.getPosition().y && puck.getPosition().y < (myPaddle.getPosition().y + 40))
	//	{
	//		puckDir = -puckDir;
		//}

		//Set Shapes Pos
		//myPaddle.setPosition(playerArray[myID].xx, playerArray[myID].yy);

		//Packet
		sf::Packet packet;
		packet << myPaddle.getPosition().x << myPaddle.getPosition().y;

		//Send my data to the server
		if (socket.send(packet) != sf::Socket::Done)
		{
			std::cout << "Error, Can't sent packet to other player :(\n";
		}

		if (socket.receive(packet) == sf::Socket::Done)
		{
			if (packet >> theirPos.x >> theirPos.y)
			{
				theirPaddle.setPosition(theirPos.x, theirPos.y);
			}
		}

		window.clear();
		window.draw(myPaddle);
		window.draw(theirPaddle);
		window.draw(puck);
		window.display();
		
	}

	std::cout << "End\n";
	return 0;
}