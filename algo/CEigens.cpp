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




	// ���� Eigen �Ķ��̹߳��ܣ��ɸ�����Ҫ������
#ifdef _OPENMP
	std::cout << "Using OpenMP for parallelism." << std::endl;
#endif
	CTickCounter tc(__FUNCTION__);

	// ���������������˷���
	//Eigen::MatrixXd dotProduct = matrix1 * matrix2;
	// ʹ�÷ֿ��㷨���о���˷�
	Eigen::MatrixXd dotProduct = matrix1.block(0, 0, 1000, 1000) * matrix2.block(0, 0, 1000, 1000);

#if 0


	// ���� Frobenius �ڻ�
	double frobeniusInnerProduct = (matrix1.array() * matrix2.array()).sum();


	// ʹ�� Eigen �� IOFormat ������Ĳ���Ԫ��ת��Ϊ�ַ���
	Eigen::IOFormat fmt(4, 0, ", ", "\n", "[", "]");
	std::stringstream ss;
	ss << dotProduct.block(0, 0, 5, 5).format(fmt);
	std::string matrixStr = ss.str();


	std::string result = "Top-left corner of the dot product matrix:\n" + matrixStr + "\n\n" + "Frobenius inner product: " + std::to_string(frobeniusInnerProduct);



	std::cout << result << std::endl;
#endif	
	//m_textEdit->setText(QString::fromStdString(result));
}