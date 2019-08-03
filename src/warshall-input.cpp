#include "warshall-input.hpp"
#include "warshall-gui.hpp"

Button::Button()
{
	rect.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	rect.setFillColor(sf::Color::Yellow);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(-2);

	text.setString("BUTTON");
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
}

void Button::setString(std::string str)
{
	static sf::Vector2f pos = sf::Vector2f(0, 0);
	rect.setPosition(pos);

	text.setString(str);
	//text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(pos.x + (rect.getGlobalBounds().width - text.getGlobalBounds().width) / 2,
		pos.y + (rect.getGlobalBounds().height - text.getCharacterSize()) / 2);
	/*text.setPosition(pos);*/
	
	pos.y += BUTTON_HEIGHT;
}

Input::Input(std::string str[BUTTONS])
{
	font.loadFromFile("fonts/Liberator-Heavy.otf");
	for (int i = 0; i < BUTTONS; i++)
	{
		m_button[i].text.setFont(font);
		m_button[i].setString(str[i]);
	}
}

int Input::getRectangleIndex(sf::Event inEvent)
{
	int i = 0;
	for (i = 0; i < BUTTONS; i++)
	{
		if (isRectClicked(m_button[i].rect, inEvent.mouseButton.x, inEvent.mouseButton.y))
		{
			return i;
		}
	}

	return -1;
}

int Input::getInput(sf::RenderWindow& window, Warshall &warshall)
{
	bool inputStatus = true;
	std::string input = "";

	sf::RectangleShape textbox;

	textbox.setFillColor(sf::Color::Black);
	textbox.setOutlineColor(sf::Color::White);
	textbox.setOutlineThickness(-2);
	textbox.setPosition(0, 0);
	textbox.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));

	sf::Font font;
	font.loadFromFile("fonts/OpenSans-Regular.ttf");
	sf::Text displayInput;
	displayInput.setFont(font);
	displayInput.setCharacterSize(20);
	displayInput.setFillColor(sf::Color::Yellow);
	displayInput.setPosition(15, (BUTTON_HEIGHT - displayInput.getCharacterSize()) / 2);

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
					return std::stoi(input);
				if (event.key.code == sf::Keyboard::Escape)
					return 0;
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
		window.clear(sf::Color::Black);
		warshall.draw();
		window.draw(textbox);
		window.draw(displayInput);
		window.display();
	}

	return 0;
}

void Input::pressButton(int index)
{
	m_button[index].rect.setFillColor(sf::Color::Transparent);
	m_button[index].rect.setOutlineColor(sf::Color::Yellow);
	m_button[index].text.setFillColor(sf::Color::Yellow);
}

void Input::releaseButton(int index)
{
	if (index == -1)
		return;
	m_button[index].rect.setFillColor(sf::Color::Yellow);
	m_button[index].rect.setOutlineColor(sf::Color::Black);
	m_button[index].text.setFillColor(sf::Color::Black);
}

void Input::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < BUTTONS; i++)
	{
		window.draw(m_button[i].rect);
		window.draw(m_button[i].text);
	}
}
