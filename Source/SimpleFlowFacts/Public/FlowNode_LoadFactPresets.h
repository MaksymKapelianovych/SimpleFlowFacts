// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#pragma once

#include "CoreMinimal.h"
#include "FlowNode_FactBase.h"

#include "FlowNode_LoadFactPresets.generated.h"

class UFactPreset;
/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Load Fact Presets"))
class SIMPLEFLOWFACTS_API UFlowNode_LoadFactPresets : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput( const FName& PinName ) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual EDataValidationResult ValidateNode() override;
#endif
	
protected:
	UPROPERTY(EditAnywhere, Category = "Fact")
	TArray< TObjectPtr< UFactPreset > > Presets;
};
