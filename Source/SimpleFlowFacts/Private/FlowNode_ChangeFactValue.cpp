// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#include "FlowNode_ChangeFactValue.h"

#include "FactSubsystem.h"
#include "FactTypes.h"

UFlowNode_ChangeFactValue::UFlowNode_ChangeFactValue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InputPins = { FFlowPin( TEXT( "In" ) ) };
	OutputPins = { FFlowPin( TEXT( "Out" ) ) };
}

void UFlowNode_ChangeFactValue::ExecuteInput(const FName& PinName)
{
	if ( UWorld* World = GetWorld() )
	{
		UFactSubsystem& Subsystem = UFactSubsystem::Get( World );
		Subsystem.ChangeFactValue( Tag, Value, ChangeType );
	}
	else
	{
		LogError( TEXT( "No valid world" ) );
	}

	// Is it okay to trigger output in error case?
	TriggerFirstOutput( true );
}

#if WITH_EDITOR
FString UFlowNode_ChangeFactValue::GetNodeDescription() const
{
	if ( Tag.IsValid() == false )
	{
		return "None";
	}
	
	FStringFormatOrderedArguments Args;
	Args.Add(  Tag.ToString()  );
	
	Args.Add( UEnum::GetDisplayValueAsText( ChangeType ).ToString() );
	Args.Add( Value );
		
	return FString::Format( TEXT( "{0}: {1} {2}" ), Args );
}
#endif