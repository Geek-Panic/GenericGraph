#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_GenericGraph.generated.h"

class UGraphDefinitionBase;
class UGraphNodeDefinitionBase;
class UGraphEdgeDefinitionBase;
class UGraphEditorEdNodeBase;
class UGraphEditorEdEdgeNodeBase;

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
	TMap<UGraphNodeDefinitionBase*, UGraphEditorEdNodeBase*> NodeMap;

	UPROPERTY(Transient)
	TMap<UGraphEdgeDefinitionBase*, UGraphEditorEdEdgeNodeBase*> EdgeMap;

protected:
	void Clear();

	void SortNodes(UGraphNodeDefinitionBase* RootNode);
};
