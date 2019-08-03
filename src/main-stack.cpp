#include "..\headers\main-stack.hpp"

void stack(sf::RenderWindow &window)
{
	window.setTitle("Stack");

	sf::Sprite buttons[NUMBER_OF_BUTTONS];
	/*bool buttonsState[NUMBER_OF_BUTTONS];
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		buttonsState[i] = false;
	}*/
	sf::Texture		buttonPush[2],
					buttonPop[2],
					buttonQuit[1];

	if (!(buttonPush[1].loadFromFile("img/button-push-active.png") && buttonPush[0].loadFromFile("img/button-push-inactive.png")
		&& buttonPop[1].loadFromFile("img/button-pop-active.png") && buttonPop[0].loadFromFile("img/button-pop-inactive.png")
		&& buttonQuit[0].loadFromFile("img/button-quit-inactive.png")))
	{
		throw TextureNotFound();
	}

	buttons[0].setTexture(buttonPush[0]);
	buttons[1].setTexture(buttonPop[0]);
	buttons[2].setTexture(buttonQuit[0]);

	/*if (buttonsState[0])
		buttons[0].setTexture(buttonPush[1]);
	if (buttonsState[0])
		buttons[1].setTexture(buttonPop[1]);
	if (buttonsState[0])
		buttons[2].setColor(sf::Color::Red);*/


	float buttonPositionY = WINDOW_HEIGHT - 1.2 * buttons[0].getGlobalBounds().height;
	float buttonPositionX = 0.2 * buttons[0].getGlobalBounds().height;
	for (int i = 0; i < NUMBER_OF_BUTTONS - 1; i++)
	{
		buttons[i].setPosition(sf::Vector2f(buttonPositionX, buttonPositionY));
		buttonPositionX += buttons[i].getGlobalBounds().width + 0.2 * buttons[0].getGlobalBounds().height;
	}

	buttons[2].setPosition(sf::Vector2f(WINDOW_WIDTH - 0.2 * buttons[0].getGlobalBounds().height
		- buttons[2].getGlobalBounds().width, buttonPositionY));

	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
		window.draw(buttons[i]);

	Stack <std::string> myStr;
	Stack <int> myStack;
	myStr.push("Neymar");
	myStr.push("Ronaldo");
	myStack.push(5);
	myStack.push(6);

	bool appState = true;
	while (appState)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			try
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::W)
					{
						myStr.push("Messi");
						//myStack.push(4);
					}
					else if (event.key.code == sf::Keyboard::S)
					{
						//myStack.pop();
						myStr.pop();
					}
					break;

				case sf::Event::MouseButtonPressed:
					//if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					//{
					std::cout << event.mouseButton.x << ',' << event.mouseButton.y;
					if (isSpriteClicked(buttons[0], event.mouseButton.x, event.mouseButton.y))
					{
						buttons[0].setTexture(buttonPush[1]);
						window.draw(buttons[0]);
						window.display();
						sf::sleep(sf::milliseconds(200));
						std::string temp = getInput(window, buttons[0].getPosition().x, buttons[0].getPosition().y, myStr);
						if(temp != "")
							myStr.push(temp);
						break;
					}
					else if (isSpriteClicked(buttons[1], event.mouseButton.x, event.mouseButton.y))
					{
						buttons[1].setTexture(buttonPop[1]);
						myStr.pop();
						break;
					}
					else if (isSpriteClicked(buttons[2], event.mouseButton.x, event.mouseButton.y))
					{
						buttons[2].setColor(sf::Color(255, 0, 0, 255));
						appState = false;
						break;
					}
					//}

				/*case sf::Event::MouseMoved:
					std::cout << event.mouseMove.x << ", " << event.mouseMove.y << std::endl;
					break;*/

				default:
					buttons[0].setTexture(buttonPush[0]);
					buttons[1].setTexture(buttonPop[0]);
					buttons[2].setColor(sf::Color(255, 255, 255, 255));
					break;

				}
			}
			catch (Overflow)
			{
				window.clear(sf::Color(COLOR_WHITE));
				myStr.draw(window, true);
				window.display();
				sf::sleep(sf::seconds(1));
			}
			catch (Underflow)
			{
				window.clear(sf::Color(COLOR_WHITE));
				myStr.draw(window, false, true);
				window.display();
				sf::sleep(sf::seconds(1));
			}
		}

			


			//std::cout << myStack.pop() << std::endl;
			//std::cout << myStack.pop() << std::endl;

			//std::cout << myStack.peek() << std::endl;


		window.clear(sf::Color(COLOR_WHITE));
		//myStack.display(window);
		for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
			window.draw(buttons[i]);
		myStr.draw(window);
		window.display();

	}

}
