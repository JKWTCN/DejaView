/*
 * @Author: JKWTCN jkwtcn@icloud.com
 * @Date: 2025-10-16 20:40:57
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-10-16 21:12:03
 * @FilePath: \DejaView\include\ImageHasher.h
 * @Description:
 */
#ifndef IMAGEHASHER_H
#define IMAGEHASHER_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <cstdint>

class ImageHasher
{
public:
    // 平均哈希
    static uint64_t averageHash(const cv::Mat &image);

    // 差异哈希
    static uint64_t differenceHash(const cv::Mat &image);

    // 感知哈希（DCT实现）
    static uint64_t perceptualHash(const cv::Mat &image);

    // 汉明距离
    static int hammingDistance(uint64_t hash1, uint64_t hash2);

    // 计算相似度（0-1之间）
    static double similarity(uint64_t hash1, uint64_t hash2);

    // 整数哈希转十六进制字符串（可选）
    static std::string hashToHex(uint64_t hash);
};

#endif // IMAGEHASHER_H