#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "StackHandle.h"
#include "StackSystem.generated.h"



class UStack;
struct FStackHandle;

UCLASS(BlueprintType)
class STACKFRAMEWORK_API UStackSystem : public UObject
{
	GENERATED_BODY()

public:
	UStackSystem();

	const TArray<FStackHandle>& GetHandles() const { return StackHandles; }
	TArray<FStackHandle>& GetHandles() { return StackHandles; }

	int32 GetNumHandles() const { return StackHandles.Num(); }
	void ClearHandles() { StackHandles.Reset(); }
	void AddHandle(FStackHandle& InNewHandle);
	void RemoveHandle(FStackHandle& InHandleToRemove);


	UPROPERTY(EditAnywhere, Category = "System")
	FName Name;

	UPROPERTY(EditAnywhere, Instanced, Category = "System")
	TObjectPtr<UStack> StackAsset;

	UPROPERTY()
	TArray<FStackHandle> StackHandles;

};
