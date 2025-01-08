// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#include "FlowNode_FactBase.h"

#include "FactTypes.h"

UE_DEFINE_GAMEPLAY_TAG( FlowNodeStyle::Fact, "Flow.NodeStyle.Node.Fact" );

UFlowNode_FactBase::UFlowNode_FactBase( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
#if WITH_EDITOR
	NodeDisplayStyle = FlowNodeStyle::Fact;
	Category = TEXT( "Fact" );
#endif
}

#if WITH_EDITOR
EDataValidationResult UFlowNode_FactBase::ValidateNode()
{
	if ( Tag.IsValid() == false )
	{
		ValidationLog.Error< UFlowNode >( TEXT( "Missing Tag" ), this );
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}

#endif
