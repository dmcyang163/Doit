#ifndef CZIP_H
#define CZIP_H

#include <iostream>
#include <vector>


class CZip
{
public:
    CZip();

    void test();

    std::string zstd_compress(const std::string& input, int compression_level = 3);
    std::string zstd_decompress(const std::string& input);
    size_t zstd_compress_file(const std::string& input_file_path, const std::string& output_file_path, int compression_level = 3);
    size_t zstd_decompress_file(const std::string& input_file_path, const std::string& output_file_path);
};

#endif // CZIP_H
