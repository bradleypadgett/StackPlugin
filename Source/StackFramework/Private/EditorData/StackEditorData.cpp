#include "EditorData/StackEditorData.h"
#include "EditorData/StackRootEditorData.h"



UStackEditorData::UStackEditorData(const FObjectInitializer& ObjectInitializer)
{
	RootEditorData = ObjectInitializer.CreateDefaultSubobject<UStackRootEditorData>(this, TEXT("StackEditorData"));

	if (RootEditorData != nullptr)
	{
		RootEditorData->OnPersistentDataChanged().AddUObject(this, &UStackEditorData::RootEditorDataChanged);
	}
}

void UStackEditorData::PostLoad()
{
	Super::PostLoad();

	if (RootEditorData == nullptr)
	{
		RootEditorData = NewObject<UStackRootEditorData>(this, TEXT("RootEditorData"), RF_Transactional);
		RootEditorData->OnPersistentDataChanged().AddUObject(this, &UStackEditorData::RootEditorDataChanged);
	}

	RootEditorData->ConditionalPostLoad();
}

void UStackEditorData::RootEditorDataChanged()
{
	OnPersistentDataChanged().Broadcast();
}

UStackRootEditorData& UStackEditorData::GetRootEditorData() const
{
	check(RootEditorData != nullptr);
	return *RootEditorData;
}

