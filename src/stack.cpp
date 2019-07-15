#pragma once

#include <iostream>
#include "stack.hpp"

template <class T>
void Stack<T>::push(T inData)
{
	if (top == MAX - 1)
	{
		throw Overflow();
	}
	else
	{
		m_data[++top] = inData;
	}
}

template <class T>
T Stack<T>::pop()
{
	if (top < 0)
	{
		throw Underflow();
	}
	else
	{
		return m_data[top--];
	}
}

template <class T>
T Stack<T>::peek()
{
	if (top < 0)
	{
		throw Underflow();
	}
	else
	{
		return m_data[top];
	}
}

template <class T>
void Stack<T>::display(sf::RenderWindow &window)
{
	sf::RectangleShape table;
	table.setSize(sf::Vector2f(WINDOW_WIDTH / 3, 3 * WINDOW_HEIGHT / 4));
	table.setPosition((WINDOW_WIDTH / 2) - (table.getGlobalBounds().width / 2), 
					  (WINDOW_HEIGHT / 2) - (table.getGlobalBounds().height / 2));
	table.setFillColor(sf::Color::Black);

	window.draw(table);

	sf::Font font;
	if (!font.loadFromFile("fonts/Liberator-Heavy.otf"))
	{
		throw FontNotLoaded();
	}

	float dataSpriteHeight = table.getGlobalBounds().height / MAX ;
	float dataSpritePositionX = table.getGlobalBounds().left;
	float dataSpritePositionY = table.getGlobalBounds().top + table.getGlobalBounds().height;
	for (int i = top; i >= 0; i--)
	{
		// for each rectangular sprite box
		m_dataSprite[i].setSize(sf::Vector2f(table.getGlobalBounds().width, dataSpriteHeight));
		dataSpritePositionY -= m_dataSprite[i].getGlobalBounds().height;
		m_dataSprite[i].setPosition(dataSpritePositionX, dataSpritePositionY);
		m_dataSprite[i].setFillColor(sf::Color::Yellow);
		m_dataSprite[i].setOutlineThickness(-0.1f * m_dataSprite[i].getGlobalBounds().height);
		m_dataSprite[i].setOutlineColor(sf::Color::Black);

		// for text in each sprite box
		m_dataText[i].setFont(font);
		//m_dataText[i].setCharacterSize()

		window.draw(m_dataSprite[i]);

	}

}