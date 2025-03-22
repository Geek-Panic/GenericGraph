#include "GraphEdgeDefinitionBase.h"

UGraphEdgeDefinitionBase::UGraphEdgeDefinitionBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.Get())
{
	
}

UGraphEdgeDefinitionBase::~UGraphEdgeDefinitionBase() {}

UGraphDefinitionBase* UGraphEdgeDefinitionBase::GetGraph() const
{
	return Graph;
}

#if WITH_EDITOR
void UGraphEdgeDefinitionBase::SetNodeTitle(const FText& NewTitle)
{
	DisplayName = NewTitle;
}
#endif // #if WITH_EDITOR