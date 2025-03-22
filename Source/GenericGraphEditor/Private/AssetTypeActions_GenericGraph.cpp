#include "AssetTypeActions_GenericGraph.h"
#include "GenericGraphAssetEditor/AssetEditor_GenericGraph.h"
#include "GenericGraphEditorPCH.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_GenericGraph"

FAssetTypeActions_GenericGraph::FAssetTypeActions_GenericGraph(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FAssetTypeActions_GenericGraph::GetName() const
{
	return LOCTEXT("FGenericGraphAssetTypeActionsName", "Generic Graph");
}

FColor FAssetTypeActions_GenericGraph::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FAssetTypeActions_GenericGraph::GetSupportedClass() const
{
	return UGenericGraphDefinition::StaticClass();
}

void FAssetTypeActions_GenericGraph::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UGenericGraphDefinition* Graph = Cast<UGenericGraphDefinition>(*ObjIt))
		{
			// Open generic graph editor for each
			const TSharedRef<FAssetEditor_GenericGraph> NewGraphEditor(new FAssetEditor_GenericGraph());
			NewGraphEditor->InitGenericGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

uint32 FAssetTypeActions_GenericGraph::GetCategories()
{
	return AssetCategory;
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE