// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "FactTypes.h"
#include "Interfaces/FlowPredicateInterface.h"
#include "AddOns/FlowNodeAddOn.h"
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
	FFactCondition Condition;
};
