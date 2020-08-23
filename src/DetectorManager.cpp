
#include "YolactDetector.h"
#include "DetectorManager.h"


DetectorManager::DetectorManager(const DetectorMap_t& detectors)
    : m_detectors(detectors) 
{}

std::unique_ptr<DetectorManager> DetectorManager::create() 
{
	DetectorMap_t detectors = 
	{
		{"yolact", std::make_shared<DetectorLauncher<Yolact>>()},
	};

	auto mgt = new DetectorManager(detectors);
	if (!mgt) 
	{
		return nullptr;
	}

	return std::unique_ptr<DetectorManager>(std::move(mgt));
}

std::shared_ptr<Detector> DetectorManager::createDetector(const std::string& detectorName) 
{
	auto it = m_detectors.find(detectorName);
	if (m_detectors.end() == it) 
	{
		return nullptr;
	}

	auto& detectorLauncher = it->second;
	if (!detectorLauncher) 
	{
		return nullptr;
	}

	auto detector = std::shared_ptr<Detector>(detectorLauncher->create());
	if (!detector) 
	{
		return nullptr;
	}

	return detector;
}


