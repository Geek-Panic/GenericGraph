using UnrealBuildTool;

public class GenericGraphEditor : ModuleRules
{
	public GenericGraphEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;
#if UE_5_6_OR_LATER
		CppCompileWarningSettings.ShadowVariableWarningLevel = WarningLevel.Error;
#else
		ShadowVariableWarningLevel = WarningLevel.Error;
#endif

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