#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UGraphEditorEdNodeBase;

class GENERICGRAPHEDITOR_API SGraphEditorNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SGraphEditorNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UGraphEditorEdNodeBase* InNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual bool IsNameReadOnly() const override;

	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

	virtual FSlateColor GetBorderBackgroundColor() const;
	virtual FSlateColor GetBackgroundColor() const;

	virtual EVisibility GetDragOverMarkerVisibility() const;

	virtual const FSlateBrush* GetNameIcon() const;
};
