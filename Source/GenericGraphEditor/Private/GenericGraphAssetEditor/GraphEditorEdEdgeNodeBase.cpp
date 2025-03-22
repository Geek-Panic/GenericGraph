#include "GenericGraphAssetEditor/GraphEditorEdEdgeNodeBase.h"
#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"
#include "GraphEdgeDefinitionBase.h"

#define LOCTEXT_NAMESPACE "EdNode_GenericGraphEdge"

UGraphEditorEdEdgeNodeBase::UGraphEditorEdEdgeNodeBase()
{
	bCanRenameNode = true;
}

void UGraphEditorEdEdgeNodeBase::SetEdge(UGraphEdgeDefinitionBase* Edge)
{
	GenericGraphEdge = Edge;
}

void UGraphEditorEdEdgeNodeBase::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}

FText UGraphEditorEdEdgeNodeBase::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (GenericGraphEdge)
	{
		return GenericGraphEdge->GetDisplayName();
	}
	return FText();
}

void UGraphEditorEdEdgeNodeBase::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		// Commit suicide; transitions must always have an input and output
		// connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified
		// to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

void UGraphEditorEdEdgeNodeBase::PrepareForCopying()
{
	GenericGraphEdge->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
}

void UGraphEditorEdEdgeNodeBase::CreateConnections(UGraphEditorEdNodeBase* Start, UGraphEditorEdNodeBase* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}

UGraphEditorEdNodeBase* UGraphEditorEdEdgeNodeBase::GetStartNode()
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UGraphEditorEdNodeBase>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	return nullptr;
}

UGraphEditorEdNodeBase* UGraphEditorEdEdgeNodeBase::GetEndNode()
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UGraphEditorEdNodeBase>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	return nullptr;
}

#undef LOCTEXT_NAMESPACE
