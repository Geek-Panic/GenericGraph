#include "GraphEdgeDefinitionBase.h"

UGraphEdgeDefinitionBase::UGraphEdgeDefinitionBase() {}

UGraphEdgeDefinitionBase::~UGraphEdgeDefinitionBase() {}

UGraphDefinitionBase* UGraphEdgeDefinitionBase::GetGraph() const
{
	return Graph;
}

#if WITH_EDITOR
void UGraphEdgeDefinitionBase::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}
#endif // #if WITH_EDITOR