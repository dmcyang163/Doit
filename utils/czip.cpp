#include "czip.h"
#include <zstd.h>


CZip::CZip() {}

void CZip::zstdZip()
{

}

// 压缩函数
std::vector<unsigned char> CZip::compress(const std::vector<unsigned char>& input) {
    size_t const bound = ZSTD_compressBound(input.size());
    std::vector<unsigned char> buffer(bound);
    size_t const compressedSize = ZSTD_compress(buffer.data(), bound, input.data(), input.size(), 1);
    if (ZSTD_isError(compressedSize))
    {
        std::cerr << "Compression error: " << ZSTD_getErrorName(compressedSize) << std::endl;
        return {};
    }
    buffer.resize(compressedSize);
    return buffer;
}

// 解压缩函数
std::vector<unsigned char> CZip::decompress(const std::vector<unsigned char>& input, size_t originalSize) {
    std::vector<unsigned char> buffer(originalSize);
    size_t const decompressedSize = ZSTD_decompress(buffer.data(), originalSize, input.data(), input.size());
    if (ZSTD_isError(decompressedSize))
    {
        std::cerr << "Decompression error: " << ZSTD_getErrorName(decompressedSize) << std::endl;
        return {};
    }
    return buffer;
}
