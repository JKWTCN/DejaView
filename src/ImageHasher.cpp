#include "ImageHasher.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <algorithm>

// 平均哈希
uint64_t ImageHasher::averageHash(const cv::Mat &image)
{
    cv::Mat resized, gray;

    // 缩放到8x8
    cv::resize(image, resized, cv::Size(8, 8));

    // 转为灰度图
    if (resized.channels() == 3)
    {
        cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    }
    else
    {
        gray = resized.clone();
    }

    // 计算平均值
    double mean = cv::mean(gray)[0];

    // 生成哈希
    uint64_t hash = 0;
    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols; j++)
        {
            hash = (hash << 1) | ((gray.at<uchar>(i, j) > mean) ? 1 : 0);
        }
    }

    return hash;
}

// 差异哈希
uint64_t ImageHasher::differenceHash(const cv::Mat &image)
{
    cv::Mat resized, gray;

    // 缩放到9x8（多一列用于比较差异）
    cv::resize(image, resized, cv::Size(9, 8));

    // 转为灰度图
    if (resized.channels() == 3)
    {
        cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    }
    else
    {
        gray = resized.clone();
    }

    // 计算相邻像素差异
    uint64_t hash = 0;
    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols - 1; j++)
        {
            hash = (hash << 1) | ((gray.at<uchar>(i, j + 1) > gray.at<uchar>(i, j)) ? 1 : 0);
        }
    }

    return hash;
}

// 感知哈希（DCT实现）
uint64_t ImageHasher::perceptualHash(const cv::Mat &image)
{
    cv::Mat resized, gray, floatGray, dctMat;

    // 缩放到32x32
    cv::resize(image, resized, cv::Size(32, 32));

    // 转为灰度图
    if (resized.channels() == 3)
    {
        cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    }
    else
    {
        gray = resized.clone();
    }

    // 转换为浮点数
    gray.convertTo(floatGray, CV_32F);

    // 计算DCT
    cv::dct(floatGray, dctMat);

    // 取左上角8x8的低频分量
    cv::Mat lowFreq = dctMat(cv::Rect(0, 0, 8, 8));

    // 计算中位数（排除DC分量）
    std::vector<float> values;
    for (int i = 0; i < lowFreq.rows; i++)
    {
        for (int j = 0; j < lowFreq.cols; j++)
        {
            if (i == 0 && j == 0)
                continue; // 跳过DC分量
            values.push_back(lowFreq.at<float>(i, j));
        }
    }

    // 计算中位数
    std::sort(values.begin(), values.end());
    float median = values[values.size() / 2];

    // 生成哈希
    uint64_t hash = 0;
    for (int i = 0; i < lowFreq.rows; i++)
    {
        for (int j = 0; j < lowFreq.cols; j++)
        {
            if (i == 0 && j == 0)
                continue; // 跳过DC分量
            hash = (hash << 1) | ((lowFreq.at<float>(i, j) > median) ? 1 : 0);
        }
    }

    return hash;
}

// 汉明距离
int ImageHasher::hammingDistance(uint64_t hash1, uint64_t hash2)
{
    uint64_t xor_result = hash1 ^ hash2;
    int distance = 0;

    // 计算异或结果中1的位数
    while (xor_result)
    {
        distance += xor_result & 1;
        xor_result >>= 1;
    }

    return distance;
}

// 计算相似度（0-1之间）
double ImageHasher::similarity(uint64_t hash1, uint64_t hash2)
{
    int distance = hammingDistance(hash1, hash2);

    // 假设哈希长度为64位
    return 1.0 - (double)distance / 64.0;
}

// 整数哈希转十六进制字符串
std::string ImageHasher::hashToHex(uint64_t hash)
{
    std::string hexHash;
    const char hexDigits[] = "0123456789abcdef";

    // 从最高位开始处理
    bool leadingZero = true;
    for (int i = 60; i >= 0; i -= 4)
    {
        int nibble = (hash >> i) & 0xF;
        if (leadingZero && nibble == 0 && i > 0)
        {
            continue; // 跳过前导零
        }
        leadingZero = false;
        hexHash += hexDigits[nibble];
    }

    // 如果全为零，返回"0"
    if (hexHash.empty())
    {
        hexHash = "0";
    }

    return hexHash;
}
