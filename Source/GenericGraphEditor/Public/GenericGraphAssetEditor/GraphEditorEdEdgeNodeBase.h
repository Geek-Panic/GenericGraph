#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphEditorEdEdgeNodeBase.generated.h"

class UGraphNodeDefinitionBase;
class UGraphEdgeDefinitionBase;
class UGraphEditorEdNodeBase;

UCLASS(MinimalAPI)
class UGraphEditorEdEdgeNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UGraphEditorEdEdgeNodeBase();

	UPROPERTY()
	TObjectPtr<class UEdGraph> Graph;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "GenericGraph")
	UGraphEdgeDefinitionBase* GenericGraphEdge;

	void SetEdge(UGraphEdgeDefinitionBase* Edge);

	virtual void AllocateDefaultPins() override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;

	virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void CreateConnections(UGraphEditorEdNodeBase* Start, UGraphEditorEdNodeBase* End);

	UGraphEditorEdNodeBase* GetStartNode();
	UGraphEditorEdNodeBase* GetEndNode();
};
