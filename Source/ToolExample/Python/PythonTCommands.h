#pragma once

class FPythonTCommands: public TCommands<FPythonTCommands>
{
	
public:
	FPythonTCommands();
	virtual void RegisterCommands() override;
	static TSharedRef<FUICommandList> CommandList;

	TSharedPtr<FUICommandInfo> RunPython;
	void RunPython_Function();
};
