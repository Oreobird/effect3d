#pragma once
#include "IEffect.h"

class LREffect final : public Effect 
{
public:
    int draw(cv::Mat& image, const std::vector<Object>& objects);
};

class RLEffect final : public Effect 
{
    public:
    int draw(cv::Mat& image, const std::vector<Object>& objects);
};

class NFEffect final : public Effect 
{
    public:
    int draw(cv::Mat& image, const std::vector<Object>& objects);
};

class FNEffect final : public Effect 
{
    public:
    int draw(cv::Mat& image, const std::vector<Object>& objects);
};
