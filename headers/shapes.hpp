#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <SFML\Graphics.hpp>

#include "defines.hpp"

class ArrowShape : public sf::Shape
{
private:
	float m_length;
	float m_lengthRect;
	const float m_breadth;
	const float m_breadthArrow;
	const float m_lengthArrow;

public:
	explicit ArrowShape(float length);

	void setLength(const float length);
	const float getLength() const;

	virtual size_t getPointCount() const;
	virtual sf::Vector2f getPoint(size_t index) const;
};

struct Node
{
	sf::CircleShape circle;
	int index;
	sf::Text indexText;
	bool isSelected;

	Node(sf::Font& font, int posX, int posY, int index = 0);

	void move(int posX, int posY);
	void draw(sf::RenderWindow& window);
};

struct Path
{
	ArrowShape m_arrow;
	sf::Text m_text;

	Path(Node node1, Node node2, sf::Font &font,int weight = INF);

	void setPath(Node node1, Node node2, int weight = INF);

	void draw(sf::RenderWindow& window);
};
