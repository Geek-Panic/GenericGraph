#include "GenericGraphNodeFactory.h"
#include "GenericGraphAssetEditor/GraphEditorEdEdgeNodeBase.h"
#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"
#include "GenericGraphAssetEditor/SGraphEditorEdge.h"
#include "GenericGraphAssetEditor/SGraphEditorNode.h"
#include <EdGraph/EdGraphNode.h>

TSharedPtr<SGraphNode> FGraphEditorNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	// TODO : Add entry node
	
	if (UGraphEditorEdNodeBase* GraphNode = Cast<UGraphEditorEdNodeBase>(Node))
	{
		return SNew(SGraphEditorNode, GraphNode);
	}
	if (UGraphEditorEdEdgeNodeBase* GraphEdge = Cast<UGraphEditorEdEdgeNodeBase>(Node))
	{
		return SNew(SGraphEditorEdge, GraphEdge);
	}
	return nullptr;
}
