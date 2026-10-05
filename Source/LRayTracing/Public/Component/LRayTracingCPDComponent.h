// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LRayTracingCPDComponent.generated.h"


class UPrimitiveComponent;

/** Writes one test acoustic value to the attached parent primitive's CPD float slot 0. */
UCLASS(ClassGroup=(LRayTracing), meta=(BlueprintSpawnableComponent))
class LRAYTRACING_API ULRayTracingCPDComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	ULRayTracingCPDComponent();

	/** Test value exposed in Details. The GPU-side CPD value is TestValue + 1 to distinguish unset from zero. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LRayTracing|CPD", meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float TestValue = 0.5f;

	UFUNCTION(BlueprintCallable, Category="LRayTracing|CPD")
	void SetTestValue(float NewValue);

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void OnAttachmentChanged() override;
	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	static constexpr int32 CPDFloatIndex = 0;

	void UpdateParentCustomPrimitiveData();
	void ClearPreviousParentCustomPrimitiveData();

	TWeakObjectPtr<UPrimitiveComponent> PreviousParentPrimitive;
};