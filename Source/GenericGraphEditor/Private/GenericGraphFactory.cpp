#include "GenericGraphFactory.h"
#include "GenericGraphDefinition.h"

#include "ClassFilter/AssetParentClassFilter.h"
#include "ClassViewerModule.h"
#include "Kismet2/SClassPickerDialog.h"

#define LOCTEXT_NAMESPACE "GenericGraphFactory"


UGenericGraphFactory::UGenericGraphFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UGenericGraphDefinition::StaticClass();
}

UGenericGraphFactory::~UGenericGraphFactory() {}

bool UGenericGraphFactory::ConfigureProperties()
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
	Filter->AllowedChildrenOfClasses.Add(UGenericGraphDefinition::StaticClass());

	const FText TitleText = LOCTEXT("CreateGenericGraphAssetOptions", "Pick Generic Graph Class");
	UClass* ChosenClass = nullptr;

	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UGenericGraphDefinition::StaticClass());

	if (bPressedOk)
	{
		GenericGraphClass = ChosenClass;
	}

	return bPressedOk;
}

UObject* UGenericGraphFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	if (GenericGraphClass != nullptr)
	{
		return NewObject<UGenericGraphDefinition>(InParent, GenericGraphClass, Name, Flags | RF_Transactional);
	}
	check(Class->IsChildOf(UGenericGraphDefinition::StaticClass()));
	
	return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
}

#undef LOCTEXT_NAMESPACE
