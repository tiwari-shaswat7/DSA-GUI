#pragma once 

#include "main-warshall.hpp"

void displayMat(int** mat, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << mat[i][j] << '\t';
		}
		std::cout << std::endl;
	}

}

int main()
{
	drawWarshall();

	int n;
	std::cout << "Number of nodes: ";
	std::cin >> n;

	int** mat = new int* [n];
	std::cout << "Enter matrix: " << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Row " << i + 1 << std::endl;
		mat[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			std::cin >> mat[i][j];
		}
	}

	displayMat(mat, n);

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!(i == j || i == k || j == k))
				{
					int intermediate = mat[i][k] + mat[k][j];
					if (intermediate < mat[i][j])
					{
						mat[i][j] = intermediate;
					}
				}
			}
		}
	}

	std::cout << "---------------------------" << std::endl;
	displayMat(mat, n);

	return 0;
}