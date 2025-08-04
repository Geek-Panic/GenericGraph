#pragma once
#include "CoreMinimal.h"
#include "GraphEdgeDefinitionBase.h"
#include "GraphNodeDefinitionBase.h"

#include "GraphDefinitionBase.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class GENERICGRAPHRUNTIME_API UGraphDefinitionBase : public UObject
{
	GENERATED_BODY()

public:
	explicit UGraphDefinitionBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual  ~UGraphDefinitionBase() override;
	
	/** Outputs graph structure to console/log */
	UFUNCTION(BlueprintCallable, Category = "Graph")
	void Print(bool ToConsole = true, bool ToScreen = true) const;

	/** Returns total depth of the graph hierarchy */
	UFUNCTION(BlueprintCallable, Category = "Graph")
	int GetLevelNum() const;

	/** Gets all nodes at specified hierarchy level */
	UFUNCTION(BlueprintCallable, Category = "Graph")
	void GetNodesByLevel(int Level, TArray<UGraphNodeDefinitionBase*>& Nodes) const;

	/** Resets graph by clearing all nodes and connections */
	void ClearGraph();
	
	/** Class for graph nodes */
	UPROPERTY(EditDefaultsOnly, Category = "Graph", AdvancedDisplay)
	TSubclassOf<UGraphNodeDefinitionBase> NodeType = nullptr;

	/** Class for graph edges */
	UPROPERTY(EditDefaultsOnly, Category = "Graph", AdvancedDisplay)
	TSubclassOf<UGraphEdgeDefinitionBase> EdgeType = nullptr;

	/** Enable/disable edge connections between nodes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graph", AdvancedDisplay)
	bool bEdgeEnabled = true;

	/** Root nodes of the graph hierarchy */
	UPROPERTY(BlueprintReadOnly, Category = "Graph")
	TArray<TObjectPtr<UGraphNodeDefinitionBase>> RootNodes = {};

	/** All nodes in the graph */
	UPROPERTY(BlueprintReadOnly, Category = "Graph")
	TArray<TObjectPtr<UGraphNodeDefinitionBase>> AllNodes = {};

#if WITH_EDITORONLY_DATA
	/** Editor-time graph representation.*/
	UPROPERTY()
	TObjectPtr<class UEdGraph> EditorGraph = nullptr;

	/** Allow node renaming in editor */
	UPROPERTY(EditDefaultsOnly, Category = "Editor", AdvancedDisplay)
	bool bCanRenameNode = true;

	/** Allow cyclic connections between nodes */
	UPROPERTY(EditDefaultsOnly, Category = "Editor", AdvancedDisplay)
	bool bCanBeCyclical = true;
#endif
};
