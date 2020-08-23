
#pragma once
#include <vector>
#include <memory>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "DetectorManager.h"
#include "EffectManager.h"

class MediaHandler
{
public:
    MediaHandler(const std::string &detectName, const std::string &effectName);
    virtual int preProcess(const std::string &inFile) = 0;
    virtual int doTask() = 0;
    virtual int postProcess(const std::string &outFile) = 0;
protected:
    std::unique_ptr<DetectorManager> m_detectorMgt;
    std::unique_ptr<EffectManager> m_effectMgt;
    
    std::shared_ptr<Detector> m_detector;
    std::shared_ptr<Effect> m_effect;
};