#pragma once
#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FGraphEditorNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};