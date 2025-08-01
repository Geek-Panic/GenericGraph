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
	void InitPass(UGraphNodeDefinitionBase* RootNode, const FVector2D& Anchor);
	bool ResolveConflictPass(UGraphNodeDefinitionBase* Node);

	bool ResolveConflict(UGraphNodeDefinitionBase* LRoot, UGraphNodeDefinitionBase* RRoot);

	void GetLeftContour(UGraphNodeDefinitionBase* RootNode, int32 Level, TArray<UGraphEditorEdNodeBase*>& Contour);
	void GetRightContour(UGraphNodeDefinitionBase* RootNode, int32 Level, TArray<UGraphEditorEdNodeBase*>& Contour);

	void ShiftSubTree(UGraphNodeDefinitionBase* RootNode, const FVector2D& Offset);

	void UpdateParentNodePosition(UGraphNodeDefinitionBase* RootNode);
};
