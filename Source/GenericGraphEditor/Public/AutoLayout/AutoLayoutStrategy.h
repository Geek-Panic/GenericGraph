#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "GenericGraphAssetEditor/EdGraph_GenericGraph.h"
#include "GenericGraphAssetEditor/EdNode_GenericGraphEdge.h"
#include "GenericGraphAssetEditor/EdNode_GenericGraphNode.h"
#include "GenericGraphAssetEditor/Settings_GenericGraphEditor.h"
#include "GenericGraphDefinition.h"
#include "AutoLayoutStrategy.generated.h"

UCLASS(abstract)
class GENERICGRAPHEDITOR_API UAutoLayoutStrategy : public UObject
{
	GENERATED_BODY()
public:
	UAutoLayoutStrategy();
	virtual ~UAutoLayoutStrategy() override;

	virtual void Layout(UEdGraph* G){};

	class UGenericGraphEditorSettings* Settings;

protected:
	int32 GetNodeWidth(UEdNode_GenericGraphNode* EdNode);

	int32 GetNodeHeight(UEdNode_GenericGraphNode* EdNode);

	FBox2D GetNodeBound(UEdGraphNode* EdNode);

	FBox2D GetActualBounds(UGenericGraphNode* RootNode);

	virtual void RandomLayoutOneTree(UGenericGraphNode* RootNode, const FBox2D& Bound);

	UGenericGraphDefinition* Graph;
	UEdGraph_GenericGraph* EdGraph;
	int32 MaxIteration;
	int32 OptimalDistance;
};
