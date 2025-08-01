#include "AutoLayout/AutoLayoutStrategy.h"
#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"
#include "GenericGraphAssetEditor/SGraphEditorNode.h"
#include "Kismet/KismetMathLibrary.h"

UAutoLayoutStrategy::UAutoLayoutStrategy()
{
	Settings = nullptr;
	MaxIteration = 50;
	OptimalDistance = 150;
}

UAutoLayoutStrategy::~UAutoLayoutStrategy() {}

FBox2D UAutoLayoutStrategy::GetNodeBound(UEdGraphNode* EdNode)
{
	const auto NodeWidth = GetNodeWidth(Cast<UGraphEditorEdNodeBase>(EdNode));
	const auto NodeHeight = GetNodeHeight(Cast<UGraphEditorEdNodeBase>(EdNode));
	const auto Min = FVector2D(EdNode->NodePosX, EdNode->NodePosY);
	const auto Max = FVector2D(EdNode->NodePosX + NodeWidth, EdNode->NodePosY + NodeHeight);
	return FBox2D(Min, Max);
}

FBox2D UAutoLayoutStrategy::GetActualBounds(UGraphNodeDefinitionBase* RootNode)
{
	int Level = 0;
	TArray<UGraphNodeDefinitionBase*> CurrLevelNodes = {RootNode};
	TArray<UGraphNodeDefinitionBase*> NextLevelNodes;

	FBox2D Rtn = GetNodeBound(EdGraph->NodeMap[RootNode]);

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UGraphNodeDefinitionBase* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			Rtn += GetNodeBound(EdGraph->NodeMap[Node]);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
	return Rtn;
}

void UAutoLayoutStrategy::RandomLayoutOneTree(UGraphNodeDefinitionBase* RootNode, const FBox2D& Bound)
{
	int Level = 0;
	TArray<UGraphNodeDefinitionBase*> CurrLevelNodes = {RootNode};
	TArray<UGraphNodeDefinitionBase*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UGraphNodeDefinitionBase* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			UGraphEditorEdNodeBase* EdNode_Node = EdGraph->NodeMap[Node];

			EdNode_Node->NodePosX = UKismetMathLibrary::RandomFloatInRange(Bound.Min.X, Bound.Max.X);
			EdNode_Node->NodePosY = UKismetMathLibrary::RandomFloatInRange(Bound.Min.Y, Bound.Max.Y);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}

int32 UAutoLayoutStrategy::GetNodeWidth(UGraphEditorEdNodeBase* EdNode)
{
	return EdNode->SEdNode->GetCachedGeometry().GetLocalSize().X;
}

int32 UAutoLayoutStrategy::GetNodeHeight(UGraphEditorEdNodeBase* EdNode)
{
	return EdNode->SEdNode->GetCachedGeometry().GetLocalSize().Y;
}
