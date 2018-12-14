#include "SimpleMatrixOperationsTest.h"
#include "modCntrl.h"

#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

void menu();


int main()
{	

	while (true)
	{
		menu();
		int choice = 1;
		cin >> choice;
		
		switch (choice)
		{
		case 1: 
			showMatrixDeterminant();
			break;
		case 2:
			showMatrixInversed();
			break;
		case 3:
			showMatrixTwoMultiplied();
			break;
		case 4:
			showMatrixSquarePowerX();
			break;
		default: exit(1);
		}
	}

	
	
	return 0;
}

void menu()
{
	std::cout << "\n\n";
	std::cout << "ENTER A NUMBER OF OPERATION:\n\n";
	std::cout << "1. Get matrix determinant\n";
	std::cout << "2. Get inverse matrix\n";
	std::cout << "3. Multiply two matrix\n";
	std::cout << "4. Get square matrix degree\n";
	std::cout << "0. Exit\n";
	
}