#include "Component/LRayTracingCPDComponent.h"

#include "Components/PrimitiveComponent.h"

ULRayTracingCPDComponent::ULRayTracingCPDComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULRayTracingCPDComponent::SetTestValue(float NewValue)
{
	TestValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
	UpdateParentCustomPrimitiveData();
}

void ULRayTracingCPDComponent::OnRegister()
{
	Super::OnRegister();
	UpdateParentCustomPrimitiveData();
}

void ULRayTracingCPDComponent::OnUnregister()
{
	ClearPreviousParentCustomPrimitiveData();
	Super::OnUnregister();
}

void ULRayTracingCPDComponent::OnAttachmentChanged()
{
	Super::OnAttachmentChanged();
	UpdateParentCustomPrimitiveData();
}

void ULRayTracingCPDComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateParentCustomPrimitiveData();
}

void ULRayTracingCPDComponent::DestroyComponent(bool bPromoteChildren)
{
	ClearPreviousParentCustomPrimitiveData();
	Super::DestroyComponent(bPromoteChildren);
}

#if WITH_EDITOR
void ULRayTracingCPDComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ULRayTracingCPDComponent, TestValue))
	{
		UpdateParentCustomPrimitiveData();
	}
}
#endif

void ULRayTracingCPDComponent::UpdateParentCustomPrimitiveData()
{
	UPrimitiveComponent* ParentPrimitive = Cast<UPrimitiveComponent>(GetAttachParent());
	if (PreviousParentPrimitive.Get() != ParentPrimitive)
	{
		ClearPreviousParentCustomPrimitiveData();
	}

	if (ParentPrimitive)
	{
		// Slot 0 is reserved by this test component; +1 distinguishes an authored zero from an unset slot.
		ParentPrimitive->SetCustomPrimitiveDataFloat(CPDFloatIndex, FMath::Clamp(TestValue, 0.0f, 1.0f) + 1.0f);
		PreviousParentPrimitive = ParentPrimitive;
	}
}

void ULRayTracingCPDComponent::ClearPreviousParentCustomPrimitiveData()
{
	if (UPrimitiveComponent* PreviousParent = PreviousParentPrimitive.Get())
	{
		PreviousParent->SetCustomPrimitiveDataFloat(CPDFloatIndex, 0.0f);
	}
	PreviousParentPrimitive.Reset();
}