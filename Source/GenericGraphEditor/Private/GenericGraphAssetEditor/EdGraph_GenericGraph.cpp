#include "GenericGraphAssetEditor/EdGraph_GenericGraph.h"
#include "GenericGraphAssetEditor/GraphEditorEdEdgeNodeBase.h"
#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"
#include "GenericGraphEditorPCH.h"
#include "GraphDefinitionBase.h"

UEdGraph_GenericGraph::UEdGraph_GenericGraph() {}

UEdGraph_GenericGraph::~UEdGraph_GenericGraph() {}

void UEdGraph_GenericGraph::RebuildGenericGraph()
{
	LOG_INFO(TEXT("UGenericGraphEdGraph::RebuildGenericGraph has been called"));

	UGraphDefinitionBase* Graph = GetGenericGraph();

	Clear();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UGraphEditorEdNodeBase* EdNode = Cast<UGraphEditorEdNodeBase>(Nodes[i]))
		{
			if (EdNode->GenericGraphNode == nullptr)
			{
				continue;
			}

			UGraphNodeDefinitionBase* GenericGraphNode = EdNode->GenericGraphNode;

			NodeMap.Add(GenericGraphNode, EdNode);

			Graph->AllNodes.Add(GenericGraphNode);

			for (int PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
			{
				UEdGraphPin* Pin = EdNode->Pins[PinIdx];

				if (Pin->Direction != EGPD_Output)
				{
					continue;
				}

				for (int LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
				{
					UGraphNodeDefinitionBase* ChildNode = nullptr;
					if (UGraphEditorEdNodeBase* EdNode_Child = Cast<UGraphEditorEdNodeBase>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						ChildNode = EdNode_Child->GenericGraphNode;
					}
					else if (UGraphEditorEdEdgeNodeBase* EdNode_Edge = Cast<UGraphEditorEdEdgeNodeBase>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
					{
						UGraphEditorEdNodeBase* Child = EdNode_Edge->GetEndNode();
						if (Child != nullptr)
						{
							ChildNode = Child->GenericGraphNode;
						}
					}

					if (ChildNode != nullptr)
					{
						GenericGraphNode->ChildrenNodes.Add(ChildNode);

						ChildNode->ParentNodes.Add(GenericGraphNode);
					}
					else
					{
						LOG_ERROR(TEXT("UEdGraph_GenericGraph::RebuildGenericGraph can't "
									   "find child node"));
					}
				}
			}
		}
		else if (UGraphEditorEdEdgeNodeBase* EdgeNode = Cast<UGraphEditorEdEdgeNodeBase>(Nodes[i]))
		{
			UGraphEditorEdNodeBase* StartNode = EdgeNode->GetStartNode();
			UGraphEditorEdNodeBase* EndNode = EdgeNode->GetEndNode();
			UGraphEdgeDefinitionBase* Edge = EdgeNode->GenericGraphEdge;

			if (StartNode == nullptr || EndNode == nullptr || Edge == nullptr)
			{
				LOG_ERROR(TEXT("UEdGraph_GenericGraph::RebuildGenericGraph add edge failed."));
				continue;
			}

			EdgeMap.Add(Edge, EdgeNode);

			Edge->Graph = Graph;
			Edge->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
			Edge->StartNode = StartNode->GenericGraphNode;
			Edge->EndNode = EndNode->GenericGraphNode;
			Edge->StartNode->Edges.Add(Edge->EndNode, Edge);
		}
	}

	for (int i = 0; i < Graph->AllNodes.Num(); ++i)
	{
		UGraphNodeDefinitionBase* Node = Graph->AllNodes[i];
		if (Node->ParentNodes.Num() == 0)
		{
			Graph->RootNodes.Add(Node);

			SortNodes(Node);
		}

		Node->Graph = Graph;
		Node->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
	}

	Graph->RootNodes.Sort(
		[&](const UGraphNodeDefinitionBase& L, const UGraphNodeDefinitionBase& R)
		{
			UGraphEditorEdNodeBase* EdNode_LNode = NodeMap[&L];
			UGraphEditorEdNodeBase* EdNode_RNode = NodeMap[&R];
			return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
		});
}

UGraphDefinitionBase* UEdGraph_GenericGraph::GetGenericGraph() const
{
	return CastChecked<UGraphDefinitionBase>(GetOuter());
}

bool UEdGraph_GenericGraph::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	bool Rtn = Super::Modify(bAlwaysMarkDirty);

	GetGenericGraph()->Modify();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	return Rtn;
}

void UEdGraph_GenericGraph::Clear()
{
	UGraphDefinitionBase* Graph = GetGenericGraph();

	Graph->ClearGraph();
	NodeMap.Reset();
	EdgeMap.Reset();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UGraphEditorEdNodeBase* EdNode = Cast<UGraphEditorEdNodeBase>(Nodes[i]))
		{
			UGraphNodeDefinitionBase* GenericGraphNode = EdNode->GenericGraphNode;
			if (GenericGraphNode)
			{
				GenericGraphNode->ParentNodes.Reset();
				GenericGraphNode->ChildrenNodes.Reset();
				GenericGraphNode->Edges.Reset();
			}
		}
	}
}

void UEdGraph_GenericGraph::SortNodes(UGraphNodeDefinitionBase* RootNode)
{
	int Level = 0;
	TArray<UGraphNodeDefinitionBase*> CurrLevelNodes = {RootNode};
	TArray<UGraphNodeDefinitionBase*> NextLevelNodes;
	TSet<UGraphNodeDefinitionBase*> Visited;

	while (CurrLevelNodes.Num() != 0)
	{
		int32 LevelWidth = 0;
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UGraphNodeDefinitionBase* Node = CurrLevelNodes[i];
			Visited.Add(Node);

			auto Comp = [&](const UGraphNodeDefinitionBase& L, const UGraphNodeDefinitionBase& R)
			{
				UGraphEditorEdNodeBase* EdNode_LNode = NodeMap[&L];
				UGraphEditorEdNodeBase* EdNode_RNode = NodeMap[&R];
				return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
			};

			Node->ChildrenNodes.Sort(Comp);
			Node->ParentNodes.Sort(Comp);

			for (int j = 0; j < Node->ChildrenNodes.Num(); ++j)
			{
				UGraphNodeDefinitionBase* ChildNode = Node->ChildrenNodes[j];
				if (!Visited.Contains(ChildNode))
				{
					NextLevelNodes.Add(Node->ChildrenNodes[j]);
				}
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}

void UEdGraph_GenericGraph::PostEditUndo()
{
	Super::PostEditUndo();

	NotifyGraphChanged();
}
