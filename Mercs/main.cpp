#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "SFML WORKS");

	while(window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

		}

		window.clear();
		window.display();
	}

	return 0;
}