#pragma once
#include <opencv2/opencv.hpp>
#include <cstdint>
cv::Mat loadImage(const std::wstring& path);

uint64_t hammingDistanceOptimized(uint64_t x, uint64_t y);

bool isSimilar(uint64_t x, uint64_t y);
