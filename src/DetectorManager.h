#pragma once
#include <map>
#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>

#include "common.h"
#include "IDetector.h"

class DetectorManager {
public:
    struct DetectorLauncherInterface {
        virtual ~DetectorLauncherInterface() {}
        virtual Detector* create() = 0;
    };

    template <typename T>
    struct DetectorLauncher final : public DetectorLauncherInterface {
        Detector* create() {
            return new T();
        }
    };

    typedef std::map<std::string, std::shared_ptr<DetectorLauncherInterface>> DetectorMap_t;

    DetectorManager(const DetectorMap_t& detectors);

    static std::unique_ptr<DetectorManager> create();

    std::shared_ptr<Detector> createDetector(const std::string& detectorName);

private:
    DetectorMap_t m_detectors;
};
