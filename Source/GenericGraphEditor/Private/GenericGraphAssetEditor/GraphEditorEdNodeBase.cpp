#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"

#include "SGraphPin.h"
#include "GenericGraphAssetEditor/EdGraph_GenericGraph.h"
#include "GenericGraphAssetEditor/SGraphEditorNode.h"
#include "Kismet2/Kismet2NameValidators.h"

#define LOCTEXT_NAMESPACE "EdNode_GenericGraph"

UGraphEditorEdNodeBase::UGraphEditorEdNodeBase()
{
	bCanRenameNode = true;
}

void UGraphEditorEdNodeBase::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

UEdGraph_GenericGraph* UGraphEditorEdNodeBase::GetGenericGraphEdGraph()
{
	return Cast<UEdGraph_GenericGraph>(GetGraph());
}

FText UGraphEditorEdNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (GenericGraphNode == nullptr)
	{
		return Super::GetNodeTitle(TitleType);
	}
	return GenericGraphNode->GetDisplayName();
}

void UGraphEditorEdNodeBase::PrepareForCopying()
{
	GenericGraphNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

void UGraphEditorEdNodeBase::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

void UGraphEditorEdNodeBase::SetGenericGraphNode(UGraphNodeDefinitionBase* InNode)
{
	GenericGraphNode = InNode;
}

FLinearColor UGraphEditorEdNodeBase::GetBackgroundColor() const
{
	return GenericGraphNode == nullptr ? FLinearColor::Black : GenericGraphNode->GetBackgroundColor();
}

UEdGraphPin* UGraphEditorEdNodeBase::GetInputPin() const
{
	return Pins[0];
}

UEdGraphPin* UGraphEditorEdNodeBase::GetOutputPin() const
{
	return Pins[1];
}

TSharedPtr<SGraphNode> UGraphEditorEdNodeBase::GetNodeView()
{
	return SNew(SGraphEditorNode, this);
}

TSubclassOf<UGraphNodeDefinitionBase> UGraphEditorEdNodeBase::GetNodeClass()
{
	return UGraphNodeDefinitionBase::StaticClass();
}

#if WITH_EDITOR
void UGraphEditorEdNodeBase::PostEditUndo()
{
	UEdGraphNode::PostEditUndo();
}
#endif

#undef LOCTEXT_NAMESPACE
