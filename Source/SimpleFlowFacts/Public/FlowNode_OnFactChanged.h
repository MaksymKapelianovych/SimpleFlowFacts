// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlowNode_FactBase.h"
#include "FlowNode_OnFactChanged.generated.h"

/**
 * Triggers output when Flow Component with matching Identity Tag calls NotifyGraph function with matching Notify Tag
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "On Fact Changed"))
class SIMPLEFLOWFACTS_API UFlowNode_OnFactChanged : public UFlowNode_FactBase
{
	GENERATED_UCLASS_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Fact")
	bool bWaitForExactValue = true;
	
	UPROPERTY(EditAnywhere, Category = "Fact", meta = (EditCondition = bWaitForExactValue, EditConditionHides))
	int32 WantedValue;
	
	// This node will become Completed, if Success Limit > 0 and Success Count reaches this limit
	// Set this to zero, if you'd like receive events indefinitely (node would finish work only if explicitly Stopped)
	UPROPERTY(EditAnywhere, Category = "Lifetime", meta = (ClampMin = 0))
	int32 SuccessLimit;

	// This node will become Completed, if Success Limit > 0 and Success Count reaches this limit
	UPROPERTY(VisibleAnywhere, Category = "Lifetime", SaveGame)
	int32 SuccessCount;

protected:
	virtual void ExecuteInput( const FName& PinName ) override;
	virtual void OnLoad_Implementation() override;

	virtual void StartObserving();
	virtual void StopObserving();

	void OnEventReceived( int32 CurrentValue );

	virtual void Cleanup() override;

#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
#endif
};
