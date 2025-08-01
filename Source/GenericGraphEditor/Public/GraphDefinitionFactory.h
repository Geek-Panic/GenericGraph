#pragma once
#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "GraphDefinitionBase.h"
#include "GraphDefinitionFactory.generated.h"

UCLASS(MinimalAPI)
class UGraphDefinitionFactory : public UFactory
{
	GENERATED_BODY()

public:
	UGraphDefinitionFactory();
	virtual ~UGraphDefinitionFactory() override;
	
	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
	UPROPERTY(EditAnywhere, Category = "DataAsset")
	TSubclassOf<UGraphDefinitionBase> GenericGraphClass;
};
