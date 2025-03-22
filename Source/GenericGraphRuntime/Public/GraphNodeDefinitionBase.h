#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GraphNodeDefinitionBase.generated.h"

class UGraphDefinitionBase;
class UGraphEdgeDefinitionBase;

UENUM(BlueprintType)
enum class ENodeLimit : uint8
{
	Unlimited,
	Limited
};

UCLASS(Blueprintable)
class GENERICGRAPHRUNTIME_API UGraphNodeDefinitionBase : public UObject
{
	GENERATED_BODY()

	friend class UGraphDefinitionBase;
	
public:
	
	UGraphNodeDefinitionBase();
	virtual ~UGraphNodeDefinitionBase() override;


#if WITH_EDITOR
	virtual bool IsNameEditable() const;

	virtual FLinearColor GetBackgroundColor() const;

	virtual FText GetDisplayName() const;

	virtual void SetDisplayName(const FText& NewDisplayName);

	virtual bool CanCreateConnection(UGraphNodeDefinitionBase* Other, FText& ErrorMessage);

	virtual bool CanCreateConnectionTo(UGraphNodeDefinitionBase* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage);
	virtual bool CanCreateConnectionFrom(UGraphNodeDefinitionBase* Other, int32 NumberOfParentNodes, FText& ErrorMessage);
#endif

	UFUNCTION(BlueprintCallable, Category = "GenericGraphNode")
	virtual UGraphEdgeDefinitionBase* GetEdge(UGraphNodeDefinitionBase* ChildNode);

	UFUNCTION(BlueprintCallable, Category = "GenericGraphNode")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category = "GenericGraphNode")
	UGraphDefinitionBase* GetGraph() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GenericGraphNode")
	FText GetDescription() const;
	virtual FText GetDescription_Implementation() const;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode")
	FText DisplayName;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "GenericGraphNode")
	UGraphDefinitionBase* Graph;
	
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TArray<TObjectPtr<UGraphNodeDefinitionBase>> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TArray<TObjectPtr<UGraphNodeDefinitionBase>> ChildrenNodes;
	
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraphNode")
	TMap<TObjectPtr<UGraphNodeDefinitionBase>, TObjectPtr<UGraphEdgeDefinitionBase>> Edges;
	
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "GenericGraphNode_Editor")
	TSubclassOf<UGraphDefinitionBase> CompatibleGraphType;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FLinearColor BackgroundColor;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	FText ContextMenuName;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	ENodeLimit ParentLimitType;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor", meta = (ClampMin = "0", EditCondition = "ParentLimitType == ENodeLimit::Limited", EditConditionHides))
	int32 ParentLimit;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor")
	ENodeLimit ChildrenLimitType;

	UPROPERTY(EditDefaultsOnly, Category = "GenericGraphNode_Editor", meta = (ClampMin = "0", EditCondition = "ChildrenLimitType == ENodeLimit::Limited", EditConditionHides))
	int32 ChildrenLimit;
#endif
};
