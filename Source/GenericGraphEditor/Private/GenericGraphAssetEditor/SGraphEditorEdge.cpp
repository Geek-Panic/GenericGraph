#include "EdGraphSchema_K2.h"
#include "GenericGraphAssetEditor/ConnectionDrawingPolicy_GenericGraph.h"
#include "GenericGraphAssetEditor/GraphEditorEdEdgeNodeBase.h"
#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"
#include "GenericGraphAssetEditor/SGraphEditorEdge.h"
#include "GraphEdgeDefinitionBase.h"
#include "SGraphPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SToolTip.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

#define LOCTEXT_NAMESPACE "SGenericGraphEdge"

void SGraphEditorEdge::Construct(const FArguments& InArgs, UGraphEditorEdEdgeNodeBase* InNode)
{
	this->GraphNode = InNode;
	this->UpdateGraphNode();
}

bool SGraphEditorEdge::RequiresSecondPassLayout() const
{
	return true;
}

void SGraphEditorEdge::PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& NodeToWidgetLookup) const
{
	UGraphEditorEdEdgeNodeBase* EdgeNode = CastChecked<UGraphEditorEdEdgeNodeBase>(GraphNode);

	FGeometry StartGeom;
	FGeometry EndGeom;

	UGraphEditorEdNodeBase* Start = EdgeNode->GetStartNode();
	UGraphEditorEdNodeBase* End = EdgeNode->GetEndNode();
	if (Start != nullptr && End != nullptr)
	{
		const TSharedRef<SNode>* pFromWidget = NodeToWidgetLookup.Find(Start);
		const TSharedRef<SNode>* pToWidget = NodeToWidgetLookup.Find(End);
		if (pFromWidget != nullptr && pToWidget != nullptr)
		{
			const TSharedRef<SNode>& FromWidget = *pFromWidget;
			const TSharedRef<SNode>& ToWidget = *pToWidget;

			StartGeom = FGeometry(FVector2D(Start->NodePosX, Start->NodePosY), FVector2D::ZeroVector, FromWidget->GetDesiredSize(), 1.0f);
			EndGeom = FGeometry(FVector2D(End->NodePosX, End->NodePosY), FVector2D::ZeroVector, ToWidget->GetDesiredSize(), 1.0f);
		}
	}

	PositionBetweenTwoNodesWithOffset(StartGeom, EndGeom, 0, 1);
}

void SGraphEditorEdge::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
	SGraphNode::OnNameTextCommited(InText, CommitInfo);

	UGraphEditorEdEdgeNodeBase* MyNode = CastChecked<UGraphEditorEdEdgeNodeBase>(GraphNode);

	if (MyNode != nullptr && MyNode->GenericGraphEdge != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("GenericGraphEditorRenameEdge", "Generic Graph Editor: Rename Edge"));
		MyNode->Modify();
		MyNode->GenericGraphEdge->SetDisplayName(InText);
		UpdateGraphNode();
	}
}

void SGraphEditorEdge::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
			[SNew(SOverlay) + SOverlay::Slot()[SNew(SImage).Image(FAppStyle::GetBrush("Graph.TransitionNode.ColorSpill")).ColorAndOpacity(this, &SGraphEditorEdge::GetEdgeColor)]
			 + SOverlay::Slot()[SNew(SImage).Image(this, &SGraphEditorEdge::GetEdgeImage).Visibility(this, &SGraphEditorEdge::GetEdgeImageVisibility)]

			 + SOverlay::Slot().Padding(FMargin(4.0f, 4.0f, 4.0f, 4.0f))
				   [SNew(SVerticalBox)
					+ SVerticalBox::Slot()
						  .HAlign(HAlign_Center)
						  .AutoHeight()[SAssignNew(InlineEditableText, SInlineEditableTextBlock)
											.ColorAndOpacity(FLinearColor::Black)
											.Visibility(this, &SGraphEditorEdge::GetEdgeTitleVisbility)
											.Font(FCoreStyle::GetDefaultFontStyle("Regular", 12))
											.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
											.OnTextCommitted(this, &SGraphEditorEdge::OnNameTextCommited)]
					+ SVerticalBox::Slot().AutoHeight()[NodeTitle.ToSharedRef()]

	]];
}

void SGraphEditorEdge::PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const
{
	// Get a reasonable seed point (halfway between the boxes)
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

	// Find the (approximate) closest points between the two boxes
	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);

	// Position ourselves halfway along the connecting line between the
	// nodes, elevated away perpendicular to the direction of the line
	constexpr float Height = 30.0f;

	const FVector2D DesiredNodeSize = GetDesiredSize();

	FVector2D DeltaPos(EndAnchorPoint - StartAnchorPoint);

	if (DeltaPos.IsNearlyZero())
	{
		DeltaPos = FVector2D(10.0f, 0.0f);
	}

	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

	const FVector2D NewCenter = StartAnchorPoint + (0.5f * DeltaPos) + (Height * Normal);

	FVector2D DeltaNormal = DeltaPos.GetSafeNormal();

	// Calculate node offset in the case of multiple transitions between the same two nodes MultiNodeOffset: the offset where 0 is the centre of the transition, -1 is 1 <size of node> towards the PrevStateNode and +1 is
	// 1 <size of node> towards the NextStateNode.

	constexpr float MutliNodeSpace = 0.2f;					// Space between multiple transition nodes (in units of <size of node> )
	constexpr float MultiNodeStep = (1.f + MutliNodeSpace); // Step between node centres (Size of node + size of node spacer)

	const float MultiNodeStart = -((MaxNodes - 1) * MultiNodeStep) / 2.f;
	const float MultiNodeOffset = MultiNodeStart + (NodeIndex * MultiNodeStep);

	// Now we need to adjust the new center by the node size, zoom factor and multi node offset
	const FVector2D NewCorner = NewCenter - (0.5f * DesiredNodeSize) + (DeltaNormal * MultiNodeOffset * DesiredNodeSize.Size());

	GraphNode->NodePosX = NewCorner.X;
	GraphNode->NodePosY = NewCorner.Y;
}

FSlateColor SGraphEditorEdge::GetEdgeColor() const
{
	UGraphEditorEdEdgeNodeBase* EdgeNode = CastChecked<UGraphEditorEdEdgeNodeBase>(GraphNode);
	if (EdgeNode != nullptr && EdgeNode->GenericGraphEdge != nullptr)
	{
		return EdgeNode->GenericGraphEdge->GetEdgeColour();
	}
	return FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
}

const FSlateBrush* SGraphEditorEdge::GetEdgeImage() const
{
	return FAppStyle::GetBrush("Graph.TransitionNode.Icon");
}

EVisibility SGraphEditorEdge::GetEdgeImageVisibility() const
{
	UGraphEditorEdEdgeNodeBase* EdgeNode = CastChecked<UGraphEditorEdEdgeNodeBase>(GraphNode);
	if (EdgeNode && EdgeNode->GenericGraphEdge && EdgeNode->GenericGraphEdge->bShouldDrawDisplayName)
	{
		return EVisibility::Hidden;
	}

	return EVisibility::Visible;
}

EVisibility SGraphEditorEdge::GetEdgeTitleVisbility() const
{
	UGraphEditorEdEdgeNodeBase* EdgeNode = CastChecked<UGraphEditorEdEdgeNodeBase>(GraphNode);
	if (EdgeNode && EdgeNode->GenericGraphEdge && EdgeNode->GenericGraphEdge->bShouldDrawDisplayName)
	{
		return EVisibility::Visible;
	}

	return EVisibility::Collapsed;
}

#undef LOCTEXT_NAMESPACE
