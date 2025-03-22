#pragma once
#include <EdGraph/EdGraphNode.h>
#include <EdGraphUtilities.h>

class FGraphPanelNodeFactory_GenericGraph : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};