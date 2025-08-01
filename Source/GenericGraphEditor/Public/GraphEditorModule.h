#pragma once
#include "CoreMinimal.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

struct FGraphPanelNodeFactory;
class IAssetTypeActions;

DECLARE_LOG_CATEGORY_EXTERN(GraphEditorLog, Log, All);

class FGraphEditorModule : public IModuleInterface
{
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
	TSharedPtr<FGraphPanelNodeFactory>    GraphNodeFactory;

protected:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	void UnRegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	static FGraphEditorModule& Get() { return FModuleManager::LoadModuleChecked<FGraphEditorModule>("GenericGraphEditor"); }
	static bool                IsAvailable() { return FModuleManager::Get().IsModuleLoaded("GenericGraphEditor"); }

	
};