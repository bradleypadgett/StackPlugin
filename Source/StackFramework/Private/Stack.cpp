#include "Stack.h"
#include "ViewModels/StackEntry.h"



UStack::UStack()
{
	if (!StackID.IsValid())
	{
		StackID = FGuid::NewGuid();
	}
}

void UStack::Initialize()
{

}

const FString& UStack::GetUniqueStackName() {
	return UniqueStackName;
}

bool UStack::SetUniqueStackName(const FString& NewName)
{
	if (NewName == UniqueStackName) return false;

	Modify();
	UniqueStackName = NewName;

	const FString ExistingName = IsAsset() ? GetFName().GetPlainNameString() : GetName();
	if (ExistingName != NewName)
	{
		Rename(*MakeUniqueObjectName(GetOuter(), StaticClass(), *NewName).ToString(), GetOuter());
	}

	// TO-DO ~ in the future, update parameter binding paths ( "OldName.Param" - "NewName.Param" )

	return true;
}



UStackEditorData* UStack::GetStackEditorData() const
{
	return StackEditorData;
}