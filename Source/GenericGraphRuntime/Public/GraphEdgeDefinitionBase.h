#pragma once

#include "CoreMinimal.h"
#include "GraphNodeDefinitionBase.h"
#include "GraphEdgeDefinitionBase.generated.h"

class UGraphDefinitionBase;

UCLASS(Blueprintable)
class GENERICGRAPHRUNTIME_API UGraphEdgeDefinitionBase : public UObject
{
	GENERATED_BODY()

public:
	
	UGraphEdgeDefinitionBase();
	virtual ~UGraphEdgeDefinitionBase() override;


	UFUNCTION(BlueprintPure, Category = "GenericGraphEdge")
	UGraphDefinitionBase* GetGraph() const;

	// TODO : Add CanTransition logic
	
#if WITH_EDITOR
	virtual FText GetNodeTitle() const { return NodeTitle; }
	FLinearColor GetEdgeColour() const { return EdgeColour; }

	virtual void SetNodeTitle(const FText& NewTitle);
#endif

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "GenericGraphNode")
	UGraphDefinitionBase* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphEdge")
	UGraphNodeDefinitionBase* StartNode;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphEdge")
	UGraphNodeDefinitionBase* EndNode;

	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	bool bShouldDrawTitle = false;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText NodeTitle;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphEdge")
	FLinearColor EdgeColour = FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
#endif

};
