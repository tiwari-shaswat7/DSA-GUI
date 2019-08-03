#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "defines.hpp"
#include "utilities.hpp"
//#include "warshall-gui.hpp"

struct Warshall;

struct Button {
	sf::RectangleShape rect;
	sf::Text text;

	Button();
	void setString(std::string str);
};

class Input
{
private:
	//sf::RectangleShape m_table;
	Button m_button[BUTTONS];
	sf::Font font;

public:
	Input(std::string str[BUTTONS]);

	int getRectangleIndex(sf::Event inEvent);
	int getInput(sf::RenderWindow& window, Warshall &warshall);

	void pressButton(int index);
	void releaseButton(int index);

	void draw(sf::RenderWindow &window);

};