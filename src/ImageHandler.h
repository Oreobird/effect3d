
#pragma once
#include <vector>
#include <memory>
#include <string>

#include <opencv2/core/core.hpp>

#include "MediaHandler.h"

class ImageHandler: public MediaHandler 
{
public:
    ImageHandler(const std::string &detectName, const std::string &effectName);
    int preProcess(const std::string &inFile, const std::string &targetName);
    int doTask();
    int postProcess(const std::string &outFile);
private:
    cv::Mat m_img;
    std::string m_targetName;
};