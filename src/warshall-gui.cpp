#pragma once

#include "warshall-gui.hpp"

void drawWarshall()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Warshall Algorithm", sf::Style::Default, settings);

	sf::Font font;
	if (!font.loadFromFile("fonts/Liberator-Heavy.otf"))
	{
		std::cout << "Font not loaded!!" << std::endl;
		exit(1);
	}
	/*sf::CircleShape circle(30.0f, 3);
	circle.setFillColor(sf::Color::Yellow);*/
	ArrowShape arrow(200);
	arrow.setFillColor(sf::Color::Transparent);
	arrow.setOutlineColor(sf::Color::Yellow);
	arrow.setOutlineThickness(2);
	arrow.rotate(45);
	Node node1(font, 500, 500, 1);
	Node node2(font, 200, 200, 2);
	Path path(node1, node2, font, 2);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				std::cout << sf::Mouse::getPosition().x << ", " 
					<< sf::Mouse::getPosition().y << std::endl;
				break;
			}
		}

		window.clear(sf::Color::Black);
		path.draw(window);
		node1.draw(window);
		node2.draw(window);
		window.draw(arrow);
		window.display();

	}
}