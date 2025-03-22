#include "GraphDefinitionBase.h"
#include "GraphDefinitionFactory.h"

#include "ClassFilter/AssetParentClassFilter.h"
#include "ClassViewerModule.h"
#include "Kismet2/SClassPickerDialog.h"

#define LOCTEXT_NAMESPACE "GenericGraphFactory"


UGraphDefinitionFactory::UGraphDefinitionFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UGraphDefinitionBase::StaticClass();
}

UGraphDefinitionFactory::~UGraphDefinitionFactory() {}

bool UGraphDefinitionFactory::ConfigureProperties()
{
	// nullptr the GenericGraphClass so we can check for selection
	GenericGraphClass = nullptr;

	// Load the ClassViewer module to display a class picker
	FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	const TSharedRef<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilters.Add(Filter);

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UGraphDefinitionBase::StaticClass());

	const FText TitleText = LOCTEXT("GraphEditor.ClassPickerTitle", "Pick Graph Definition Class");
	UClass* ChosenClass = nullptr;

	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UGraphDefinitionBase::StaticClass());

	if (bPressedOk)
	{
		GenericGraphClass = ChosenClass;
	}

	return bPressedOk;
}

UObject* UGraphDefinitionFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UGraphDefinitionBase::StaticClass()));
	
	if (GenericGraphClass != nullptr)
	{
		return NewObject<UGraphDefinitionBase>(InParent, GenericGraphClass, Name, Flags | RF_Transactional);
	}
	
	return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE
