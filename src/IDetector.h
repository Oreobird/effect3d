#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include "common.h"

class Detector {
public:
    virtual ~Detector() {}
    virtual int detect(cv::Mat& image, std::vector<Object>& objects) = 0;
    virtual int draw(cv::Mat& image, const std::vector<Object>& objects) = 0;
};

