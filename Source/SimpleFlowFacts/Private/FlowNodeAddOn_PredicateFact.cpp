// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNodeAddOn_PredicateFact.h"

#include "FactSubsystem.h"
#include "FactTypes.h"
#include "FlowSettings.h"

UFlowNodeAddOn_PredicateFact::UFlowNodeAddOn_PredicateFact( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
#if WITH_EDITOR
	NodeStyle = EFlowNodeStyle::Logic;
	Category = TEXT("Composite");
#endif
}

bool UFlowNodeAddOn_PredicateFact::EvaluatePredicate_Implementation() const
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& Subsystem = UFactSubsystem::Get( World );
		return Subsystem.CheckFactSimpleCondition( Condition );
	}
	else
	{
		LogError( TEXT( "No valid world" ) );
		return false;
	}
}

#if WITH_EDITOR
FText UFlowNodeAddOn_PredicateFact::GetNodeTitle() const
{
	if ( Condition.IsValid() && UFlowSettings::Get()->bUseAdaptiveNodeTitles )
	{
		return FText::FromString( Condition.ToString() );
	}
	
	return Super::GetNodeTitle();
}
#endif