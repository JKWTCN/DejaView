/*
 * @Author: JKWTCN jkwtcn@icloud.com
 * @Date: 2025-10-16 20:40:57
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-10-16 20:45:10
 * @FilePath: \DejaView\include\ImageHasher.h
 * @Description:
 */
#ifndef IMAGEHASHER_H
#define IMAGEHASHER_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class ImageHasher
{
public:
    // 平均哈希
    static std::string averageHash(const cv::Mat &image);

    // 差异哈希
    static std::string differenceHash(const cv::Mat &image);

    // 感知哈希（DCT实现）
    static std::string perceptualHash(const cv::Mat &image);

    // 汉明距离
    static int hammingDistance(const std::string &hash1, const std::string &hash2);

    // 计算相似度（0-1之间）
    static double similarity(const std::string &hash1, const std::string &hash2);

    // 二进制哈希转十六进制
    static std::string binaryToHex(const std::string &binaryHash);
};

#endif // IMAGEHASHER_H