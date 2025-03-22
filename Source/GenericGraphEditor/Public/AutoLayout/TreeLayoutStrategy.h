#pragma once

#include "AutoLayoutStrategy.h"
#include "CoreMinimal.h"
#include "TreeLayoutStrategy.generated.h"

UCLASS()
class GENERICGRAPHEDITOR_API UTreeLayoutStrategy : public UAutoLayoutStrategy
{
	GENERATED_BODY()
public:
	UTreeLayoutStrategy();
	virtual ~UTreeLayoutStrategy() override;

	virtual void Layout(UEdGraph* EdGraph) override;

protected:
	void InitPass(UGenericGraphNode* RootNode, const FVector2D& Anchor);
	bool ResolveConflictPass(UGenericGraphNode* Node);

	bool ResolveConflict(UGenericGraphNode* LRoot, UGenericGraphNode* RRoot);

	void GetLeftContour(UGenericGraphNode* RootNode, int32 Level, TArray<UEdNode_GenericGraphNode*>& Contour);
	void GetRightContour(UGenericGraphNode* RootNode, int32 Level, TArray<UEdNode_GenericGraphNode*>& Contour);

	void ShiftSubTree(UGenericGraphNode* RootNode, const FVector2D& Offset);

	void UpdateParentNodePosition(UGenericGraphNode* RootNode);
};
