using System.IO;
using UnrealBuildTool;

public class ShaderExample : ModuleRules
{
    public ShaderExample(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicIncludePaths.AddRange(
            new string[] {
                // ... add public include paths required here ...
                Path.Combine(GetModuleDirectory("Renderer"), "Private"),
                Path.Combine(GetModuleDirectory("Renderer"), "Internal"),
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject", "Engine", "Slate",
                "SlateCore", "Projects",
                "RHI", "Renderer", "RenderCore",
            }
        );
    }
}