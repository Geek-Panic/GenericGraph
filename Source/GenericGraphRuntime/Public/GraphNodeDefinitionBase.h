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
	
	UGraphNodeDefinitionBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual ~UGraphNodeDefinitionBase() override;


#if WITH_EDITOR
	virtual bool IsNameEditable() const;

	virtual FLinearColor GetBackgroundColor() const;

	virtual FText GetDisplayName() const;
	virtual void SetDisplayName(const FText& InDisplayName);

	virtual bool CanCreateConnection(UGraphNodeDefinitionBase* Other, FText& ErrorMessage);
	virtual bool CanCreateConnectionTo(UGraphNodeDefinitionBase* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage);
	virtual bool CanCreateConnectionFrom(UGraphNodeDefinitionBase* Other, int32 NumberOfParentNodes, FText& ErrorMessage);
#endif

	UFUNCTION(BlueprintCallable, Category = "Node")
	virtual UGraphEdgeDefinitionBase* GetEdge(UGraphNodeDefinitionBase* ChildNode);

	UFUNCTION(BlueprintCallable, Category = "Node")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category = "Node")
	UGraphDefinitionBase* GetGraph() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Node")
	FText GetDescription() const;
	virtual FText GetDescription_Implementation() const;

	
	UPROPERTY(EditDefaultsOnly, Category = "Node")
	FText DisplayName = FText();
	
	UPROPERTY(/*VisibleDefaultsOnly, Category = "Node"*/)
	UGraphDefinitionBase* Graph = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Node")
	TArray<TObjectPtr<UGraphNodeDefinitionBase>> ParentNodes = {};

	UPROPERTY(BlueprintReadOnly, Category = "Node")
	TArray<TObjectPtr<UGraphNodeDefinitionBase>> ChildrenNodes = {};
	
	UPROPERTY(BlueprintReadOnly, Category = "Node")
	TMap<TObjectPtr<UGraphNodeDefinitionBase>, TObjectPtr<UGraphEdgeDefinitionBase>> Edges = {};

	
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "Editor")
	TSubclassOf<UGraphDefinitionBase> CompatibleGraphType = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Editor")
	FLinearColor BackgroundColor = FLinearColor::Black;

	UPROPERTY(EditDefaultsOnly, Category = "Editor")
	FText ContextMenuName = FText();

	UPROPERTY(EditDefaultsOnly, Category = "Editor")
	ENodeLimit ParentLimitType = ENodeLimit::Unlimited;

	UPROPERTY(EditDefaultsOnly, Category = "Editor", meta = (ClampMin = "0", EditCondition = "ParentLimitType == ENodeLimit::Limited", EditConditionHides))
	int32 ParentLimit = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Editor")
	ENodeLimit ChildrenLimitType = ENodeLimit::Unlimited;

	UPROPERTY(EditDefaultsOnly, Category = "Editor", meta = (ClampMin = "0", EditCondition = "ChildrenLimitType == ENodeLimit::Limited", EditConditionHides))
	int32 ChildrenLimit = 0;
#endif
	
};
