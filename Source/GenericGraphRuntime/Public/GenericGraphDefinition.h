#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericGraphEdge.h"
#include "GenericGraphNode.h"

#include "GenericGraphDefinition.generated.h"

/**
 * @class UGenericGraphDefinition
 * @see UObject
 * @brief Base class defining a generic graph data structure with nodes and edges.
 */
UCLASS(Blueprintable, Abstract, BlueprintType)
class GENERICGRAPHRUNTIME_API UGenericGraphDefinition : public UObject
{
	GENERATED_BODY()

public:
	
	UGenericGraphDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual ~UGenericGraphDefinition() override;

	
	/** Outputs graph structure to console/log */
	UFUNCTION(BlueprintCallable, Category = "GenericGraph")
	void Print(bool ToConsole = true, bool ToScreen = true);

	/** Returns total depth of the graph hierarchy */
	UFUNCTION(BlueprintCallable, Category = "GenericGraph")
	int GetLevelNum() const;

	/** Gets all nodes at specified hierarchy level */
	UFUNCTION(BlueprintCallable, Category = "GenericGraph")
	void GetNodesByLevel(int Level, TArray<UGenericGraphNode*>& Nodes);

	/** Resets graph by clearing all nodes and connections */
	void ClearGraph();

	
	/** Display name of the graph, used for debug purpose */
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph")
	FString Name;

	/** Class for graph nodes */
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph")
	TSubclassOf<UGenericGraphNode> NodeType;

	/** Class for graph edges */
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph")
	TSubclassOf<UGenericGraphEdge> EdgeType;

	/** Gameplay tags associated with this graph */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GenericGraph")
	FGameplayTagContainer GraphTags;


protected:
	
	/** Root nodes of the graph hierarchy */
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraph")
	TArray<UGenericGraphNode*> RootNodes;

	/** All nodes in the graph */
	UPROPERTY(BlueprintReadOnly, Category = "GenericGraph")
	TArray<UGenericGraphNode*> AllNodes;
	
	/** Enable/disable edge connections between nodes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GenericGraph")
	bool bEdgeEnabled;

#if WITH_EDITORONLY_DATA
    /** Editor-time graph representation.*/
	UPROPERTY()
	class UEdGraph* EditorGraph;

	/** Allow node renaming in editor */
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph_Editor")
	bool bCanRenameNode;

	/** Allow cyclic connections between nodes */
	UPROPERTY(EditDefaultsOnly, Category = "GenericGraph_Editor")
	bool bCanBeCyclical = true;
#endif
};
