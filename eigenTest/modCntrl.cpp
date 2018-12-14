#include "modCntrl.h"


modCntrl::modCntrl()
{
	cout << "Enter the dimension of matrix A: ";
	cin >> n;
	cout << "Enter matrix A:" << std::endl;
	A = MatrixXd(n, n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> A(i, j);
		}
	}
	cout << "Enter the number of columns of matrix B: ";
	cin >> m;
	cout << "Enter matrix B:" << std::endl;
	B = MatrixXd(n, m);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> B(i, j);
		}
	}
	cout << "Enter the roots of the characteristic equation:" << std::endl;
	for (int i = 0; i < n; ++i)
	{
		int k = 0;
		cin >> k;
		l.push_back(k);
		l[i] *= (-1);
	}
	p = VectorXd(n);
	a = VectorXd(n);
	C = VectorXd(n);
}


modCntrl::~modCntrl()
{
}

void modCntrl::countS()
{
	scol = n * m;
	S = MatrixXd(n, scol);
	int start = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = start; j < m; ++j)
		{
			S(i, j) = B(i, j);
		}
	}
	start = start + m;
	for (int i = 1; i < n; ++i)
	{
		MatrixXd Amult(n, n);
		Amult = A;
		for (int j = 2; j <= i; ++j)
		{
			Amult = Amult * A;
		}


		MatrixXd tmp(n, m);
		tmp = Amult * B;
		for (int k = 0; k < n; ++k)
		{
			for (int l = start; l < m + start; ++l)
			{
				S(k, l) = tmp(k, l - start);
			}
		}
		start = start + m;
	}
	S = S.inverse();
}

void modCntrl::countP()
{
	MatrixXd tmp(n, n);
	tmp = A;
	for (int i = 2; i <= n; ++i)
	{
		tmp = tmp * A;
	}
	VectorXd ptmp(n);
	ptmp = (S*tmp)*B*(-1);
	for (int i = n - 1; i >= 0; --i)
	{
		p(n - i - 1) = ptmp(i);
	}
}

void modCntrl::countA()
{
	if (n == 2)
	{
		a(0) = l[0] + l[1];
		a(1) = l[0] * l[1];
	}
	else if (n == 3)
	{
		a(0) = l[0] + l[1] + l[2];
		a(1) = l[0] * l[1] + l[0] * l[2] + l[1] * l[2];
		a(2) = l[0] * l[1] * l[2];
	}
	else if (n == 4)
	{
		a(0) = l[0] + l[1] + l[2] + l[3];
		a(1) = l[0] * l[1] + l[0] * l[2] + l[1] * l[2];
		a(1) = a(1) + l[0] * l[3] + l[1] * l[3] + l[2] * l[3];
		a(2) = l[0] * l[1] * l[2] + l[0] * l[1] * l[3] + l[1] * l[2] * l[3];
		a(3) = l[0] * l[1] * l[2] * l[3];
	}
}

void modCntrl::countResult()
{
	S.transposeInPlace();
	MatrixXd tmp(n, n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
			{
				tmp(i, j) = 1;
			}
			else if (j > i)
			{
				tmp(i, j) = 0;
			}
			else
			{
				tmp(i, j) = p(i - j - 1);
			}
		}
	}

	VectorXd pMinA(n);
	pMinA = p - a;
	C = S * tmp * pMinA;
}

void modCntrl::output()
{
	cout << "Result: " << std::endl;
	cout << "u(t) = ";
	for (int i = 0; i < n; ++i)
	{
		cout << C(i);
		cout << "*x" << i + 1 << "(t)";
		if (i != n - 1)
		{
			cout << " + ";
		}
	}
	cout << std::endl;
}