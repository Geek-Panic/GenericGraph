#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphNodeDefinitionBase.h"
#include "GraphEditorEdNodeBase.generated.h"

class UGraphEditorEdEdgeNodeBase;
class UEdGraph_GenericGraph;
class SGraphEditorNode;

UCLASS()
class GENERICGRAPHEDITOR_API UGraphEditorEdNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:
	explicit UGraphEditorEdNodeBase();

	UPROPERTY(VisibleAnywhere, Instanced, Category = "GenericGraph")
	TObjectPtr<UGraphNodeDefinitionBase> GenericGraphNode;

	void SetGenericGraphNode(UGraphNodeDefinitionBase* InNode);
	UEdGraph_GenericGraph* GetGenericGraphEdGraph();

	SGraphEditorNode* SEdNode;

	//~ Begin UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	//~ End UEdGraphNode Interface

	virtual FLinearColor GetBackgroundColor() const;
	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

	virtual TSharedPtr<SGraphNode>                GetNodeView();
	virtual TSubclassOf<UGraphNodeDefinitionBase> GetNodeClass();

#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif
};
