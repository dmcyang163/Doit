#include "czip.h"
#include <zstd.h>
#include <fstream>
#include <QDebug>


CZip::CZip() {}


void CZip::test()
{
	std::string original = "这是一段需要压缩的测试字符串hello world!";
	std::string compressed = zstd_compress(original);
	std::cout << "压缩后的数据: " << compressed << std::endl;

	std::string decompressed = zstd_decompress(compressed);
	std::cout << "解压缩后的数据: " << decompressed << std::endl;


	qDebug() << QString::fromStdString(compressed);
	qDebug() << QString::fromStdString(decompressed);




	std::string input_file_path = "D:/young/qts/Doit/data/WinSetupMon.log";
	std::string compressed_file_path = "D:/young/qts/Doit/data/WinSetupMon.log.zst";
	std::string decompressed_file_path = "D:/young/qts/Doit/data/WinSetupMonDecompressed.log";

	int compression_level = 3;
	size_t compressed_size = zstd_compress_file(input_file_path, compressed_file_path, compression_level);
	if (compressed_size > 0)
	{
		qDebug() << "文件已压缩，压缩后大小: " << compressed_size << " 字节" ;
	}

	size_t decompressed_size = zstd_decompress_file(compressed_file_path, decompressed_file_path);
	if (decompressed_size > 0)
	{
		qDebug() << "文件已解压缩，解压缩后大小: " << decompressed_size << " 字节";
	}

}

std::string  CZip::zstd_compress(const std::string& input, int compression_level/* = 3*/) 
{
	size_t max_compressed_size = ZSTD_compressBound(input.size());
	std::vector<char> compressed_buffer(max_compressed_size);

	//int maxCompressionLevel = ZSTD_maxCLevel();
	size_t compressed_size = ZSTD_compress(compressed_buffer.data(), max_compressed_size, input.data(), input.size(), compression_level);

	return std::string(compressed_buffer.data(), compressed_size);
}

std::string  CZip::zstd_decompress(const std::string& input) 
{
	size_t decompressed_size = ZSTD_getFrameContentSize(input.data(), input.size());
	std::vector<char> decompressed_buffer(decompressed_size);

	size_t real_decompressed_size = ZSTD_decompress(decompressed_buffer.data(), decompressed_size, input.data(), input.size());

	return std::string(decompressed_buffer.data(), real_decompressed_size);
}

size_t CZip::zstd_compress_file(const std::string& input_file_path, const std::string& output_file_path, int compression_level/* = 3*/) 
{
	std::ifstream input_file(input_file_path, std::ios::binary);
	if (!input_file)
	{
		std::cerr << "无法打开输入文件: " << input_file_path << std::endl;
		return 0;
	}

	// 获取输入文件大小
	input_file.seekg(0, std::ios::end);
	size_t input_size = input_file.tellg();
	input_file.seekg(0, std::ios::beg);

	std::vector<char> input_data(input_size);
	input_file.read(input_data.data(), input_size);

	size_t max_compressed_size = ZSTD_compressBound(input_size);
	std::vector<char> compressed_buffer(max_compressed_size);

	size_t compressed_size = ZSTD_compress(compressed_buffer.data(), max_compressed_size, input_data.data(), input_size, compression_level);
	if (ZSTD_isError(compressed_size))
	{
		std::cerr << "压缩错误: " << ZSTD_getErrorName(compressed_size) << std::endl;
		return 0;
	}

	std::ofstream output_file(output_file_path, std::ios::binary);
	if (!output_file)
	{
		std::cerr << "无法打开输出文件: " << output_file_path << std::endl;
		return 0;
	}
	output_file.write(compressed_buffer.data(), compressed_size);
	return compressed_size;
}


size_t CZip::zstd_decompress_file(const std::string& input_file_path, const std::string& output_file_path) 
{
	std::ifstream input_file(input_file_path, std::ios::binary);
	if (!input_file)
	{
		std::cerr << "无法打开输入文件: " << input_file_path << std::endl;
		return 0;
	}

	// 获取输入文件大小
	input_file.seekg(0, std::ios::end);
	size_t compressed_size = input_file.tellg();
	input_file.seekg(0, std::ios::beg);

	std::vector<char> compressed_data(compressed_size);
	input_file.read(compressed_data.data(), compressed_size);

	size_t decompressed_size = ZSTD_getFrameContentSize(compressed_data.data(), compressed_size);
	std::vector<char> decompressed_buffer(decompressed_size);

	size_t real_decompressed_size = ZSTD_decompress(decompressed_buffer.data(), decompressed_size, compressed_data.data(), compressed_size);
	if (ZSTD_isError(real_decompressed_size))
	{
		std::cerr << "解压缩错误: " << ZSTD_getErrorName(real_decompressed_size) << std::endl;
		return 0;
	}

	std::ofstream output_file(output_file_path, std::ios::binary);
	if (!output_file)
	{
		std::cerr << "无法打开输出文件: " << output_file_path << std::endl;
		return 0;
	}
	output_file.write(decompressed_buffer.data(), real_decompressed_size);
	return real_decompressed_size;
}
