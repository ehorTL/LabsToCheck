#include "SimpleMatrixOperationsTest.h"
#include <Eigen/Dense>
#include <iostream>

using Eigen::MatrixXd;
using std::cout;
using std::cin;

void showMatrixDeterminant()
{
	int dim = 1;
	cout << "ENTER DIMENSION OF SQUARE MATIRX: ";
	cin >> dim;

	MatrixXd matrix;
	matrix.resize(dim, dim);

	cout << "ENTER THE MATRIX: \n";
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			cin >> matrix(i, j);
		}
	}

	cout << "Matrix determinant: " << matrix.determinant() << "\n";
}

void showMatrixInversed()
{
	int dim = 1;
	cout << "ENTER THE DIMENSION OF MATIRX:\n";
	cin >> dim;

	MatrixXd matrix;
	matrix.resize(dim, dim);

	cout << "ENTER THE MATRIX:\n";
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			cin >> matrix(i, j);
		}
	}

	if (matrix.determinant() == 0)
	{
		cout << "DOES NOT EXIST\n";
		return;
	}
	else
	{
		cout << "Inversed matrix:\n" << matrix.inverse() << "\n";
	}
}

void showMatrixTwoMultiplied()
{
	int d11, d12, d21, d22;
	cout <<"ENTER DIMENSIONS OF MATRIX1:\n";
	cin >> d11 >> d12;
	cout << "ENTER DIMENSIONS OF MATRIX2:\n";
	cin >> d21 >> d22;
	
	if (d12 != d21)
	{
		cout << "NOT DEFINE\n";
		return;
	}
	
	MatrixXd m1, m2;
	m1.resize(d11, d12);
	m2.resize(d21, d22);

	cout << "ENTER MATRIX1\n";
	for (int i = 0; i < d11; i++)
	{
		for (int j = 0; j < d12 ; j++)
		{
			cin >> m1(i, j);
		}
	}
	
	cout << "ENTER MATRIX2\n";
	for (int i = 0; i < d21; i++)
	{
		for (int j = 0; j < d22; j++)
		{
			cin >> m2(i, j);
		}
	}

	cout << "PRODUCT:\n" << m1 * m2 << "\n";
}



void showMatrixSquarePowerX() 
{
	cout << "ENTER DIMENTION OF SQUARE MATRIX: ";
	int dim = 0;
	cin >> dim;
	MatrixXd m;
	m.resize(dim, dim);
	cout << "ENTER THE MATRIX:\n";
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < dim; j++)
			cin >> m(i, j);
	}

	cout << "ENTER THE DEGREE: ";
	int deg = 1;
	cin >> deg;
	if (deg <= 0) 
	{
		cout << "FORBIDDEN";
		return;
	}

	MatrixXd tmp;
	tmp.resize(m.rows(), m.cols());
	tmp = m;
	for (int i = 1; i < deg; i++)
	{
		tmp *= m;
	}

	cout << "MAXTRIX IN " << deg << "DEGREE:\n";
	cout << tmp;
}

