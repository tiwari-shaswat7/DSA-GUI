#pragma once

#include <string>
#include <typeinfo>
#include <SFML\Graphics.hpp>

#include "defines.hpp"
#include "utilities.hpp"

#define MAX 5

class Overflow { };
class Underflow { };
class FontNotLoaded { };
class TextureNotFound { };

template <class T>
class Stack
{
private:
	T m_data[MAX];
	int top;

	sf::RectangleShape m_dataSprite[MAX];
	sf::Text m_dataText[MAX];

public:
	Stack();

	void push(T inData);
	T pop();
	T peek();

	void draw(sf::RenderWindow& window, bool overflow = false, bool underflow = false);
};
