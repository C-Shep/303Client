#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>



int main()
{
	sf::IpAddress inputAddress;

	//Packet
	sf::Packet packet;

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

	
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.0f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				shape.setPosition(shape.getPosition().x, shape.getPosition().y - 3.0);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				shape.setPosition(shape.getPosition().x, shape.getPosition().y + 3.0);
			}
			float yy = shape.getPosition().y;
			packet << yy;

			//TCP socket
			if (socket.send(packet) != sf::Socket::Done)
			{
				std::cout << "ERROR\n";
			}

		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	//return 0;



	char data[100];



	std::cout << "DATA SENT\n";


	//Recieve Data
	char recdata[100];
	std::size_t received;

	if (socket.receive(recdata, 100, received) != sf::Socket::Done)
	{
		//EROOR
	}

	std::cout << "Received" << received << " bytes " << std::endl;

	std::cout << "End\n";
	return 0;
}