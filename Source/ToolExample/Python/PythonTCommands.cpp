#include "PythonTCommands.h"

#include "IPythonScriptPlugin.h"
#include "PythonScriptTypes.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "Python TCommands"
TSharedRef<FUICommandList> FPythonTCommands::CommandList = MakeShareable(new FUICommandList);

FPythonTCommands::FPythonTCommands(): TCommands<FPythonTCommands>
(
	"Python TCommands",
	NSLOCTEXT("Python", "Python Commands", "Example Plugin"),
	NAME_None,
	"TAStyle" //FXXXX::GetAppStyleSetName() // Icon
)
{
}

void FPythonTCommands::RegisterCommands()
{
	UI_COMMAND(RunPython, "Run Python", "Python ToolTip", EUserInterfaceActionType::Button,
		   FInputChord());
	CommandList->MapAction(RunPython, FExecuteAction::CreateRaw(this, &FPythonTCommands::RunPython_Function));

}

void FPythonTCommands::RunPython_Function()
{
	//Python 是否启动
	IPythonScriptPlugin* PythonPlugin = IPythonScriptPlugin::Get();
	if (!PythonPlugin || !PythonPlugin->IsPythonAvailable())
	{
		return;
	}
	//查找当前插件
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("ToolExample");

	FString PluginPath = Plugin->GetBaseDir();
	//Plugin/Python/main.py
	FString PythonPath = FPaths::Combine(PluginPath,TEXT("Python/main.py"));

	FPythonCommandEx PythonCommandEx;
	PythonCommandEx.Command = FString::Printf(TEXT("\"%s\" --foo bar"), *PythonPath);
	//File Mode 是默认设置
	// PythonCommandEx.ExecutionMode = EPythonCommandExecutionMode::ExecuteFile;
	PythonPlugin->ExecPythonCommandEx(PythonCommandEx);
}
#undef LOCTEXT_NAMESPACE
