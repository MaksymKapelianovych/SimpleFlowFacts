// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowNode_FactBase.h"
#include "FlowNode_ChangeFactValue.generated.h"

/**
 *  Change value of the fact (set or add)
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Change Fact"))
class SIMPLEFLOWFACTS_API UFlowNode_ChangeFactValue : public UFlowNode_FactBase
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif
	
protected:
	UPROPERTY(EditAnywhere, Category = "Fact")
	int32 Value = 0;
	
	UPROPERTY(EditAnywhere, Category = "Fact")
	EFactValueChangeType ChangeType = EFactValueChangeType::Set;
};
