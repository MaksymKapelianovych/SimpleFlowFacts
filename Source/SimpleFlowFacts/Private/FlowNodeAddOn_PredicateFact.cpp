// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNodeAddOn_PredicateFact.h"

#include "FactSubsystem.h"
#include "FactTypes.h"

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
		LogErrorConst( TEXT( "No valid world" ) );
		return false;
	}
}

#if WITH_EDITOR
FText UFlowNodeAddOn_PredicateFact::GetNodeTitle() const
{
	return Condition.IsValid() ? FText::FromString( Condition.ToString() ) : FText::FromString( "Fact is not set" );
}
#endif

UFlowNode_FactCondition::UFlowNode_FactCondition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	NodeStyle = EFlowNodeStyle::Custom;
	NodeColor = FLinearColor{ 0.275f, 1.f, .8f };
	Category = TEXT( "Fact" );
#endif
	
	InputPins = { FFlowPin( TEXT( "In" ) ) };
	OutputPins = { FFlowPin( TEXT( "True" ) ), FFlowPin( TEXT( "False" ) ) };
}

void UFlowNode_FactCondition::ExecuteInput(const FName& PinName)
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& Subsystem = UFactSubsystem::Get( World );
		TriggerOutput( Subsystem.CheckFactCondition( Condition ) ? TEXT( "True" ) : TEXT( "False" ), true );
	}
	else
	{
		LogError( TEXT( "No valid world" ) );
		// Is it okay to trigger output in error case?
		TriggerOutput( TEXT( "False" ), true );
	}
}

#if WITH_EDITOR
EDataValidationResult UFlowNode_FactCondition::ValidateNode()
{
	return Condition.IsValid() ? EDataValidationResult::Valid : EDataValidationResult::Invalid;
}

FString UFlowNode_FactCondition::GetNodeDescription() const
{
	FString Description = Condition.ToString();
	return Description.IsEmpty() ? "None" : Description;
}
#endif