#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_GenericGraph.generated.h"

class UGraphDefinitionBase;
class UGraphNodeDefinitionBase;
class UGraphEdgeDefinitionBase;
class UEdNode_GenericGraphNode;
class UEdNode_GenericGraphEdge;

UCLASS()
class GENERICGRAPHEDITOR_API UEdGraph_GenericGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UEdGraph_GenericGraph();
	virtual ~UEdGraph_GenericGraph() override;

	virtual void RebuildGenericGraph();

	UGraphDefinitionBase* GetGenericGraph() const;

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;
	virtual void PostEditUndo() override;

	UPROPERTY(Transient)
	TMap<UGraphNodeDefinitionBase*, UEdNode_GenericGraphNode*> NodeMap;

	UPROPERTY(Transient)
	TMap<UGraphEdgeDefinitionBase*, UEdNode_GenericGraphEdge*> EdgeMap;

protected:
	void Clear();

	void SortNodes(UGraphNodeDefinitionBase* RootNode);
};
