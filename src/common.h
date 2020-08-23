#pragma once

#include <map>
#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>

struct Object
{
    cv::Rect_<float> rect;
    int label;
    float prob;
    std::vector<float> maskdata;
    cv::Mat mask;
};

