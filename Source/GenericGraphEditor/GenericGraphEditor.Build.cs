using UnrealBuildTool;

public class GenericGraphEditor : ModuleRules
{
	public GenericGraphEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
		ShadowVariableWarningLevel = WarningLevel.Error;

		PrivateIncludePaths.AddRange(new[]
		{
			"GenericGraphEditor/Private",
			"GenericGraphEditor/Public"
		});

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"GenericGraphRuntime",
			"AssetTools",
			"Slate",
			"InputCore",
			"SlateCore",
			"GraphEditor",
			"PropertyEditor",
			"EditorStyle",
			"Kismet",
			"KismetWidgets",
			"ApplicationCore",
			"ToolMenus"
		});
	}
}