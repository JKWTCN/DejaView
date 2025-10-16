#include "ImageHasher.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <algorithm>

// 平均哈希
std::string ImageHasher::averageHash(const cv::Mat &image)
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
    std::string hash;
    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols; j++)
        {
            hash += (gray.at<uchar>(i, j) > mean) ? "1" : "0";
        }
    }

    return hash;
}

// 差异哈希
std::string ImageHasher::differenceHash(const cv::Mat &image)
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
    std::string hash;
    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols - 1; j++)
        {
            hash += (gray.at<uchar>(i, j + 1) > gray.at<uchar>(i, j)) ? "1" : "0";
        }
    }

    return hash;
}

// 感知哈希（DCT实现）
std::string ImageHasher::perceptualHash(const cv::Mat &image)
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
    std::string hash;
    for (int i = 0; i < lowFreq.rows; i++)
    {
        for (int j = 0; j < lowFreq.cols; j++)
        {
            if (i == 0 && j == 0)
                continue; // 跳过DC分量
            hash += (lowFreq.at<float>(i, j) > median) ? "1" : "0";
        }
    }

    return hash;
}

// 汉明距离
int ImageHasher::hammingDistance(const std::string &hash1, const std::string &hash2)
{
    if (hash1.length() != hash2.length())
    {
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < hash1.length(); i++)
    {
        if (hash1[i] != hash2[i])
        {
            distance++;
        }
    }
    return distance;
}

// 计算相似度（0-1之间）
double ImageHasher::similarity(const std::string &hash1, const std::string &hash2)
{
    int distance = hammingDistance(hash1, hash2);
    if (distance == -1)
        return 0.0;

    return 1.0 - (double)distance / hash1.length();
}

// 二进制哈希转十六进制
std::string ImageHasher::binaryToHex(const std::string &binaryHash)
{
    std::string hexHash;
    for (size_t i = 0; i < binaryHash.length(); i += 4)
    {
        std::string nibble = binaryHash.substr(i, 4);
        int value = 0;
        for (char c : nibble)
        {
            value = (value << 1) | (c - '0');
        }
        hexHash += "0123456789abcdef"[value];
    }
    return hexHash;
}
