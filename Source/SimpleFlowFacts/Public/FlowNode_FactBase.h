// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactTypes.h"
#include "NativeGameplayTags.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_FactBase.generated.h"

namespace FlowNodeStyle
{
	SIMPLEFLOWFACTS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Fact);
}

/**
 *  Base node for dealing with facts
 */
UCLASS(Abstract, NotBlueprintable, HideCategories=(Internal))
class SIMPLEFLOWFACTS_API UFlowNode_FactBase : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	
#if WITH_EDITOR
	virtual EDataValidationResult ValidateNode() override;
#endif
	
protected:
	UPROPERTY(EditAnywhere, Category = "Fact")
	FFactTag Tag;
};
