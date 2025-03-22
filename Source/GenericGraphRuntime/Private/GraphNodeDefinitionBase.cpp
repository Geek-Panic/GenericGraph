#include "GraphDefinitionBase.h"
#include "GraphNodeDefinitionBase.h"

#define LOCTEXT_NAMESPACE "GenericGraphNode"

UGraphNodeDefinitionBase::UGraphNodeDefinitionBase()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UGraphDefinitionBase::StaticClass();

	BackgroundColor = FLinearColor::Black;
#endif
}

UGraphNodeDefinitionBase::~UGraphNodeDefinitionBase() {}

UGraphEdgeDefinitionBase* UGraphNodeDefinitionBase::GetEdge(UGraphNodeDefinitionBase* ChildNode)
{
	return Edges.Contains(ChildNode) ? Edges.FindChecked(ChildNode) : nullptr;
}

FText UGraphNodeDefinitionBase::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Generic Graph Node");
}

#if WITH_EDITOR
bool UGraphNodeDefinitionBase::IsNameEditable() const
{
	return true;
}

FLinearColor UGraphNodeDefinitionBase::GetBackgroundColor() const
{
	return BackgroundColor;
}

FText UGraphNodeDefinitionBase::GetNodeTitle() const
{
	return NodeTitle.IsEmpty() ? GetDescription() : NodeTitle;
}

void UGraphNodeDefinitionBase::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}

bool UGraphNodeDefinitionBase::CanCreateConnection(UGraphNodeDefinitionBase* Other, FText& ErrorMessage)
{
	return true;
}

bool UGraphNodeDefinitionBase::CanCreateConnectionTo(UGraphNodeDefinitionBase* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage)
{
	if (ChildrenLimitType == ENodeLimit::Limited && NumberOfChildrenNodes >= ChildrenLimit)
	{
		ErrorMessage = FText::FromString("Children limit exceeded");
		return false;
	}

	return CanCreateConnection(Other, ErrorMessage);
}

bool UGraphNodeDefinitionBase::CanCreateConnectionFrom(UGraphNodeDefinitionBase* Other, int32 NumberOfParentNodes, FText& ErrorMessage)
{
	if (ParentLimitType == ENodeLimit::Limited && NumberOfParentNodes >= ParentLimit)
	{
		ErrorMessage = FText::FromString("Parent limit exceeded");
		return false;
	}

	return true;
}

#endif

bool UGraphNodeDefinitionBase::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

UGraphDefinitionBase* UGraphNodeDefinitionBase::GetGraph() const
{
	return Graph;
}

#undef LOCTEXT_NAMESPACE
