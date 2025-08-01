#pragma once
#include "AssetTypeActions_Base.h"
#include "CoreMinimal.h"

class GENERICGRAPHEDITOR_API FAssetTypeActions_GenericGraph : public FAssetTypeActions_Base
{
	EAssetTypeCategories::Type AssetCategory;

public:
	explicit FAssetTypeActions_GenericGraph(EAssetTypeCategories::Type InAssetCategory);

	// FAssetTypeActions_Base
	virtual FText   GetName() const override;
	virtual FColor  GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32  GetCategories() override;
	virtual void    OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	// ~FAssetTypeActions_Base
};