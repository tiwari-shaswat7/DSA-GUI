#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "stack.hpp"

std::string to_string(std::string value);
template <class T>
std::string to_string(T value);

bool isSpriteClicked(sf::Sprite object, int mouseX, int mouseY);
bool isRectClicked(sf::RectangleShape object, int mouseX, int mouseY);
bool isCircleClicked(sf::CircleShape object, int mouseX, int mouseY);
bool isTextHovered(sf::Text object, int mouseX, int mouseY);



