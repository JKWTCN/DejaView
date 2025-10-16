#include "tools.h"
#include <filesystem>

cv::Mat loadImage(const std::wstring & path)
{
	return cv::imread(std::filesystem::path(path).string());
}
