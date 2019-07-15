#pragma once

#include "..\headers\main.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stack");

	Stack <int> myStack;
	myStack.push(5);
	myStack.push(6);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::W)
				{
					myStack.push(4);
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					myStack.pop();
				}
				break;

			/*case sf::Event::MouseMoved:
				std::cout << event.mouseMove.x << ", " << event.mouseMove.y << std::endl;
				break;*/

			default:
				break;

			}
		}

		try
		{
			

			//std::cout << myStack.pop() << std::endl;
			//std::cout << myStack.pop() << std::endl;

			//std::cout << myStack.peek() << std::endl;

		}
		catch (Overflow)
		{
			std::cout << "Stack Overflow!" << std::endl;
		}
		catch (Underflow)
		{
			std::cout << "Stack Underflow!" << std::endl;
		}

		window.clear(sf::Color(COLOR_WHITE));
		myStack.display(window);
		//window.draw(circle);
		window.display();

	}

	return 0;
}
