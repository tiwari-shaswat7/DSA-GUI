#include "textbox.hpp"

template <class T>
std::string getInput(sf::RenderWindow& window, int positionX, int positionY, Stack <T> &stack)
{
	bool inputStatus = true;
	std::string input = "";

	sf::Sprite textbox;
	sf::Texture texture;
	if (!texture.loadFromFile("img/textbox.png"))
	{
		exit(17723);
	}

	textbox.setTexture(texture);
	textbox.setPosition(sf::Vector2f(positionX, positionY));

	sf::Font font;
	font.loadFromFile("fonts/OpenSans-Regular.ttf");
	sf::Text displayInput;
	displayInput.setFont(font);
	displayInput.setCharacterSize(30);
	displayInput.setFillColor(sf::Color::Black);
	displayInput.setPosition(positionX + 20, positionY + 5 /*+ (textbox.getGlobalBounds().height / 2
		- displayInput.getGlobalBounds().height / 2)*/);

	sf::Event event;
	while (inputStatus)
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter)
					return input;
				if (event.key.code == sf::Keyboard::Escape)
					return "";
				break;

			case sf::Event::TextEntered:
				if (event.text.unicode == 8)
				{
					if (input != "")
					{
						input.pop_back();
						displayInput.setString(input);
					}
				}
				else if (event.text.unicode < 128)
				{
					input += event.text.unicode;
					displayInput.setString(input);			
				}
				break;
				//case sf::
			}
		}
		//window
		window.clear(sf::Color::White);
		stack.draw(window);
		window.draw(textbox);
		window.draw(displayInput);
		window.display();
	}

	return "Beckham";
}