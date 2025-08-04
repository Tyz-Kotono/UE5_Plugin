#include "ExampleTCommands.h"

#define LOCTEXT_NAMESPACE "Example TCommands"

TSharedRef<FUICommandList> FExampleTCommands::CommandList = MakeShareable(new FUICommandList);

FExampleTCommands::FExampleTCommands()
	: TCommands<FExampleTCommands>
	(
		"FExample TCommands",
		NSLOCTEXT("Level", "Extend Editor Commands", "Example Pugin"),
		NAME_None,
		"TAStyle" //FXXXX::GetAppStyleSetName() // Icon
	)
{
}

void FExampleTCommands::RegisterCommands()
{
	UI_COMMAND(CommandLogLambda, "Example LOG", "Example ToolTip", EUserInterfaceActionType::Button, FInputChord());

	CommandList->MapAction(CommandLogLambda, FExecuteAction::CreateLambda([]
	{
		UE_LOG(LogTemp, Display, TEXT("Example Lambda"));
	}));
	UI_COMMAND(CommandLogFunction, "Example Function", "Example Function ToolTip", EUserInterfaceActionType::Button, FInputChord());
	CommandList->MapAction(CommandLogFunction, FExecuteAction::CreateRaw(this, &FExampleTCommands::ExampleLOG_Function));
	
}

void FExampleTCommands::ExampleLOG_Function()
{
	UE_LOG(LogTemp, Warning, TEXT("Example LOG Function is called."))
}
#undef LOCTEXT_NAMESPACE
