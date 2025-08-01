#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class GENERICGRAPHEDITOR_API FGraphEditorStyle
{
	static TSharedPtr<FSlateStyleSet> StyleSet;

public:
	static void Initialize();
	static void Shutdown(); 
	static const FName& GetStyleSetName();
};
