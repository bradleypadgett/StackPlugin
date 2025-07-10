#include "State/StackEditorState.h"
#include "State/StackViewState.h"



UStackEditorState::UStackEditorState(const FObjectInitializer& ObjectInitializer)
{
	StackViewState = ObjectInitializer.CreateDefaultSubobject<UStackViewState>(this, TEXT("StackViewState"));

	//if (StackViewState != nullptr)
	//{
	//	StackViewState->OnPersistentDataChanged().AddUObject(this, &UStackEditorState::OnPersistentDataChanged);
	//}
}

void UStackEditorState::PostLoad()
{
	Super::PostLoad();

	if (StackViewState == nullptr)
	{
		StackViewState = NewObject<UStackViewState>(this, TEXT("StackViewState"), RF_Transactional);
	//	StackViewState->OnPersistentDataChanged().AddUObject(this, &UStackEditorState::OnPersistentDataChanged);
	}

	StackViewState->ConditionalPostLoad();
}

UStackViewState& UStackEditorState::GetStackViewState() const
{
	check(StackViewState != nullptr);
	return *StackViewState;
}

const TArray<UStackModule*>& UStackEditorState::GetModules() const
{
	static TArray<UStackModule*> DummyModules;

	if (DummyModules.Num() == 0)
	{
		for (int32 i = 0; i < 2; ++i)
		{
			UStackModule* Module = NewObject<UStackModule>(const_cast<UStackEditorState*>(this));
			DummyModules.Add(Module);
		}
	}

	return DummyModules;
}

