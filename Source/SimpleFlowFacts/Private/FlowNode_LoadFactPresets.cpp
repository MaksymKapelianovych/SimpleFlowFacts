// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.

#include "FlowNode_LoadFactPresets.h"

#include "FactPreset.h"
#include "FactStatics.h"

UFlowNode_LoadFactPresets::UFlowNode_LoadFactPresets( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
#if WITH_EDITOR
	NodeDisplayStyle = FlowNodeStyle::Fact;
	Category = TEXT( "Fact" );
#endif
	
	InputPins = { FFlowPin( TEXT( "In" ) ) };
	OutputPins = { FFlowPin( TEXT( "Out" ) ) };
}

void UFlowNode_LoadFactPresets::ExecuteInput( const FName& PinName )
{
	if ( UWorld* World = GetWorld() )
	{
		UFactStatics::LoadFactPresets( World, Presets );
		TriggerFirstOutput( true );
	}
	else
	{
		LogError( TEXT( "No valid world" ) );
	}
}

#if WITH_EDITOR
FString UFlowNode_LoadFactPresets::GetNodeDescription() const
{
	FTextBuilder Builder;

	for ( const UFactPreset* Preset : Presets )
	{
		Builder.AppendLine( Preset ? Preset->GetName() : "None" );
	}
		
	return Builder.ToText().ToString();
}

EDataValidationResult UFlowNode_LoadFactPresets::ValidateNode()
{
	EDataValidationResult ValidationResult = Super::ValidateNode();

	for ( const UFactPreset* Preset : Presets )
	{
		if ( Preset == nullptr )
		{
			ValidationLog.Warning( TEXT( "Some preset is not set" ), this );
			ValidationResult = EDataValidationResult::Invalid;
			break;
		}
	}

	return ValidationResult;
}
#endif