#pragma once
#include <Eigen/Dense>



class CEigens
{
public:
	CEigens();
	~CEigens();

	Eigen::MatrixXd matrix1, matrix2;
	void calculate();
};

