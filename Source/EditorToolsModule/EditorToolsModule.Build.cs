using UnrealBuildTool;

public class EditorToolsModule : ModuleRules
{
    public EditorToolsModule(ReadOnlyTargetRules Target) : base(Target)
    {
        if (Target.bBuildEditor)
        {
            PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd",           
                "PropertyEditor",    
                "Slate",
                "SlateCore",
                "EditorStyle"     
            });

            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "InputCore",
                "Projects"
            });
        }
    }
}
