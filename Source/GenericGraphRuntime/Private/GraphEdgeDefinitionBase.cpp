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
void UGraphEdgeDefinitionBase::SetDisplayName(const FText& InDisplayName)
{
	DisplayName = InDisplayName;
}
#endif // #if WITH_EDITOR