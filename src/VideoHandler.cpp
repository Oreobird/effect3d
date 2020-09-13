#include "VideoHandler.h"
#include <iostream>

VideoHandler::VideoHandler(const std::string &detectName, const std::string &effectName)
            :MediaHandler(detectName, effectName),
            m_cap(nullptr),
            m_videoWriter(nullptr),
            m_targetName("person")
{
    m_frames.clear();
}

int VideoHandler::preProcess(const std::string &videoInFile, const std::string &targetName) 
{
    m_cap = std::make_shared<cv::VideoCapture>(videoInFile.c_str());
    if (!m_cap || !m_cap->isOpened()) 
    {
        std::cout << "Error open video file" << std::endl;
        return -1;
    }
 
    m_targetName = targetName;
    return 0;
}

int VideoHandler::doTask() 
{
    int frame_num = 0;
    bool half_count = false;
    int frame_count = m_cap->get(cv::CAP_PROP_FRAME_COUNT);

    while (true) 
    {
        cv::Mat frame;
        m_cap->read(frame);

        if (frame.empty()) 
        {
            break;
        }

        frame_num++;
        std::cout << "total frame " << frame_count << ", current_num " << frame_num << " progress " << (float)frame_num / frame_count * 100 << "%" << std::endl;
        std::vector<Object> objects;

        m_detector->detect(frame, objects, m_targetName);

        //m_detector->draw(frame, objects);
        m_effect->draw(frame, objects);

        m_frames.push_back(frame);

        cv::waitKey(5);
    }
}

int VideoHandler::postProcess(const std::string &videoOutFile) 
{
    int frame_width = m_cap->get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = m_cap->get(cv::CAP_PROP_FRAME_HEIGHT);

    m_videoWriter = std::make_shared<cv::VideoWriter>(videoOutFile, 0x00000021, 25, cv::Size(frame_width, frame_height));
    if (!m_videoWriter) 
    {
        std::cout << "Error create video writer" << std::endl;
        return -1;
    }

    for (auto frame : m_frames) 
    {
        m_videoWriter->write(frame);
    }
    
    m_cap->release();
    cv::destroyAllWindows();
}
