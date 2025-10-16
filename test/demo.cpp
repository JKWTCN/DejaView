#include <opencv2/opencv.hpp>
#include <iostream>
#include <bitset>
#include <filesystem>
#include "tools.h"
#include "ImageHasher.h"
int main()
{
    std::wstring path1=L"D:/Temporary/2510/16/1.jpg";
    std::wstring path2=L"D:/Temporary/2510/16/2.jpg";
    std::wstring path3=L"D:/Temporary/2510/16/3.jpg";
    std::wstring path4=L"D:/Temporary/2510/16/4.jpg";
    std::wstring path5=L"D:/Temporary/2510/16/5.jpg";
    std::wstring path6 = L"D:/Temporary/2510/16/6.jpg";
    auto image1=loadImage(path1);
    auto image2=loadImage(path2);
    auto image3=loadImage(path3);
    auto image4=loadImage(path4);
    auto image5=loadImage(path5);
    auto image6 = loadImage(path6);
    uint64_t distance = hammingDistanceOptimized(ImageHasher::perceptualHash(image2), ImageHasher::perceptualHash(image5));
    std::cout << distance << std::endl;
}
