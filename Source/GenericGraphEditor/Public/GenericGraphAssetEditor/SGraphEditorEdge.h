#pragma once
#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "SNodePanel.h"
#include "Styling/SlateColor.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"

class SToolTip;
class UGraphEditorEdEdgeNodeBase;

class GENERICGRAPHEDITOR_API SGraphEditorEdge : public SGraphNode
{
	TSharedPtr<STextEntryPopup> TextEntryWidget;

protected:
	EVisibility GetEdgeImageVisibility() const;
	EVisibility GetEdgeTitleVisibility() const;

	FSlateColor        GetEdgeColor() const;
	const FSlateBrush* GetEdgeImage() const;
	
public:
	SLATE_BEGIN_ARGS(SGraphEditorEdge) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UGraphEditorEdEdgeNodeBase* InNode);

	// SGraphNode
	virtual bool RequiresSecondPassLayout() const override;
	virtual void PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& NodeToWidgetLookup) const override;
	virtual void UpdateGraphNode() override;
	// ~SGraphNode
	
	void PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const;
	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);
};
