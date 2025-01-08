
// Copyright 2024, Maksym Kapelianovych. Licensed under MIT license.
#include "Modules/ModuleManager.h"

#if WITH_EDITOR
#include "FlowModule.h"
#include "FlowNode_FactBase.h"
#include "Graph/FlowGraphSettings.h"
#endif

class FSimpleFlowFactsModule : public IModuleInterface
{
	virtual void StartupModule() override
	{
#if WITH_EDITOR
		// Force the Flow module to be loaded before we try to access the Settings
		FModuleManager::LoadModuleChecked< FFlowModule >( "Flow" );

		UFlowGraphSettings& Settings = *UFlowGraphSettings::Get();
		(void) Settings.TryAddDefaultNodeDisplayStyle( FFlowNodeDisplayStyleConfig( FlowNodeStyle::Fact, FLinearColor{ 0.275f, 1.f, .8f } ) );
#endif
	}
};


IMPLEMENT_MODULE( FSimpleFlowFactsModule, SimpleFlowFacts )