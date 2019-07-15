#include <iostream>
#include <SFML\Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");
	sf::CircleShape circle(100.f);
	circle.setFillColor(sf::Color::Green);

	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "Couldnot Load Font" << std::endl;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(circle);
		window.display();
	}

	return 0;
}