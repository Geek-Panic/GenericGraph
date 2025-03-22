#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GraphEdgeDefinitionBase.h"
#include "GraphNodeDefinitionBase.h"

#include "GraphDefinitionBase.generated.h"

/**
 * @class UGraphDefinitionBase
 * @see UObject
 * @brief Base class defining a generic graph data structure with nodes and edges.
 */
UCLASS(Blueprintable, BlueprintType)
class GENERICGRAPHRUNTIME_API UGraphDefinitionBase : public UObject
{
	GENERATED_BODY()

public:
	
	UGraphDefinitionBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual ~UGraphDefinitionBase() override;
	
	
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

	
	/** Display name of the graph, used for debug purpose */
	UPROPERTY(EditDefaultsOnly, Category = "Graph")
	FText DisplayName = FText();

	/** Class for graph nodes */
	UPROPERTY(EditDefaultsOnly, Category = "Graph")
	TSubclassOf<UGraphNodeDefinitionBase> NodeType = nullptr;

	/** Class for graph edges */
	UPROPERTY(EditDefaultsOnly, Category = "Graph")
	TSubclassOf<UGraphEdgeDefinitionBase> EdgeType = nullptr;

	/** Gameplay tags associated with this graph */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graph")
	FGameplayTagContainer GraphTags = FGameplayTagContainer();

	
	/** Root nodes of the graph hierarchy */
	UPROPERTY(BlueprintReadOnly, Category = "Graph")
	TArray<UGraphNodeDefinitionBase*> RootNodes = {};

	/** All nodes in the graph */
	UPROPERTY(BlueprintReadOnly, Category = "Graph")
	TArray<UGraphNodeDefinitionBase*> AllNodes = {};
	
	/** Enable/disable edge connections between nodes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Graph")
	bool bEdgeEnabled = true;

	
#if WITH_EDITORONLY_DATA
	/** Editor-time graph representation.*/
	UPROPERTY()
	class UEdGraph* EditorGraph = nullptr;

	/** Allow node renaming in editor */
	UPROPERTY(EditDefaultsOnly, Category = "Editor")
	bool bCanRenameNode = true;

	/** Allow cyclic connections between nodes */
	UPROPERTY(EditDefaultsOnly, Category = "Editor")
	bool bCanBeCyclical = true;
#endif

	

};
