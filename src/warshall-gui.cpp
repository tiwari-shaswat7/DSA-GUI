#pragma once

#include "warshall-gui.hpp"

Warshall::Warshall(sf::Font &font, sf::RenderWindow *window) : m_mat(1), m_paths(1)
{
	m_font = font;
	m_window = window;
	m_nodes.push_back(Node(font, 300, 200, 1));
	m_mat[0].push_back(0);
	m_paths[0].push_back(Path(m_nodes[0], m_nodes[0], m_font, 0));
}

void Warshall::calculate()
{
	int n = m_mat.size();
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!(i == j || i == k || j == k))
				{
					int intermediate = m_mat[i][k] + m_mat[k][j];
					if (intermediate < m_mat[i][j])
					{
						m_mat[i][j] = intermediate;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m_paths[i][j].setPath(m_nodes[i], m_nodes[j], m_mat[i][j], false);
			if (!m_paths[i][j].m_biDirectional && isBiDirectional(i, j))
			{
				m_paths[i][j].makeBiDirectional();
				m_paths[j][i].makeBiDirectional();
			}
		}
	}
}

void Warshall::newNode(sf::Event inEvent)
{
	bool functionState = true;

	m_nodes.push_back(Node(m_font, inEvent.mouseButton.x, inEvent.mouseButton.y, m_nodes.size() + 1));
	int prevSize = m_mat[0].size();

	std::vector <int> row;
	std::vector <Path> rowPath;
	for (int i = 0; i < prevSize; i++)
	{
		m_mat[i].push_back(INF);
		m_paths[i].push_back(Path(m_nodes[i], m_nodes.back(), m_font, INF));
		row.push_back(INF);
		rowPath.push_back(Path(m_nodes.back(), m_nodes[i], m_font, INF));
	}
	row.push_back(0);
	rowPath.push_back(Path(m_nodes.back(), m_nodes.back(), m_font, 0));
	m_mat.push_back(row);
	m_paths.push_back(rowPath);

	while (functionState)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				m_nodes[prevSize].move(event.mouseButton.x, event.mouseButton.y);
				functionState = false;
				break;
			case sf::Event::MouseMoved:
				m_nodes[prevSize].move(event.mouseMove.x, event.mouseMove.y);
				break;
			}
		}

		m_window->clear(sf::Color::Black);
		draw();
		m_window->display();

	}
}

int Warshall::selectNode()
{
	bool selection = false;

	sf::Event event;
	while (!selection)
	{
		while(m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				for (int i = 0; i < m_nodes.size(); i++)
				{
					if (isCircleClicked(m_nodes[i].circle, event.mouseButton.x, event.mouseButton.y))
					{
						m_nodes[i].isSelected = true;
						m_nodes[i].draw(*m_window);
						m_window->display();
						selection = true;
						return i;
					}
				}

			}
		}
	}
	return -1;
}

bool Warshall::isBiDirectional(int index1, int index2)
{
	if (index1 == index2)
		return false;

	if (m_mat[index1][index2] < INF && m_mat[index2][index1] < INF)
	{
		return true;
	}
	return false;
}

void Warshall::handleEvent()
{
	bool appState = true;
	while (appState)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				appState = false;
				//m_window->close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.x < BUTTON_WIDTH &&
					event.mouseButton.y < BUTTONS * BUTTON_HEIGHT)
				{
					prevCommand = menu.getRectangleIndex(event);
					menu.pressButton(prevCommand);
					switch (prevCommand)
					{
					case 0:		// Add node
						newNode(event);
						break;

					case 1:		// Add connection
						inputWeight = menu.getInput(*m_window, *this);
						selectNode1 = selectNode();
						selectNode2 = selectNode();
						m_mat[selectNode1][selectNode2] = inputWeight;
						m_paths[selectNode1][selectNode2].setPath(m_nodes[selectNode1],
							m_nodes[selectNode2], inputWeight, true);
						if (!m_paths[selectNode1][selectNode2].m_biDirectional && isBiDirectional(selectNode1, selectNode2))
						{
							m_paths[selectNode1][selectNode2].makeBiDirectional();
							m_paths[selectNode2][selectNode1].makeBiDirectional();
						}

						break;

					case 2:		// Calculate
						calculate();
						break;
					}
				}
				break;
			case sf::Event::MouseMoved:
				std::cout << sf::Mouse::getPosition().x << ", "
					<< sf::Mouse::getPosition().y << std::endl;
				break;
			default:
				
				if (selectNode1 != -1)
				{
					m_nodes[selectNode1].isSelected = false;
					selectNode1 = -1;
				}
				if (selectNode2 != -1)
				{
					m_nodes[selectNode2].isSelected = false;
					selectNode2 = -1;
				}

				if (prevCommand != -1)
				{
					menu.releaseButton(prevCommand);
					prevCommand = -1;
				}
				break;
			}
		}

		m_window->clear(sf::Color::Black);

		draw();

		m_window->display();

	}
}

void Warshall::draw()
{
	menu.draw(*m_window);

	for (int i = 0; i < m_paths.size(); i++)
	{
		for (int j = 0; j < m_paths[i].size(); j++)
		{
			if (m_mat[i][j] != 0 && m_mat[i][j] != INF) 
			{
				m_paths[i][j].draw(*m_window);
			}
		}
	}

	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i].draw(*m_window);
	}


	/*sf::CircleShape circle(30.0f, 3);
	circle.setFillColor(sf::Color::Yellow);*/

	/*ArrowShape arrow(200);
	arrow.setFillColor(sf::Color::Transparent);
	arrow.setOutlineColor(sf::Color::Yellow);
	arrow.setOutlineThickness(2);
	arrow.rotate(45);
	Node node1(font, 500, 500, 1);
	Node node2(font, 200, 200, 2);
	Path path1(node1, node2, font, 25);
	Path path2(node2, node1, font, 139);*/
	

		/*path1.draw(window);
		path2.draw(window);
		node1.draw(window);
		node2.draw(window);
		m_window->draw(arrow);*/

	
}