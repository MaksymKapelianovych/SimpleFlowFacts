// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactTypes.h"
#include "FlowNode_FactBase.h"
#include "FlowNode_FactCondition.generated.h"

/**
 * Node for checking fact conditions.
 * After merging https://github.com/MothCocoon/FlowGraph/pull/202 this node will be refactored.
 */
UCLASS(meta = (DisplayName = "Fact Condition"), HideCategories=("Fact"))
class SIMPLEFLOWFACTS_API UFlowNode_FactCondition : public UFlowNode
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void ExecuteInput(const FName& PinName) override;
	
#if WITH_EDITOR
	virtual EDataValidationResult ValidateNode() override;
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere)
	FFactCondition Condition;
};
