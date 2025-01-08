// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#include "FlowNode_OnFactDefined.h"

#include "FactSubsystem.h"

UFlowNode_OnFactDefined::UFlowNode_OnFactDefined( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
#if WITH_EDITOR
	NodeDisplayStyle = FlowNodeStyle::Condition;
#endif
}

void UFlowNode_OnFactDefined::ExecuteInput( const FName& PinName )
{
	if ( Tag.IsValid() )
	{
		if ( PinName == DefaultInputPin.PinName )
		{
			StartObserving();
		}
	}
	else
	{
		LogError( "No fact tag" );
	}
}

void UFlowNode_OnFactDefined::OnLoad_Implementation()
{
	if ( Tag.IsValid() )
	{
		StartObserving();
	}
}

void UFlowNode_OnFactDefined::StartObserving()
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& FactSubsystem = UFactSubsystem::Get( World );
		FactSubsystem.GetOnFactBecameDefinedDelegate( Tag ).AddUObject( this, &ThisClass::OnEventReceived );
	}
	else
	{
		LogError(TEXT("No valid world"));
		// What next?
	}
}

void UFlowNode_OnFactDefined::StopObserving()
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& FactSubsystem = UFactSubsystem::Get( World );
		FactSubsystem.GetOnFactBecameDefinedDelegate( Tag ).RemoveAll( this );
	}
}

void UFlowNode_OnFactDefined::OnEventReceived( int32 CurrentValue )
{
	TriggerFirstOutput( true );
}

void UFlowNode_OnFactDefined::Cleanup()
{
	StopObserving();
}

#if WITH_EDITOR
FString UFlowNode_OnFactDefined::GetNodeDescription() const
{
	return Tag.IsValid() ? Tag.ToString() : "None";
}
#endif
