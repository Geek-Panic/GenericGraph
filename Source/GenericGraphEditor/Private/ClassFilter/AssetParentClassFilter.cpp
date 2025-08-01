// Fill out your copyright notice in the Description page of Project Settings.
#include "ClassFilter/AssetParentClassFilter.h"
#include "Kismet2/KismetEditorUtilities.h"

bool FAssetClassParentFilter::IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs)
{
	const bool bAllowed = !InClass->HasAnyClassFlags(DisallowedClassFlags) && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;

	if (bAllowed && bDisallowBlueprintBase)
	{
		if (FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass))
		{
			return false;
		}
	}

	return bAllowed;
}

bool FAssetClassParentFilter::IsUnloadedClassAllowed(
	const FClassViewerInitializationOptions& InInitOptions,
	const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
	TSharedRef<FClassViewerFilterFuncs> InFilterFuncs)
{
	if (bDisallowBlueprintBase)
	{
		return false;
	}

	return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags) && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
}
