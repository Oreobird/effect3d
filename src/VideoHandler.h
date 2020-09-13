
#pragma once
#include <vector>
#include <memory>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "MediaHandler.h"

class VideoHandler: public MediaHandler 
{
public:
    VideoHandler(const std::string &detectName, const std::string &effectName);
    int preProcess(const std::string &inFile, const std::string &targetName);
    int doTask();
    int postProcess(const std::string &outFile);
private:
    std::shared_ptr<cv::VideoCapture> m_cap;
    std::shared_ptr<cv::VideoWriter> m_videoWriter;
    std::vector<cv::Mat> m_frames;
    std::string m_targetName;
};
