#pragma once

#include <vector>
#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using namespace Eigen;
using std::cout;
using std::cin;
using std::vector;

class modCntrl
{
public:
	modCntrl();
	~modCntrl();
	void output();
	void countS();
	void countP();
	void countA();
	void countResult();
private:
	int n; // dimension of matrix A
	int m; // columns of matrix B
	int scol; // columns of matrix S;
	vector<int> l; // eigenvector
	MatrixXd A;
	MatrixXd B;
	VectorXd C;
	MatrixXd S;
	VectorXd p;
	VectorXd a;
};


