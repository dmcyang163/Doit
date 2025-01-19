#include "CEigens.h"
#include "CTickCounter.h"
#include <iostream>


CEigens::CEigens()
{
	//matrix1 = Eigen::Matrix<double, 1000, 1000, Eigen::RowMajor>::Random();
	//matrix2 = Eigen::Matrix<double, 1000, 1000, Eigen::RowMajor>::Random();
	//matrix1 = Eigen::MatrixXd::Random(1000, 1000);
	//matrix2 = Eigen::MatrixXd::Random(1000, 1000);
}

CEigens::~CEigens()
{

}

void CEigens::calculate() 
{

#ifdef EIGEN_USE_BLAS
	std::cout << "Eigen is using BLAS." << std::endl;
#else
	std::cout << "Eigen is not using BLAS." << std::endl;
#endif

	// 启用 Eigen 的多线程功能（可根据需要开启）
#ifdef _OPENMP
	std::cout << "Using OpenMP for parallelism." << std::endl;
#endif



	// 启用 Eigen 的多线程支持
	Eigen::initParallel();
	// 设置线程数
	Eigen::setNbThreads(12);

	// 定义两个 1000×1000 的双精度矩阵，使用 Eigen::MatrixXd
	Eigen::MatrixXd matrix1 = Eigen::MatrixXd::Random(1000, 1000);
	Eigen::MatrixXd matrix2 = Eigen::MatrixXd::Random(1000, 1000);

	CTickCounter tc(__FUNCTION__);


	// 1.使用表达式模板进行矩阵乘法 fast
	for (int i=0; i<100; ++i)
		Eigen::MatrixXd result = (matrix1.array() * matrix2.array()).matrix();


	// 2.分块计算矩阵乘法
	//Eigen::MatrixXd result(1000, 1000);
	//for (int i = 0; i < 1000; i += 100)
	//{
	//	for (int j = 0; j < 1000; j += 100)
	//	{
	//		result.block(i, j, 100, 100) = matrix1.block(i, 0, 100, 100) * matrix2.block(0, j, 100, 100);
	//	}
	//}

	// 3.使用部分求值
	//Eigen::MatrixXd result = (matrix1 * matrix2).eval();

	// 输出结果矩阵的一些信息（这里仅输出矩阵的维度）
	//std::cout << "结果矩阵的维度: " << result.rows() << " × " << result.cols() << std::endl;


}