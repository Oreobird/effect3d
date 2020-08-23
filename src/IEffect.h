#pragma once
#include <vector>
#include <opencv2/core/core.hpp>
#include "common.h"

class Effect {
public:
    virtual ~Effect() {}
    virtual int draw(cv::Mat& image, const std::vector<Object>& objects) = 0;
};

