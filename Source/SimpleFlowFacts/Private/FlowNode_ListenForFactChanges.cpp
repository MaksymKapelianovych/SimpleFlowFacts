// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNode_ListenForFactChanges.h"

#include "FactSubsystem.h"
#include "FactTypes.h"
#include "FlowSettings.h"

#define LOCTEXT_NAMESPACE "FlowFacts"

UFlowNode_ListenForFactChanges::UFlowNode_ListenForFactChanges(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	NodeStyle = EFlowNodeStyle::Custom;
	Category = TEXT( "Fact" );
#endif

	InputPins = { FFlowPin( TEXT( "Start" ) ), FFlowPin( TEXT( "Stop" ) ) };
	OutputPins = { FFlowPin( TEXT( "ValueChanged" ) ), FFlowPin( TEXT( "BecameDefined" ) ) };
}

void UFlowNode_ListenForFactChanges::SubscribeDelegates()
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& FactSubsystem = UFactSubsystem::Get( World );
		FactSubsystem.GetOnFactValueChangedDelegate( Tag ).AddUObject( this, &ThisClass::HandleFactValueChanged );
		FactSubsystem.GetOnFactBecameDefinedDelegate( Tag ).AddUObject( this, &ThisClass::HandleFactBecameDefined );
	}
	else
	{
		LogError(TEXT("No valid world"));
		// What next?
	}
}

void UFlowNode_ListenForFactChanges::UnsubscribeDelegates() const
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& FactSubsystem = UFactSubsystem::Get( World );
		FactSubsystem.GetOnFactValueChangedDelegate( Tag ).RemoveAll( this );
		FactSubsystem.GetOnFactBecameDefinedDelegate( Tag ).RemoveAll( this );
	}
}

void UFlowNode_ListenForFactChanges::HandleFactValueChanged(int32 CurrentValue)
{
	TriggerOutput( TEXT( "ValueChanged" ) );
}

void UFlowNode_ListenForFactChanges::HandleFactBecameDefined(int32 CurrentValue)
{
	TriggerOutput( TEXT( "BecameDefined" ) );
}

void UFlowNode_ListenForFactChanges::ExecuteInput(const FName& PinName)
{
	if ( PinName == TEXT( "Start" ) )
	{
		SubscribeDelegates();
	}
	else if ( PinName == TEXT( "Stop" ) )
	{
		UnsubscribeDelegates();
	}
}

void UFlowNode_ListenForFactChanges::OnLoad_Implementation()
{
	SubscribeDelegates();
}

void UFlowNode_ListenForFactChanges::Cleanup()
{
	UnsubscribeDelegates();
}

#if WITH_EDITOR

FText UFlowNode_ListenForFactChanges::GetNodeTitle() const
{
	const bool bUseAdaptiveNodeTitles = UFlowSettings::Get()->bUseAdaptiveNodeTitles;

	if ( bUseAdaptiveNodeTitles && Tag.IsValid() )
	{
		FFormatOrderedArguments Args;
		Args.Add( FText::FromString( Tag.ToString() ) );
		return FText::Format( LOCTEXT( "ListenForFactChanges", "Listen {0}" ), Args );
	}

	return Super::GetNodeTitle();
}

FString UFlowNode_ListenForFactChanges::GetNodeDescription() const
{
	if ( UFlowSettings::Get()->bUseAdaptiveNodeTitles )
	{
		return Super::GetNodeDescription();
	}

	return Tag.ToString();
}

#endif

#undef LOCTEXT_NAMESPACE