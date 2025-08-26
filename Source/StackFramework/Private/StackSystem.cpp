#include "StackSystem.h"
#include "Stack.h"
#include "StackHandle.h"
#include "EditorData/StackSystemEditorData.h"



UStackSystem::UStackSystem()
{
	Name = NAME_None;
}

void UStackSystem::PostInitProperties()
{
	Super::PostInitProperties();

	if (!HasAnyFlags(RF_ClassDefaultObject | RF_NeedLoad))
	{
#if WITH_EDITORONLY_DATA && WITH_EDITOR
		if (SystemEditorData == nullptr)
		{
			SystemEditorData = NewObject<UStackSystemEditorData>(this, TEXT("SystemEditorData"), RF_Transactional);
		}
#endif
	}
}

UStackSystemEditorData* UStackSystem::GetSystemEditorData()
{
	return SystemEditorData;
}

FStackHandle& UStackSystem::GetHandle(int HandleIndex)
{
	check(Handles.IsValidIndex(HandleIndex)); 
	return Handles[HandleIndex];
}

FStackHandle UStackSystem::AddHandle(UStack& InStack, FName InStackName)
{
	FStackHandle NewHandle(InStack);
	Handles.Add(NewHandle);
	return NewHandle;
}

void UStackSystem::RemoveHandle(FStackHandle& InHandleToRemove)
{
	Handles.Remove(InHandleToRemove);
}
