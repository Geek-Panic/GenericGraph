#include "GraphDefinitionBase.h"
#include "Engine/Engine.h"
#include "GenericGraphRuntimePCH.h"

#define LOCTEXT_NAMESPACE "GenericGraph"

UGraphDefinitionBase::UGraphDefinitionBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.Get())
{
	NodeType = UGraphNodeDefinitionBase::StaticClass();
	EdgeType = UGraphEdgeDefinitionBase::StaticClass();

	bEdgeEnabled = true;

	#if WITH_EDITORONLY_DATA
	EditorGraph = nullptr;

	bCanRenameNode = true;
	#endif
}

UGraphDefinitionBase::~UGraphDefinitionBase() {}

void UGraphDefinitionBase::Print(const bool ToConsole /*= true*/, const bool ToScreen /*= true*/) const
{
	int Level = 0;
	TArray<UGraphNodeDefinitionBase*> CurrLevelNodes = RootNodes;
	TArray<UGraphNodeDefinitionBase*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UGraphNodeDefinitionBase* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			FString Message = FString::Printf(TEXT("%s, Level %d"), *Node->GetDescription().ToString(), Level);

			if (ToConsole)
			{
				LOG_INFO(TEXT("%s"), *Message);
			}

			if (ToScreen && GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, Message);
			}

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

int UGraphDefinitionBase::GetLevelNum() const
{
	int Level = 0;
	TArray<UGraphNodeDefinitionBase*> CurrLevelNodes = RootNodes;
	TArray<UGraphNodeDefinitionBase*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UGraphNodeDefinitionBase* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}

	return Level;
}

void UGraphDefinitionBase::GetNodesByLevel(const int Level, TArray<UGraphNodeDefinitionBase*>& Nodes) const
{
	int CurrentLevel = 0;
	TArray<UGraphNodeDefinitionBase*> NextLevelNodes;

	Nodes = RootNodes;

	while (Nodes.Num() != 0)
	{
		if (CurrentLevel == Level)
		{
			break;
		}

		for (int i = 0; i < Nodes.Num(); ++i)
		{
			UGraphNodeDefinitionBase* Node = Nodes[i];
			check(Node != nullptr);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				NextLevelNodes.Add(Node->ChildrenNodes[j]);
			}
		}

		Nodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++CurrentLevel;
	}
}

void UGraphDefinitionBase::ClearGraph()
{
	for (int i = 0; i < AllNodes.Num(); ++i)
	{
		if (UGraphNodeDefinitionBase* Node = AllNodes[i])
		{
			Node->ParentNodes.Empty();
			Node->ChildrenNodes.Empty();
			Node->Edges.Empty();
		}
	}

	AllNodes.Empty();
	RootNodes.Empty();
}

#undef LOCTEXT_NAMESPACE
