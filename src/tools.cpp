#include "tools.h"
#include <filesystem>

cv::Mat loadImage(const std::wstring & path)
{
	return cv::imread(std::filesystem::path(path).string());
}

uint64_t hammingDistanceOptimized(uint64_t x, uint64_t y) {
    uint64_t xor_result = x ^ y;
    uint64_t distance = 0;

    // 使用 Brian Kernighan 算法
    while (xor_result) {
        distance++;
        xor_result = xor_result & (xor_result - 1);  // 清除最低位的1
    }

    return distance;
}

bool isSimilar(uint64_t x, uint64_t y){
	return hammingDistanceOptimized(x, y) <= 5;
}
