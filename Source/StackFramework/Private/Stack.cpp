#include "Stack.h"
#include "ViewModels/StackEntry.h"



UStack::UStack()
{
	if (!StackID.IsValid())
	{
		StackID = FGuid::NewGuid();
	}
}

const FString& UStack::GetUniqueName() {
	return UniqueName;
}

bool UStack::SetUniqueName(const FString& InName) {
	UniqueName = InName;
	return true;
}

UStackEditorState* UStack::GetStackEditorState() const
{
	return StackEditorState;
}