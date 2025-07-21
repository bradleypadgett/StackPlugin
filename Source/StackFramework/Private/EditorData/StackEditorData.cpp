#include "EditorData/StackEditorData.h"
#include "EditorData/StackEntryEditorData.h"



UStackEditorData::UStackEditorData(const FObjectInitializer& ObjectInitializer)
{
	StackEntryEditorData = ObjectInitializer.CreateDefaultSubobject<UStackEntryEditorData>(this, TEXT("StackEditorData"));

	if (StackEntryEditorData != nullptr)
	{
		StackEntryEditorData->OnPersistentDataChanged().AddUObject(this, &UStackEditorData::StackEntryEditorDataChanged);
	}
}

void UStackEditorData::PostLoad()
{
	Super::PostLoad();

	if (StackEntryEditorData == nullptr)
	{
		StackEntryEditorData = NewObject<UStackEntryEditorData>(this, TEXT("StackEntryEditorData"), RF_Transactional);
		StackEntryEditorData->OnPersistentDataChanged().AddUObject(this, &UStackEditorData::StackEntryEditorDataChanged);
	}

	StackEntryEditorData->ConditionalPostLoad();
}

void UStackEditorData::StackEntryEditorDataChanged()
{
	OnPersistentDataChanged().Broadcast();
}

UStackEntryEditorData& UStackEditorData::GetStackEntryEditorData() const
{
	check(StackEntryEditorData != nullptr);
	return *StackEntryEditorData;
}

