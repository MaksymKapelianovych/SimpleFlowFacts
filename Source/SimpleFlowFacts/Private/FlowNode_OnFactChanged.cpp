// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#include "FlowNode_OnFactChanged.h"

#include "FactSubsystem.h"

UFlowNode_OnFactChanged::UFlowNode_OnFactChanged( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
	, WantedValue( 0 )
	, SuccessLimit( 1 )
	, SuccessCount( 0 )
{
#if WITH_EDITOR
	NodeDisplayStyle = FlowNodeStyle::Condition;
#endif

	InputPins = { FFlowPin( TEXT( "Start" ) ), FFlowPin( TEXT( "Stop" ) ) };
	OutputPins = { FFlowPin( TEXT( "Success" ) ), FFlowPin( TEXT( "Completed" ) ), FFlowPin( TEXT( "Stopped" ) ) };
}

void UFlowNode_OnFactChanged::ExecuteInput( const FName& PinName )
{
	if ( Tag.IsValid() )
	{
		if ( PinName == TEXT( "Start" ) )
		{
			StartObserving();
		}
		else if ( PinName == TEXT( "Stop" ) )
		{
			TriggerOutput( TEXT( "Stopped" ), true );
		}
	}
	else
	{
		LogError( "No fact tag" );
	}
}

void UFlowNode_OnFactChanged::OnLoad_Implementation()
{
	if ( Tag.IsValid() )
	{
		StartObserving();
	}
}

void UFlowNode_OnFactChanged::StartObserving()
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& FactSubsystem = UFactSubsystem::Get( World );
		FactSubsystem.GetOnFactValueChangedDelegate( Tag ).AddUObject( this, &ThisClass::OnEventReceived );
	}
	else
	{
		LogError(TEXT("No valid world"));
		// What next?
	}
}

void UFlowNode_OnFactChanged::StopObserving()
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& FactSubsystem = UFactSubsystem::Get( World );
		FactSubsystem.GetOnFactValueChangedDelegate( Tag ).RemoveAll( this );
	}
}

void UFlowNode_OnFactChanged::OnEventReceived( int32 CurrentValue )
{
	if ( bWaitForExactValue && CurrentValue != WantedValue )
	{
		return;
	}

	TriggerOutput( TEXT( "Success" ) );
	SuccessCount++;
	if ( SuccessLimit > 0 && SuccessCount == SuccessLimit )
	{
		TriggerOutput( TEXT( "Completed" ), true );
	}
}

void UFlowNode_OnFactChanged::Cleanup()
{
	StopObserving();
	SuccessCount = 0;
}

#if WITH_EDITOR
FString UFlowNode_OnFactChanged::GetNodeDescription() const
{
	FStringFormatOrderedArguments Args;
	Args.Add( Tag.IsValid() ? Tag.ToString() : "None" );
	Args.Add( bWaitForExactValue ? FString::FromInt( WantedValue ) : "Any" );
	
	return FString::Format( TEXT("{0}\nWanted value:{1}"), Args );
}
#endif
