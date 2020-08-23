#include "VideoHandler.h"

MediaHandler::MediaHandler(const std::string &detectName, const std::string &effectName) 
{
    m_detectorMgt = DetectorManager::create();
    m_detector = m_detectorMgt->createDetector(detectName);

    m_effectMgt = EffectManager::create();
    m_effect = m_effectMgt->createEffect(effectName);
}
