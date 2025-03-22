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
	
	UGraphEdgeDefinitionBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual ~UGraphEdgeDefinitionBase() override;

	UFUNCTION(BlueprintPure, Category = "GenericGraphEdge")
	UGraphDefinitionBase* GetGraph() const;

	// TODO : Add transition logic
	
#if WITH_EDITOR
	virtual FText GetDisplayName() const { return DisplayName; }
	FLinearColor GetEdgeColour() const { return EdgeColour; }

	virtual void SetNodeTitle(const FText& NewTitle);
#endif

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "GenericGraphNode")
	TObjectPtr<UGraphDefinitionBase> Graph = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphEdge")
	TObjectPtr<UGraphNodeDefinitionBase> StartNode = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphEdge")
	TObjectPtr<UGraphNodeDefinitionBase> EndNode = nullptr;

	// TODO : Add transition type/behavior property
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	bool bShouldDrawDisplayName = false;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphEdge")
	FLinearColor EdgeColour = FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
#endif

};
