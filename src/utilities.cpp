#include <utilities.hpp>

template <class T>
std::string to_string(T value)
{
	return std::to_string(value);
}

std::string to_string(std::string value)
{
	return value;
}

bool isSpriteClicked(sf::Sprite object, int mouseX, int mouseY)
{
	sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, 
		object.getGlobalBounds().width, object.getGlobalBounds().height);

	return tempRect.contains(sf::Vector2i(mouseX, mouseY));
}

bool isRectClicked(sf::RectangleShape object, int mouseX, int mouseY)
{
	sf::IntRect tempRect(object.getPosition().x, object.getPosition().y,
		object.getGlobalBounds().width, object.getGlobalBounds().height);

	return tempRect.contains(sf::Vector2i(mouseX, mouseY));
}

bool isSpriteHovered(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{

	return false;
}

