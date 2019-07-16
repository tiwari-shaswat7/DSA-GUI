#pragma once

#include <string>
#include <SFML\Graphics.hpp>

#include "defines.hpp"

#define MAX 5

class Overflow { };
class Underflow { };
class FontNotLoaded { };

template <class T>
class Stack
{
private:
	T m_data[MAX];
	sf::RectangleShape m_dataSprite[MAX];
	sf::Text m_dataText[MAX];
	int top;

public:
	Stack() : top(-1) {}

	void push(T inData);
	T pop();
	T peek();

	void display(sf::RenderWindow& window);
};
