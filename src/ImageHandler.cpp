#include "ImageHandler.h"

ImageHandler::ImageHandler(const std::string &detectName, const std::string &effectName)
            :MediaHandler(detectName, effectName)
{}

int ImageHandler::preProcess(const std::string &inFile) 
{
    m_img = cv::imread(inFile.c_str(), 1);
    if (m_img.empty()) 
    {
        fprintf(stderr, "cv::imread %s failed\n", inFile.c_str());
        return -1;
    }

    return 0;
}

int ImageHandler::doTask() 
{
    std::vector<Object> objects;

    int ret = m_detector->detect(m_img, objects);
    if (ret != 0) 
    {
        return -1;
    }
    //ret = m_detector->draw(m_img, objects);

    ret = m_effect->draw(m_img, objects);
    if (ret != 0) 
    {
        return -1;
    }

    return 0;
}

int ImageHandler::postProcess(const std::string &outFile) 
{
    cv::imwrite(outFile.c_str(), m_img);
    cv::destroyAllWindows();
}