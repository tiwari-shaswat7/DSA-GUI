#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "stack.hpp"

std::string to_string(std::string value);
template <class T>
std::string to_string(T value);

bool isSpriteClicked(sf::Sprite object, int mouseX, int mouseY);
bool isSpriteHovered(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);



