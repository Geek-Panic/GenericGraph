#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphNodeDefinitionBase.h"
#include "GraphEditorEdNodeBase.generated.h"

class UGraphEditorEdEdgeNodeBase;
class UEdGraph_GenericGraph;
class SGraphEditorNode;

UCLASS(MinimalAPI)
class UGraphEditorEdNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UGraphEditorEdNodeBase();
	virtual ~UGraphEditorEdNodeBase() override;

	UPROPERTY(VisibleAnywhere, Instanced, Category = "GenericGraph")
	UGraphNodeDefinitionBase* GenericGraphNode;

	void SetGenericGraphNode(UGraphNodeDefinitionBase* InNode);
	UEdGraph_GenericGraph* GetGenericGraphEdGraph();

	SGraphEditorNode* SEdNode;

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
