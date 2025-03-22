#pragma once
#include "GenericGraphEditorModule.h"
#include "Modules/ModuleManager.h"
#include <EdGraphUtilities.h>
#include <IAssetTools.h>

class FGenericGraphEditor : public IGenericGraphEditor
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	EAssetTypeCategories::Type GenericGraphAssetCategoryBit;

	TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_GenericGraph;
};