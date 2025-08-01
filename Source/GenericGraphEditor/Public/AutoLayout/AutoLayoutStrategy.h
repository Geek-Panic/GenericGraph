#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "GenericGraphAssetEditor/EdGraph_GenericGraph.h"
#include "GenericGraphAssetEditor/Settings_GenericGraphEditor.h"
#include "GraphDefinitionBase.h"
#include "AutoLayoutStrategy.generated.h"

UCLASS(abstract)
class GENERICGRAPHEDITOR_API UAutoLayoutStrategy : public UObject
{
	GENERATED_BODY()
	
public:
	UAutoLayoutStrategy();
	virtual ~UAutoLayoutStrategy() override;

	virtual void Layout(UEdGraph* G){};

	UPROPERTY()
	TObjectPtr<class UGenericGraphEditorSettings> Settings;

protected:
	int32 GetNodeWidth(UGraphEditorEdNodeBase* EdNode);
	int32 GetNodeHeight(UGraphEditorEdNodeBase* EdNode);

	FBox2D GetNodeBound(UEdGraphNode* EdNode);
	FBox2D GetActualBounds(UGraphNodeDefinitionBase* RootNode);

	virtual void RandomLayoutOneTree(UGraphNodeDefinitionBase* RootNode, const FBox2D& Bound);

	UPROPERTY()
	TObjectPtr<UGraphDefinitionBase> Graph;

	UPROPERTY()
	TObjectPtr<UEdGraph_GenericGraph> EdGraph;

	int32 MaxIteration;
	int32 OptimalDistance;
};
