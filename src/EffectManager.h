#pragma once
#include <map>
#include <memory>

#include "IEffect.h"


class EffectManager 
{
public:
    struct EffectLauncherInterface 
    {
        virtual ~EffectLauncherInterface() {}
        virtual Effect* create() = 0;
    };

    template <typename T>
    struct EffectLauncher final : public EffectLauncherInterface 
    {
        Effect* create() {
            return new T();
        }
    };

    typedef std::map<std::string, std::shared_ptr<EffectLauncherInterface>> EffectMap_t;

    EffectManager(const EffectMap_t& effects);

    static std::unique_ptr<EffectManager> create();

    std::shared_ptr<Effect> createEffect(const std::string& effectName);

private:
    EffectMap_t m_effects;
};
