#include "State/StackData.h"
#include "State/StackEditorData.h"



UStackData::UStackData(const FObjectInitializer& ObjectInitializer)
{
	EditorData = ObjectInitializer.CreateDefaultSubobject<UStackEditorData>(this, TEXT("EditorData"));

	//if (EditorData != nullptr)
	//{
	//	EditorData->OnPersistentDataChanged().AddUObject(this, &UStackData::OnPersistentDataChanged);
	//}
}

void UStackData::PostLoad()
{
	Super::PostLoad();

	if (EditorData == nullptr)
	{
		EditorData = NewObject<UStackEditorData>(this, TEXT("EditorData"), RF_Transactional);
	//	StackEditorData->OnPersistentDataChanged().AddUObject(this, &UStackData::OnPersistentDataChanged);
	}

	EditorData->ConditionalPostLoad();
}

UStackEditorData& UStackData::GetEditorData() const
{
	check(EditorData != nullptr);
	return *EditorData;
}
