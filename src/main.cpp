#include "main-stack.hpp"
#include "main-warshall.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Data Structures and Algorithms", sf::Style::Default, settings);

	sf::Texture menuTexture;
	menuTexture.loadFromFile("img/menu.png");
	sf::Sprite background;
	background.setTexture(menuTexture);

	sf::Font font;
	font.loadFromFile("fonts/MyriadPro-regular.otf");

	sf::Text project[PROJECTS];
	for (int i = 0; i < PROJECTS; i++)
	{
		project[i].setFont(font);
		project[i].setCharacterSize(36);
	}
	project[0].setString("1. Stack");
	project[0].setPosition(580, 285);
	project[1].setString("2. Floyd - Warshall");
	project[1].setPosition(580, 360);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				for (int i = 0; i < PROJECTS; i++)
				{
					if (isTextHovered(project[i], event.mouseMove.x, event.mouseMove.y))
					{
						project[i].setFillColor(sf::Color::Yellow);
						break;
					}
					else
					{
						project[i].setFillColor(sf::Color::White);
					}
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (isTextHovered(project[0], event.mouseButton.x, event.mouseButton.y))
				{
					stack(window);
					break;
				}
				if (isTextHovered(project[1], event.mouseButton.x, event.mouseButton.y))
				{
					floyd_warshall(window);
					break;
				}

			default:
				
				break;
			}
		}
		window.clear();

		window.draw(background);
		for (int i = 0; i < PROJECTS; i++)
		{
			window.draw(project[i]);
		}

		window.display();
	}

	return 0;
}