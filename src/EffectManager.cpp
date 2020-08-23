#include <vector>
#include "EffectManager.h"
#include "Effect3d.h"


EffectManager::EffectManager(const EffectMap_t& effects)
    : m_effects(effects) 
{}

std::unique_ptr<EffectManager> EffectManager::create() 
{
	EffectMap_t effects = 
	{
		{"lr", std::make_shared<EffectLauncher<LREffect>>()},
		{"rl", std::make_shared<EffectLauncher<RLEffect>>()},
		{"nf", std::make_shared<EffectLauncher<NFEffect>>()},
		{"fn", std::make_shared<EffectLauncher<FNEffect>>()},
	};

	auto mgt = new EffectManager(effects);
	if (!mgt) 
	{
		return nullptr;
	}

	return std::unique_ptr<EffectManager>(std::move(mgt));
}

std::shared_ptr<Effect> EffectManager::createEffect(const std::string& effectName) 
{
	auto it = m_effects.find(effectName);
	if (m_effects.end() == it) 
	{
		return nullptr;
	}

	auto& effectLauncher = it->second;
	if (!effectLauncher) 
	{
		return nullptr;
	}

	auto effect = std::shared_ptr<Effect>(effectLauncher->create());
	if (!effect) 
	{
		return nullptr;
	}

	return effect;
}

