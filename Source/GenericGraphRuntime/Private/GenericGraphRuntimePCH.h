#pragma once
#include "IGenericGraphRuntime.h"

#define LOG_INFO(FMT, ...) UE_LOG(GenericGraphRuntime, Display, (FMT), ##__VA_ARGS__)
#define LOG_WARNING(FMT, ...) UE_LOG(GenericGraphRuntime, Warning, (FMT), ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) UE_LOG(GenericGraphRuntime, Error, (FMT), ##__VA_ARGS__)
