#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

#include "warshall-input.hpp"
#include "defines.hpp"
#include "shapes.hpp"


struct Warshall 
{
	std::vector<Node> m_nodes;
	std::vector<std::vector<Path>> m_paths;
	std::vector<std::vector<int>> m_mat;

	sf::Font m_font;
	sf::RenderWindow *m_window;

	std::string commands[BUTTONS] = { "ADD NODE", "CONNECT", "CALCULATE" };
	Input menu = Input(commands);
	int prevCommand = -1;
	int selectNode1 = -1;
	int inputWeight = INF;
	int selectNode2 = -1;


	Warshall(sf::Font &font, sf::RenderWindow *window);

	//std::vector<std::vector<int>> &getMatrix();
	//void setMatrix(std::vector<std::vector<int>> &mat);

	void calculate();
	void newNode(sf::Event inEvent);
	int selectNode();

	void handleEvent();
	void draw();
};
