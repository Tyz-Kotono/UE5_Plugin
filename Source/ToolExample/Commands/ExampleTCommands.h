#pragma once

class FExampleTCommands : public TCommands<FExampleTCommands>
{
	
public:
	FExampleTCommands();
	virtual void RegisterCommands() override;
	
	static TSharedRef<FUICommandList> CommandList;
	TSharedPtr<FUICommandInfo> CommandLogLambda;
	TSharedPtr<FUICommandInfo> CommandLogFunction;
	void ExampleLOG_Function();
};
