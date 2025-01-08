// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#pragma once

#include "CoreMinimal.h"
#include "FlowNode_FactBase.h"
#include "FactTypes.h"
#include "FlowNode_ListenForFactChanges.generated.h"


/**
 *  Node that executes every time fact value changes.
 *	ValueChanged pin executes every time value of the fact changes.
 *		If it is first change and fact became defined by this change, BecameDefined will be triggered first
 *	BecameDefined pin executes when fact's state transitions from undefined to defined
 */
UCLASS(meta = (DisplayName = "Listen For Fact Changes (DEPRECATED)", Tooltip = "This node is deprecated and will be removed soon, please, use On Fact Changed or On Fact Defined instead"))
class SIMPLEFLOWFACTS_API UFlowNode_ListenForFactChanges : public UFlowNode_FactBase
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void OnLoad_Implementation() override;
	virtual void Cleanup() override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
	virtual FString GetNodeDescription() const override;
#endif

private:
	void SubscribeDelegates();
	void UnsubscribeDelegates() const;
	
	UFUNCTION()
	void HandleFactValueChanged(int32 CurrentValue);

	UFUNCTION()
	void HandleFactBecameDefined(int32 CurrentValue);
	
};
