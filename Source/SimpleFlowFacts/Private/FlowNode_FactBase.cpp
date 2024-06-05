// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNode_FactBase.h"

#include "FactTypes.h"

UFlowNode_FactBase::UFlowNode_FactBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	NodeStyle = EFlowNodeStyle::Custom;
	NodeColor = FLinearColor{ 0.275f, 1.f, .8f };
	Category = TEXT( "Fact" );
#endif
}

#if WITH_EDITOR
EDataValidationResult UFlowNode_FactBase::ValidateNode()
{
	if ( Tag.IsValid() == false )
	{
		ValidationLog.Error<UFlowNode>( TEXT( "Missing Tag" ), this );
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}

#endif
