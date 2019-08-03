#include "shapes.hpp"

Node::Node(sf::Font& font, int posX, int posY, int index)
{
	circle.setRadius(NODE_RADIUS);
	circle.setOrigin(NODE_RADIUS / 2, NODE_RADIUS / 2);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(posX, posY);
	circle.setOutlineColor(sf::Color::White);

	isSelected = false;

	Node::index = index;


	indexText.setFont(font);
	indexText.setString(std::to_string(index));
	//indexText.setCharacterSize()
	indexText.setPosition(circle.getGlobalBounds().left + NODE_RADIUS - indexText.getGlobalBounds().width / 2,
		circle.getGlobalBounds().top + NODE_RADIUS - indexText.getCharacterSize() / 2 - 5);
	indexText.setFillColor(sf::Color::Black);
}

void Node::move(int posX, int posY)
{
	circle.setPosition(posX, posY);
	indexText.setPosition(circle.getGlobalBounds().left + NODE_RADIUS - indexText.getGlobalBounds().width / 2,
		circle.getGlobalBounds().top + NODE_RADIUS - indexText.getCharacterSize() / 2 - 5);
}

void Node::draw(sf::RenderWindow& window)
{
	if (isSelected)
	{
		circle.setOutlineThickness(5);
	}
	else
	{
		circle.setOutlineThickness(0);
	}
	window.draw(circle);
	window.draw(indexText);
}

Path::Path(Node node1, Node node2, sf::Font& font, int weight) : m_arrow(100.f)
{
	m_arrow.setOrigin(0, 15);
	m_arrow.setFillColor(sf::Color::Transparent);
	m_arrow.setOutlineColor(sf::Color::White);
	m_arrow.setOutlineThickness(2);
	setPath(node1, node2, weight);

	m_text.setFont(font);
}

void Path::setPath(Node node1, Node node2, int weight, bool outline)
{
	int offsetOutline = 5;
	if (!outline)
	{
		offsetOutline = 0;
	}

	float cx1 = node1.circle.getGlobalBounds().left + node1.circle.getGlobalBounds().width / 2;
	float cy1 = node1.circle.getGlobalBounds().top + node1.circle.getGlobalBounds().width / 2;
	float cx2 = node2.circle.getGlobalBounds().left + node2.circle.getGlobalBounds().width / 2;
	float cy2 = node2.circle.getGlobalBounds().top + node2.circle.getGlobalBounds().width / 2;
	float length = sqrtf(powf(cx2 - cx1, 2) + powf(cy2 - cy1, 2)) - (node2.circle.getGlobalBounds().width / 2);
	m_arrow.setLength(length + offsetOutline);

	float angleRad = atan2(cy2 - cy1, cx2 - cx1);
	m_angleRotationRad = angleRad;
	float angle = 180 / PI * angleRad;
	m_arrow.setRotation(angle);

	m_arrow.setPosition(cx1, cy1);

	m_text.setString(std::to_string(weight));
	m_text.setCharacterSize(18);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setOrigin(0, m_text.getCharacterSize() / 2 + 2);
	m_text.setPosition(cx1 + node1.circle.getGlobalBounds().width, cy1);

	std::cout << angle << std::endl;
	if (angle < -90 || angle >= 90)
		m_text.setScale(-1, -1);
	else
		m_text.setScale(1, 1);

	m_prevPosition = m_arrow.getPosition();

	if (m_biDirectional)
	{
		float centerOffset = NODE_RADIUS + 10;	// ARROWHEAD = 10
		m_arrow.setLength(m_arrow.getLength() - centerOffset);
		m_arrow.setPosition(m_arrow.getPosition().x + centerOffset * cos(m_angleRotationRad),
			m_arrow.getPosition().y + centerOffset * sin(m_angleRotationRad));
	}

}

void Path::setPathWeight(int weight)
{
	m_text.setString(std::to_string(weight));
}

void Path::makeBiDirectional()
{
	float centerOffset = NODE_RADIUS + 10;	// ARROWHEAD = 10
	m_arrow.setLength(m_arrow.getLength() - centerOffset);
	m_arrow.setPosition(m_arrow.getPosition().x + centerOffset * cos(m_angleRotationRad),
		m_arrow.getPosition().y + centerOffset * sin(m_angleRotationRad));
	m_biDirectional = true;
}

void Path::draw(sf::RenderWindow& window)
{
	window.draw(m_arrow);

	sf::Transform m_transform;
	m_transform.rotate(m_arrow.getRotation(), m_prevPosition);
	window.draw(m_text, m_transform);
}

ArrowShape::ArrowShape(float length) :
	m_length(length), m_breadth(10), m_breadthArrow(20),
	m_lengthArrow(10), m_lengthRect(length - 10)
{
	update();
}

void ArrowShape::setLength(const float length)
{
	m_length = length;
	m_lengthRect = length - m_lengthArrow;
	update();
}

const float ArrowShape::getLength() const
{
	return m_length;
}

size_t ArrowShape::getPointCount() const
{
	return 7;
}

sf::Vector2f ArrowShape::getPoint(size_t index) const
{
	switch (index)
	{
	case 0:
		return sf::Vector2f(0, 22);
	case 1:
		return sf::Vector2f(0, 8);
	case 2:
		return sf::Vector2f(m_lengthRect, 8);
	case 3:
		return sf::Vector2f(m_lengthRect, 0);
	case 4:
		return sf::Vector2f(m_length, 15);
	case 5:
		return sf::Vector2f(m_lengthRect, 30);
	case 6:
		return sf::Vector2f(m_lengthRect, 22);
	}

	return sf::Vector2f(0, 0);
}