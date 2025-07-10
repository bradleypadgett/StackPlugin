#pragma once
#include "ViewModels/StackModule.h"
#include "StackEditorState.generated.h"



class UStackViewState;
class UStackModule;

UCLASS()
class UStackEditorState : public UObject
{
	GENERATED_BODY()

public:
	UStackEditorState(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	UStackViewState& GetStackViewState() const;

	const TArray<UStackModule*>& GetModules() const;

private:
	UPROPERTY(Instanced)
	TObjectPtr<UStackViewState> StackViewState;
};
