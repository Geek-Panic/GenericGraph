#pragma once
#include "GraphDefinitionBase.h"
#include "GraphEdgeDefinitionBase.h"
#include "GraphNodeDefinitionBase.h"
#include "GraphEditorModule.h"

#define LOG_INFO(FMT, ...) UE_LOG(GraphEditorLog, Display, (FMT), ##__VA_ARGS__)
#define LOG_WARNING(FMT, ...) UE_LOG(GraphEditorLog, Warning, (FMT), ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) UE_LOG(GraphEditorLog, Error, (FMT), ##__VA_ARGS__)
