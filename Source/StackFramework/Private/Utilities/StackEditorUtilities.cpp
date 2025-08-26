#include "Utilities/StackEditorUtilities.h"
#include "StackSystem.h"
#include "Stack.h"
#include "UObject/UObjectGlobals.h"
#include "EditorData/StackSystemEditorData.h"




const FGuid FStackEditorUtilities::AddStackToSystem(UStackSystem& StackSystem, UStack& Stack)
{
	// TO-DO ~ once templated stacks are supported, here's a good place to add in to a recently used list


	// Begin transaction for undo/redo. Is here since this is where stack actually gets added in
	const FScopedTransaction Transaction(NSLOCTEXT("Stack", "AddStack", "Add Stack"));


	// collect all existing handle names to ensure uniqueness below
	TSet<FName> HandleNames;
	for (const FStackHandle& Handle : StackSystem.GetHandles())
	{
		HandleNames.Add(Handle.GetName());
	}

	// generate a unique handle name based on the stack’s base name
	FName StackHandleName = GetUniqueName(Stack.GetFName(), HandleNames);

	// ensure name doesn’t collide with another UObject in the system
	while (FindObjectFast<UObject>(&StackSystem, StackHandleName))
	{
		StackHandleName.SetNumber(StackHandleName.GetNumber() + 1);
	}


	StackSystem.Modify();

	const FStackHandle NewHandle = StackSystem.AddHandle(Stack, StackHandleName);


	UStackSystemEditorData* SystemEditorData = CastChecked<UStackSystemEditorData>(StackSystem.GetSystemEditorData(), ECastCheckedType::NullChecked);
	// TO-DO ~ Later on when allowing standalone editing for UStacks, refactor to account for temporary systems and only allowing one stack for it
	SystemEditorData->SyncSystemGraph(StackSystem);


	return NewHandle.GetHandleID();
}


FName FStackEditorUtilities::GetUniqueName(FName BaseName, const TSet<FName>& ExistingNames)
{
	if (!ExistingNames.Contains(BaseName)) return BaseName;

	int32 Suffix = 1;
	FName CandidateName;
	do
	{
		CandidateName = *FString::Printf(TEXT("%s%d"), *BaseName.ToString(), Suffix++);
	} while (ExistingNames.Contains(CandidateName));

	return CandidateName;
}


