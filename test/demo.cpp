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
    auto image1=loadImage(path1);
    //auto image2=cv::imread(std::filesystem::path(path2).string());
    //auto image3=cv::imread(std::filesystem::path(path3).string());
    //auto image4=cv::imread(std::filesystem::path(path4).string());
    //auto image5=cv::imread(std::filesystem::path(path5).string());
	std::cout<<ImageHasher::perceptualHash(image1)<<std::endl;
}
