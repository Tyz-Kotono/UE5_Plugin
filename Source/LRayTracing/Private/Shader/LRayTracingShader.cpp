#include "LRayTracingShader.h"

IMPLEMENT_SHADER_TYPE(, FLRayTracingRGS, TEXT("/LRayTracing/LRaytracing.usf"), TEXT("MainRGS"), SF_RayGen);
IMPLEMENT_SHADER_TYPE(, FLRayTracingCHS, TEXT("/LRayTracing/LRaytracing.usf"), TEXT("MainCHS"), SF_RayHitGroup);
IMPLEMENT_GLOBAL_SHADER(FLRayTracingMS, "/Engine/Private/RayTracing/RayTracingBuiltInShaders.usf",
						"DefaultPayloadMS", SF_RayMiss);