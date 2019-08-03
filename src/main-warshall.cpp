#pragma once 

#include "main-warshall.hpp"

void displayMat(std::vector<std::vector<int>> &mat)
{
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			std::cout << mat[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

void floyd_warshall(sf::RenderWindow &window)
{
	window.setTitle("Floyd-Warshall's Algorithm");

	sf::Font font;
	if (!font.loadFromFile("fonts/Liberator-Heavy.otf"))
	{
		std::cout << "Font not loaded!!" << std::endl;
		exit(1);
	}


	Warshall warshall(font, &window);
	warshall.handleEvent();

	/*int n;
	std::cout << "Number of nodes: ";
	std::cin >> n;*/

	/*int** mat = new int* [n];*/
	/*std::cout << "Enter matrix: " << std::endl;*/
	/*for (int i = 0; i < n; i++)
	{
		std::cout << "Row " << i + 1 << std::endl;
		mat[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			std::cin >> mat[i][j];
		}
	}*/

	displayMat(warshall.m_mat);



	std::cout << "---------------------------" << std::endl;
	displayMat(warshall.m_mat);
}