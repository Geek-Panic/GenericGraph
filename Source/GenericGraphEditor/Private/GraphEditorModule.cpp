#include "GraphEditorModule.h"
#include "AssetTypeActions_GenericGraph.h"
#include "GenericGraphAssetEditor/GraphEditorStyle.h"
#include "GenericGraphNodeFactory.h"

DEFINE_LOG_CATEGORY(GraphEditorLog)

#define LOCTEXT_NAMESPACE "Editor_GenericGraph"

void FGraphEditorModule::StartupModule()
{
	UE_LOG(GraphEditorLog, Verbose, TEXT("GraphEditorModule - Startup Module"))

	// Initialize editor style
	FGraphEditorStyle::Initialize();

	// Visual node factory
	GraphNodeFactory = MakeShareable(new FGraphEditorNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphNodeFactory);

	// Register asset types from asset tools module
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const EAssetTypeCategories::Type  AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("GenericGraph")), LOCTEXT("GenericGraphAssetCategory", "GenericGraph"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GenericGraph(AssetCategory)));
}

void FGraphEditorModule::ShutdownModule()
{
	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (auto& AssetTypeAction : CreatedAssetTypeActions)
		{
			if (AssetTypeAction.IsValid())
			{
				AssetTools.UnregisterAssetTypeActions(AssetTypeAction.ToSharedRef());
			}
		}
	}
	CreatedAssetTypeActions.Empty();

	// Unregister node factories
	if (GraphNodeFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(GraphNodeFactory);
		GraphNodeFactory.Reset();
	}

	FGraphEditorStyle::Shutdown();
}

void FGraphEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

IMPLEMENT_MODULE(FGraphEditorModule, GenericGraphEditor)

#undef LOCTEXT_NAMESPACE
