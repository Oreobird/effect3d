#pragma once
#include "IDetector.h"

class Yolact final : public Detector 
{
public:
    int detect(cv::Mat& image, std::vector<Object>& objects);
    int draw(cv::Mat& image, const std::vector<Object>& objects);

private:
    float intersection_area(const Object& a, const Object& b);
    void qsort_descent_inplace(std::vector<Object>& objects, int left, int right);
    void qsort_descent_inplace(std::vector<Object>& objects);
    void nms_sorted_bboxes(const std::vector<Object>& objects, std::vector<int>& picked, float nms_threshold);
};
