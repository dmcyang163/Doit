#include "CEigens.h"
#include "CTickCounter.h"
#include <iostream>


CEigens::CEigens()
{
	matrix1 = Eigen::Matrix<double, 1000, 1000, Eigen::RowMajor>::Random();
	matrix2 = Eigen::Matrix<double, 1000, 1000, Eigen::RowMajor>::Random();
	//matrix1 = Eigen::MatrixXd::Random(1000, 1000);
	//matrix2 = Eigen::MatrixXd::Random(1000, 1000);
}

CEigens::~CEigens()
{

}

void CEigens::calculate() {
#ifdef EIGEN_USE_BLAS
	std::cout << "Eigen is using BLAS." << std::endl;
#else
	std::cout << "Eigen is not using BLAS." << std::endl;
#endif




	// 启用 Eigen 的多线程功能（可根据需要开启）
#ifdef _OPENMP
	std::cout << "Using OpenMP for parallelism." << std::endl;
#endif
	CTickCounter tc(__FUNCTION__);

	// 计算矩阵点积（矩阵乘法）
	//Eigen::MatrixXd dotProduct = matrix1 * matrix2;
	// 使用分块算法进行矩阵乘法
	Eigen::MatrixXd dotProduct = matrix1.block(0, 0, 1000, 1000) * matrix2.block(0, 0, 1000, 1000);

#if 0


	// 计算 Frobenius 内积
	double frobeniusInnerProduct = (matrix1.array() * matrix2.array()).sum();


	// 使用 Eigen 的 IOFormat 将矩阵的部分元素转换为字符串
	Eigen::IOFormat fmt(4, 0, ", ", "\n", "[", "]");
	std::stringstream ss;
	ss << dotProduct.block(0, 0, 5, 5).format(fmt);
	std::string matrixStr = ss.str();


	std::string result = "Top-left corner of the dot product matrix:\n" + matrixStr + "\n\n" + "Frobenius inner product: " + std::to_string(frobeniusInnerProduct);



	std::cout << result << std::endl;
#endif	
	//m_textEdit->setText(QString::fromStdString(result));
}