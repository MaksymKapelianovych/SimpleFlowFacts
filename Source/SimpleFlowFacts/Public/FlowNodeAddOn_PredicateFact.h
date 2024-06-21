// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <AddOns/FlowNodeAddOn.h>

#include "CoreMinimal.h"
#include "FactTypes.h"
#include "Interfaces/FlowPredicateInterface.h"
#include "Nodes/FlowNode.h"
#include "FlowNodeAddOn_PredicateFact.generated.h"


UCLASS(MinimalApi, NotBlueprintable, meta = (DisplayName = "Fact Predicate"))
class UFlowNodeAddOn_PredicateFact : public UFlowNodeAddOn, public IFlowPredicateInterface
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool EvaluatePredicate_Implementation() const override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Fact", meta = (ShowOnlyInnerProperties))
	FSimpleFactCondition Condition;
};

/**
 * Node for checking fact conditions.
 * After merging https://github.com/MothCocoon/FlowGraph/pull/202 this node will be refactored.
 */
UCLASS( meta = ( DisplayName = "Fact Condition (DEPRECATED)", Tooltip = "This node is deprecated and will be removed soon, please, use AddOn predicate" ) )
class SIMPLEFLOWFACTS_API UFlowNode_FactCondition : public UFlowNode
{
	GENERATED_UCLASS_BODY()
protected:
	virtual void ExecuteInput( const FName& PinName ) override;
	
#if WITH_EDITOR
	virtual EDataValidationResult ValidateNode() override;
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Fact", meta = (ShowOnlyInnerProperties))
	FFactCondition Condition;
};
