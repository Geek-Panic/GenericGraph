#pragma once
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(GenericGraphRuntime, Log, All);

class IGenericGraphRuntime : public IModuleInterface
{

public:
	static IGenericGraphRuntime& Get() { return FModuleManager::LoadModuleChecked<IGenericGraphRuntime>("GenericGraphRuntime"); }
	static bool                  IsAvailable() { return FModuleManager::Get().IsModuleLoaded("GenericGraphRuntime"); }
};
