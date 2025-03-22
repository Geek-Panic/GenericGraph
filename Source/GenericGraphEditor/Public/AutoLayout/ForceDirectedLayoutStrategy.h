#pragma once

#include "AutoLayoutStrategy.h"
#include "CoreMinimal.h"
#include "ForceDirectedLayoutStrategy.generated.h"

UCLASS()
class GENERICGRAPHEDITOR_API UForceDirectedLayoutStrategy : public UAutoLayoutStrategy
{
	GENERATED_BODY()
public:
	UForceDirectedLayoutStrategy();
	virtual ~UForceDirectedLayoutStrategy() override;

	virtual void Layout(UEdGraph* EdGraph) override;

protected:
	virtual FBox2D LayoutOneTree(UGenericGraphNode* RootNode, const FBox2D& PreTreeBound);

	bool bRandomInit;
	float InitTemperature;
	float CoolDownRate;
};
