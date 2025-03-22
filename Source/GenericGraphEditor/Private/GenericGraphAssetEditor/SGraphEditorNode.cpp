#include "GenericGraphAssetEditor/Colors_GenericGraph.h"
#include "GenericGraphAssetEditor/GenericGraphDragConnection.h"
#include "GenericGraphAssetEditor/GraphEditorEdNodeBase.h"
#include "GenericGraphAssetEditor/SGraphEditorNode.h"
#include "GenericGraphEditorPCH.h"
#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "SGraphPin.h"
#include "SlateOptMacros.h"
#include "SLevelOfDetailBranchNode.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

#define LOCTEXT_NAMESPACE "EdNode_GenericGraph"

//////////////////////////////////////////////////////////////////////////
class SGenericGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGenericGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		this->SetCursor(EMouseCursor::Default);

		bShowLabel = true;

		GraphPinObj = InPin;
		check(GraphPinObj != nullptr);

		const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
		check(Schema);

		SBorder::Construct(SBorder::FArguments()
							   .BorderImage(this, &SGenericGraphPin::GetPinBorder)
							   .BorderBackgroundColor(this, &SGenericGraphPin::GetPinColor)
							   .OnMouseButtonDown(this, &SGenericGraphPin::OnPinMouseDown)
							   .Cursor(this, &SGenericGraphPin::GetPinCursor)
							   .Padding(FMargin(5.0f)));
	}

protected:
	virtual FSlateColor GetPinColor() const override { return GenericGraphColors::Pin::Default; }

	virtual TSharedRef<SWidget> GetDefaultValueWidget() override { return SNew(STextBlock); }

	const FSlateBrush* GetPinBorder() const { return FAppStyle::GetBrush(TEXT("Graph.StateNode.Body")); }

	virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<class SGraphPanel>& InGraphPanel, const TArray<TSharedRef<SGraphPin>>& InStartingPins) override
	{
		FGenericGraphDragConnection::FDraggedPinTable PinHandles;
		PinHandles.Reserve(InStartingPins.Num());
		// since the graph can be refreshed and pins can be reconstructed/replaced
		// behind the scenes, the DragDropOperation holds onto FGraphPinHandles
		// instead of direct widgets/graph-pins
		for (const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
		{
			PinHandles.Add(PinWidget->GetPinObj());
		}

		return FGenericGraphDragConnection::New(InGraphPanel, PinHandles);
	}
};

//////////////////////////////////////////////////////////////////////////
void SGraphEditorNode::Construct(const FArguments& InArgs, UGraphEditorEdNodeBase* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	InNode->SEdNode = this;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGraphEditorNode::UpdateGraphNode()
{
	const FMargin NodePadding = FMargin(5);
	const FMargin NamePadding = FMargin(2);

	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an
	// already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FSlateBrush* NodeTypeIcon = GetNameIcon();

	FLinearColor TitleShadowColor(0.6f, 0.6f, 0.6f);
	TSharedPtr<SErrorText> ErrorText;
	TSharedPtr<SVerticalBox> NodeBody;
	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)[SNew(SBorder)
								   .BorderImage(FAppStyle::GetBrush("Graph.StateNode.Body"))
								   .Padding(0.0f)
								   .BorderBackgroundColor(this, &SGraphEditorNode::GetBorderBackgroundColor)
									   [SNew(SOverlay)

										+ SOverlay::Slot()
											  .HAlign(HAlign_Fill)
											  .VAlign(VAlign_Fill)
												  [SNew(SVerticalBox)

												   // Input Pin Area
												   + SVerticalBox::Slot().FillHeight(1)[SAssignNew(LeftNodeBox, SVerticalBox)]

												   // Output Pin Area
												   + SVerticalBox::Slot().FillHeight(1)[SAssignNew(RightNodeBox, SVerticalBox)]]

										+ SOverlay::Slot()
											  .HAlign(HAlign_Center)
											  .VAlign(VAlign_Center)
											  .Padding(8.0f)[SNew(SBorder)
																 .BorderImage(FAppStyle::GetBrush("Graph.StateNode.ColorSpill"))
																 .BorderBackgroundColor(TitleShadowColor)
																 .HAlign(HAlign_Center)
																 .VAlign(VAlign_Center)
																 .Visibility(EVisibility::SelfHitTestInvisible)
																 .Padding(6.0f)
																	 [SAssignNew(NodeBody, SVerticalBox)

																	  // Title
																	  + SVerticalBox::Slot().AutoHeight()
																			[SNew(SHorizontalBox)

																			 // Error message
																			 + SHorizontalBox::Slot().AutoWidth()[SAssignNew(ErrorText, SErrorText)
																													  .BackgroundColor(this, &SGraphEditorNode::GetErrorColor)
																													  .ToolTipText(this, &SGraphEditorNode::GetErrorMsgToolTip)]

																			 // Icon
																			 + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[SNew(SImage).Image(NodeTypeIcon)]

																			 // Node Title
																			 + SHorizontalBox::Slot().Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
																				   [SNew(SVerticalBox)
																					+ SVerticalBox::Slot().AutoHeight()[SAssignNew(InlineEditableText, SInlineEditableTextBlock)
																															.Style(
																																FAppStyle::Get(),
																																"Graph.StateNode."
																																"NodeTitleInlineEd"
																																"itableText")
																															.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
																															.OnVerifyTextChanged(this, &SGraphEditorNode::OnVerifyNameTextChanged)
																															.OnTextCommitted(this, &SGraphEditorNode::OnNameTextCommited)
																															.IsReadOnly(this, &SGraphEditorNode::IsNameReadOnly)
																															.IsSelected(this, &SGraphEditorNode::IsSelectedExclusively)]
																					+ SVerticalBox::Slot().AutoHeight()[NodeTitle.ToSharedRef()]]]]]]];

	// Create comment bubble
	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)[CommentBubble.ToSharedRef()];

	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);
	CreatePinWidgets();
}

void SGraphEditorNode::CreatePinWidgets()
{
	UGraphEditorEdNodeBase* StateNode = CastChecked<UGraphEditorEdNodeBase>(GraphNode);

	for (int32 PinIdx = 0; PinIdx < StateNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = StateNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SGenericGraphPin, MyPin);

			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SGraphEditorNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}

	TSharedPtr<SVerticalBox> PinBox;
	if (PinToAdd->GetDirection() == EGPD_Input)
	{
		PinBox = LeftNodeBox;
		InputPins.Add(PinToAdd);
	}
	else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		PinBox = RightNodeBox;
		OutputPins.Add(PinToAdd);
	}

	if (PinBox)
	{
		PinBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
				//.Padding(6.0f, 0.0f)
				[PinToAdd];
	}
}

bool SGraphEditorNode::IsNameReadOnly() const
{
	UGraphEditorEdNodeBase* EdNode_Node = Cast<UGraphEditorEdNodeBase>(GraphNode);
	check(EdNode_Node != nullptr);

	UGraphDefinitionBase* GenericGraph = EdNode_Node->GenericGraphNode->Graph;
	check(GenericGraph != nullptr);

	return (!GenericGraph->bCanRenameNode || !EdNode_Node->GenericGraphNode->IsNameEditable()) || SGraphNode::IsNameReadOnly();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SGraphEditorNode::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
	SGraphNode::OnNameTextCommited(InText, CommitInfo);

	UGraphEditorEdNodeBase* MyNode = CastChecked<UGraphEditorEdNodeBase>(GraphNode);

	if (MyNode != nullptr && MyNode->GenericGraphNode != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("GenericGraphEditorRenameNode", "Generic Graph Editor: Rename Node"));
		MyNode->Modify();
		MyNode->GenericGraphNode->Modify();
		MyNode->GenericGraphNode->SetDisplayName(InText);
		UpdateGraphNode();
	}
}

FSlateColor SGraphEditorNode::GetBorderBackgroundColor() const
{
	UGraphEditorEdNodeBase* MyNode = CastChecked<UGraphEditorEdNodeBase>(GraphNode);
	return MyNode ? MyNode->GetBackgroundColor() : GenericGraphColors::NodeBorder::HighlightAbortRange0;
}

FSlateColor SGraphEditorNode::GetBackgroundColor() const
{
	return GenericGraphColors::NodeBody::Default;
}

EVisibility SGraphEditorNode::GetDragOverMarkerVisibility() const
{
	return EVisibility::Visible;
}

const FSlateBrush* SGraphEditorNode::GetNameIcon() const
{
	return FAppStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
}

#undef LOCTEXT_NAMESPACE
