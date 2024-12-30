// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowNode_FactBase.h"
#include "FlowNode_OnFactDefined.generated.h"

/**
 * Triggers output when fact is defined (first time value is set).
 * Currently, fact can be defined only once, and stays defined till the end
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "On Fact Defined"))
class SIMPLEFLOWFACTS_API UFlowNode_OnFactDefined : public UFlowNode_FactBase
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput( const FName& PinName ) override;
	virtual void OnLoad_Implementation() override;

	virtual void StartObserving();
	virtual void StopObserving();

	void OnEventReceived( int32 CurrentValue );

	virtual void Cleanup() override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif
};
