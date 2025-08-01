#include "GenericGraphRuntimePCH.h"

DEFINE_LOG_CATEGORY(GenericGraphRuntime)

class FGenericGraphRuntime final : public IGenericGraphRuntime
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FGenericGraphRuntime, GenericGraphRuntime)

void FGenericGraphRuntime::StartupModule()
{
}

void FGenericGraphRuntime::ShutdownModule()
{
}
