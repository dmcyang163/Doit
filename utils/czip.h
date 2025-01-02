#ifndef CZIP_H
#define CZIP_H

#include <iostream>
#include <vector>

class CZip
{
public:
    CZip();

    void zstdZip();
    static std::vector<unsigned char> compress(const std::vector<unsigned char>& input);
    static std::vector<unsigned char> decompress(const std::vector<unsigned char>& input, size_t originalSize);
};

#endif // CZIP_H
