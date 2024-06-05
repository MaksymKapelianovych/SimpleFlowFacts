// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNode_ChangeFactValue.h"

#include "FactSubsystem.h"
#include "FactTypes.h"
#include "FlowSettings.h"

UFlowNode_ChangeFactValue::UFlowNode_ChangeFactValue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	NodeStyle = EFlowNodeStyle::Custom;
	Category = TEXT( "Fact" );
#endif

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
	if (UFlowSettings::Get()->bUseAdaptiveNodeTitles)
	{
		return Super::GetNodeDescription();
	}

	FStringFormatOrderedArguments Args;
	Args.Add(  Tag.ToString()  );
	
	Args.Add( UEnum::GetDisplayValueAsText( ChangeType ).ToString() );
	Args.Add( Value );
		
	return FString::Format( TEXT("{0}: {1} {2}"), Args );
}
#endif