#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphNodeDefinitionBase.h"
#include "EdNode_GenericGraphNode.generated.h"

class UEdNode_GenericGraphEdge;
class UEdGraph_GenericGraph;
class SEdNode_GenericGraphNode;

UCLASS(MinimalAPI)
class UEdNode_GenericGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdNode_GenericGraphNode();
	virtual ~UEdNode_GenericGraphNode() override;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "GenericGraph")
	UGraphNodeDefinitionBase* GenericGraphNode;

	void SetGenericGraphNode(UGraphNodeDefinitionBase* InNode);
	UEdGraph_GenericGraph* GetGenericGraphEdGraph();

	SEdNode_GenericGraphNode* SEdNode;

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

	virtual FLinearColor GetBackgroundColor() const;
	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif
};
