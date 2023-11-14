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
	Player me;
	Player other;

	Player playerArray[2];

	sf::IpAddress inputAddress;

	std::cout << "Enter the Address of Server: ";
	std::cin >> inputAddress;
	std::cout << "\nThanks\n";

	std::cout << "Start Client\n";
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(inputAddress, 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "ERROR\n";
	}
	else {
		std::cout << "CONNECTED\n";
	}

	sf::RenderWindow window(sf::VideoMode(200, 200), "Pong!");
	sf::CircleShape myPaddle(10.0f);
	myPaddle.setFillColor(sf::Color::Green);

	sf::CircleShape theirPaddle(20.0f);
	theirPaddle.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerArray[me.id].yy -= 3.0f;
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerArray[me.id].yy += 3.0f;
			}

			//Set Shapes Pos
			myPaddle.setPosition(playerArray[me.id].xx, playerArray[me.id].yy);
			
			//Packet
			sf::Packet packet;
			packet<< playerArray[me.id];

			//Send my data to the server
			if (socket.send(packet) != sf::Socket::Done)
			{
				std::cout << "ERROR\n";
			}

			//Receive Data
			sf::Packet packet2;

			if (socket.receive(packet2) == sf::Socket::Done)
			{
				if (packet2 >> playerArray[0] >> playerArray[1])
				{
					std::cout << "RECEIVED POSITION: " << (playerArray[0].yy) << "\n";
					std::cout << "RECEIVED POSITION: " << (playerArray[1].yy) << "\n";
				}
			}

			if (me.id == 0)
			{
				other.yy = playerArray[1].yy;
				theirPaddle.setPosition(playerArray[1].xx, playerArray[1].yy);
			}
			else {
				other.yy = playerArray[0].yy;
				theirPaddle.setPosition(playerArray[1].xx, playerArray[1].yy);
			}


			window.clear();
			window.draw(myPaddle);
			window.draw(theirPaddle);
			window.display();
		}
	}

	std::cout << "End\n";
	return 0;
}